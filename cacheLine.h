//
// Created by Yusuf Sherif on 2019-07-14.
//

#ifndef CACHESIM_CACHELINE_H
#define CACHESIM_CACHELINE_H

#include <cmath>

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)

class cacheLine {
    int blockSize;
    bool validBit;
    unsigned int tag;
    int address;
    int offset;
    int data;
public:
    cacheLine(int p_blockSize);
    bool getValidBit();

    void fill(unsigned int addr);

    unsigned int getTag();
};


#endif //CACHESIM_CACHELINE_H
