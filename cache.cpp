#include "cache.h"

unsigned int cache::rand_()
{
    /* The following implements a random number generator */
    unsigned int m_w = 0xABCCAB55;    /* must not be zero, nor 0x464fffff */
    unsigned int m_z = 0x05786902;    /* must not be zero, nor 0x9068ffff */

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

unsigned int cache::memGenA() {

    static unsigned int addr=0;
    return (addr++)%(DRAM_SIZE/4);
    //The addr variable is static. So, its value is saved even after we exit the function.
    //The address is incremented upon each call and modded with DRAM_SIZE/4. This means that every DRAM_SIZE/4 calls,
    //the address returns to zero and so on. This means that the ratio should end up being
    //(100*((blockSize-1)*int(NO_OF_ITERATIONS/blockSize)+(NO_OF_ITERATIONS%blockSize)-
    //((NO_OF_ITERATIONS%blockSize)?1:0))/NO_OF_ITERATIONS)

}

unsigned int cache::memGenB()
{
    static unsigned int addr=0;
    return  rand_()%(64*1024);
    //This uses the rand function to generate an random number then mods it with the size of the cache to limit the
    //addresses to 64 KB memory address space.
}

unsigned int cache::memGenBSeeded() {
    static unsigned int addr=0;
    return  rand()%(64*1024);
}

unsigned int cache::memGenC() {

    static unsigned int a1=0, a0=0;
    a0++;
    if(a0 == 512)
    {
        a1++;
        a0=0;
    }
    if(a1 == 128)
        a1=0;
    return(a1 + a0*128);
    //0 for 16 bits, a0 for 9 bits, a1 for 7 bits
    //Tag is always 16 bits, this means that there will be no collision misses.
    //So, misses are contributed to cold starts and blockSize. blockSize will contribute to the number of cold start
    //misses for the same reason as mentioned in D & E. It will also contribute to the hit ratio because as the
    //blockSize increases, the the offset bits increase, and in turn the index bits decrease shrinking to only come
    //from the more significant bits of the variable a0. Since a0 is incremented by 1 each iteration, the chances
    //for the index not changing between each iteration is higher since the index bits now reside in the upper 9 bits of
    //a0. This means that chances that we're accessing the same block but with different offsets, is higher as the
    //blockSize increases. Thus, the higher hit ratio in increased block sizes.
    //
}

unsigned int cache::memGenD()
{
    static unsigned int addr=0;
    return (addr++)%(1024*4);
    //Same as E but 4 times less the memory address space. Therefore higher hit ratios because cold start misses would
    //be effectively less. 4KB/blockSize misses < 16KB/blockSize misses.
    //(100*float(NO_OF_ITERATIONS-(4*1024/(float)blockSize))/NO_OF_ITERATIONS)
}

unsigned int cache::memGenE()
{
    static unsigned int addr=0;
    return (addr++)%(1024*16);
    //The addresses generated by this function would be limited to 16KB address space. The addresses are simply
    //incremented each time and then modded to fit in the 16KB address space. The only misses these addresses should
    //generate are cold starts. After that all addresses should generate hits. Thus, the 99 hit ratio in all blockSizes.
    //Notice though how the value converges to 100 as the size of the block increases. This is because as the blockSize
    //increases, the number of initial cold starts would be less. Therefore, lower misses overall.
    //(100*float(NO_OF_ITERATIONS-(16*1024/(float)blockSize))/NO_OF_ITERATIONS)
}

unsigned int cache::memGenF()
{
    static unsigned int addr=0;
    return (addr+=64)%(128*1024);
    //This memGen would result in the cache missing at every memory access if the blockSize <=64 because the addresses
    //generated are 64 numbers apart. Thus, the hit ratio being 0 for blockSizes up to 64. On blockSizes of 128, we
    //observe a hit ratio of 50 because each two consequent addresses generated by this function would be in the same
    //block. Therefore, we would have a hit after each miss. Thus, the hit ratio being 50. The addresses generated by
    //this function is limited to a 128KB address space.
    //(100-100*(float(NO_OF_ITERATIONS/((int(blockSize/64))?(int(blockSize/64)):1))/NO_OF_ITERATIONS))
}

unsigned int cache::memGenG() {
    static unsigned int addr=0;
    addr+=blockSize;
    return addr;
    //This function should result in misses every time as the addr is incremented by the blockSize to make it impossible
    //for two concurrent generated addresses to be in the same block.
}

unsigned int cache::memGenH() {
    return 0;
    //Should only result in one miss, which is the first cold start miss. Then all the consequent accesses should be
    //hits. This means that as the number of iterations increases, the hit ratio should converge to 100. Also, the
    //blockSize would not matter here as we're just accessing the first block only anyways. @100M iterations, with
    //15 decimal precision, it was represented as 100. @1000 iterations, it was 99.9, @1M it was 99.9999
}

cache::cacheResType cache::cacheSimDM(unsigned int addr) {
    //Index is extracted by dividing by blockSize (effectively shifting the offset bits to the right), then modding
    //with numOfBlocks (shifting the index bits to the right and then getting the remainder, effectively extracting the
    //index bits).
    int index = (addr/blockSize)%numOfBlocks;
    if(!cacheLines[index].getValidBit()){ //Checking for cold start misses.
        cacheLines[index].fill(addr);
        return MISS;
    } else {
        if (cacheLines[index].getTag() == (addr / blockSize / numOfBlocks)) { //Checking if the tags match
            return HIT;
        } else {
            cacheLines[index].fill(addr);
            return MISS;
        }
    }
}

#define		NO_OF_ITERATIONS	1000000		// Change to 1,000,000

void cache::simulate() {
    char *msg[2] = {"Miss","Hit"};

    uint64_t hit = 0; //Overflow happened over here
    cacheResType r;

    unsigned int addr;
    cout << "Direct Mapped Cache Simulator\n";

    for(int inst=0;inst<NO_OF_ITERATIONS;inst++)
    {
        addr = memGenBSeeded();
        r = cacheSimDM(addr);
        if(r == HIT) hit++;
        //cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";
    }
    cout<< std::setprecision(15);
    //cout << "Expected for case A: " << (100*float(float(blockSize-1)*int(NO_OF_ITERATIONS/blockSize)+(NO_OF_ITERATIONS%blockSize)-((NO_OF_ITERATIONS%blockSize)?1:0))/NO_OF_ITERATIONS) << endl;
    //cout<< "Expected for case D: " << (100*float(NO_OF_ITERATIONS-(4*1024/(float)blockSize))/NO_OF_ITERATIONS) << endl;
    //cout<< "Expected for case E: " << (100*float(NO_OF_ITERATIONS-(16*1024/(float)blockSize))/NO_OF_ITERATIONS) << endl;
    //cout<< "Expected for case F: " << (100-100*(float(NO_OF_ITERATIONS/((int(blockSize/64))?(int(blockSize/64)):1))/NO_OF_ITERATIONS)) << endl;
    cout << "Hit ratio = " <<dec<< (100*(float)hit/NO_OF_ITERATIONS)<< endl;

}

cache::cache(int p_blockSize) {
    numOfBlocks = CACHE_SIZE/p_blockSize;
    blockSize = p_blockSize;
    //Init lines is used to pass the required blockSize to the cacheLine class to that each object is aware of its size
    //so it could later properly extract the tag.
    cacheLine::initLines(p_blockSize);
    //After we calculate the numOfBlocks, we construct $numOfBlocks blocks and push them in the vector. This should
    //abstractly represent an empty cache after the loop is finished.
    for(int i = 0; i<numOfBlocks; i++) {
        cacheLines.emplace_back();
    }
}

cache::~cache() {

}
