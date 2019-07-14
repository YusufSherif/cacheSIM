//
// Created by Yusuf Sherif on 2019-07-14.
//

#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H

#include <iostream>
#include <iomanip>

using namespace std;

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)


class cache {

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
    void simulate();
};


#endif //CACHESIM_CACHE_H
