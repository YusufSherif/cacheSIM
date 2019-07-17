#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H

#include <iostream>
#include <iomanip>
#include <vector>

#include "cacheLine.h"

using namespace std;

#define		NO_OF_ITERATIONS	1000000		// Change to 1,000,000

class cache {
private:
    int numOfBlocks, blockSize;
    std::vector<cacheLine> cacheLines;

    enum cacheResType {MISS=0, HIT=1};

    unsigned int rand_();
    unsigned int memGenA();
    unsigned int memGenB();
    unsigned int memGenBSeeded();
    unsigned int memGenC();
    unsigned int memGenD();
    unsigned int memGenE();
    unsigned int memGenF();
    unsigned int memGenG();
    unsigned int memGenH();
    unsigned int memGenI();

    cacheResType cacheSimDM(unsigned int addr);

public:
    cache(int p_blockSize);
    void simulate();
    ~cache();
};


#endif //CACHESIM_CACHE_H
