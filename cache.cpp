#include "cache.h"

unsigned int cache::rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

unsigned int cache::memGenA() {

    static unsigned int addr=0;
    return (addr++)%(DRAM_SIZE/4);

}

unsigned int cache::memGenB()
{
    static unsigned int addr=0;
    return  rand_()%(64*1024);
}

unsigned int cache::memGenC() {

    static unsigned int a1=0, a0=0;
    a0++;
    if(a0 == 512) { a1++; a0=0; }
    if(a1 == 128) a1=0;
    return(a1 + a0*128);

}

unsigned int cache::memGenD()
{
    static unsigned int addr=0;
    return (addr++)%(1024*4);
}

unsigned int cache::memGenE()
{
    static unsigned int addr=0;
    return (addr++)%(1024*16);
}

unsigned int cache::memGenF()
{
    static unsigned int addr=0;
    return (addr+=64)%(128*1024);
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

#define		NO_OF_Iterations	1000000		// Change to 1,000,000

void cache::simulate() {
    char *msg[2] = {"Miss","Hit"};

    unsigned int hit = 0;
    cacheResType r;

    unsigned int addr;
    cout << "Direct Mapped Cache Simulator\n";

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGenA();
        r = cacheSimDM(addr);
        if(r == HIT) hit++;
        //cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";
    }
    cout << "Hit ratio = " <<dec<< (100*hit/NO_OF_Iterations)<< endl;

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
