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
    //100*((blockSize-1)*(NO_OF_ITERATIONS/blockSize)+(NO_OF_ITERATIONS%blockSize)-1)/NO_OF_ITERATIONS

}

unsigned int cache::memGenB()
{
    static unsigned int addr=0;
    return  rand_()%(64*1024);
    //This uses the rand function to generate an random number then mods it with the size of the cache to limit the
    //addresses to 64 KB memory space.
}

unsigned int cache::memGenC() {

    static unsigned int a1=0, a0=0;
    a0++;
    if(a0 == 512) { a1++; a0=0; }
    if(a1 == 128) a1=0;
    return(a1 + a0*128);
    //
}

unsigned int cache::memGenD()
{
    static unsigned int addr=0;
    return (addr++)%(1024*4);
    //
}

unsigned int cache::memGenE()
{
    static unsigned int addr=0;
    return (addr++)%(1024*16);
    //
}

unsigned int cache::memGenF()
{
    static unsigned int addr=0;
    return (addr++)%(128*1024);
    //
}

cache::cacheResType cache::cacheSimDM(unsigned int addr) {
    int index = (addr/blockSize)%numOfBlocks;
    if(!cacheLines[index].getValidBit()){
        cacheLines[index].fill(addr);
        return MISS;
    } else {
        if (cacheLines[index].getTag() == (addr / blockSize / numOfBlocks)) {
            return HIT;
        } else {
            cacheLines[index].fill(addr);
            return MISS;
        }
    }
}

#define		NO_OF_ITERATIONS	100000000		// Change to 1,000,000

void cache::simulate() {
    char *msg[2] = {"Miss","Hit"};

    uint64_t hit = 0; //Overflow happened over here
    cacheResType r;

    unsigned int addr;
    cout << "Direct Mapped Cache Simulator\n";

    for(int inst=0;inst<NO_OF_ITERATIONS;inst++)
    {
        addr = memGenF();
        r = cacheSimDM(addr);
        if(r == HIT) hit++;
        //cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";
    }
    cout<< std::setprecision(15);
    cout << "Expected for case A: " << (100*float(float(blockSize-1)*int(NO_OF_ITERATIONS/blockSize)+(NO_OF_ITERATIONS%blockSize)-((NO_OF_ITERATIONS%blockSize)?1:0))/NO_OF_ITERATIONS) << endl;
    cout << "Hit ratio = " <<dec<< (100*(float)hit/NO_OF_ITERATIONS)<< endl;

}

cache::cache(int p_blockSize) {
    numOfBlocks = CACHE_SIZE/p_blockSize;
    blockSize = p_blockSize;
    cacheLine::initLines(p_blockSize);
    for(int i = 0; i<numOfBlocks; i++) {
        cacheLines.emplace_back();
    }
}

cache::~cache() {

}
