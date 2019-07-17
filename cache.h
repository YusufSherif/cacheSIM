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

    unsigned int rand_();
    unsigned int memGenA();
    unsigned int memGenB();
    unsigned int memGenC();
    unsigned int memGenD();
    unsigned int memGenE();
    unsigned int memGenF();
    unsigned int memGenG();

    cacheResType cacheSimDM(unsigned int addr);

public:
    cache(int p_blockSize);
    void simulate();
    ~cache();
};


#endif //CACHESIM_CACHE_H
