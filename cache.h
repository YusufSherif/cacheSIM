#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H

#include <iostream>
#include <iomanip>
#include <vector>

#include "cacheLine.h"

using namespace std;

class cache {
private:
    int numOfBlocks, blockSize;
    std::vector<cacheLine> cacheLines;

    enum cacheResType {MISS=0, HIT=1};

    /* The following implements a random number generator */
    unsigned int m_w = 0xABCCAB55;    /* must not be zero, nor 0x464fffff */
    unsigned int m_z = 0x05786902;    /* must not be zero, nor 0x9068ffff */
    unsigned int rand_();
    unsigned int memGenA();
    unsigned int memGenB();
    unsigned int memGenC();
    unsigned int memGenD();
    unsigned int memGenE();
    unsigned int memGenF();


    cacheResType cacheSimDM(unsigned int addr);

public:
    cache(int p_blockSize);
    void simulate();
    ~cache();
};


#endif //CACHESIM_CACHE_H
