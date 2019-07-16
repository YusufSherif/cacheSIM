#ifndef CACHESIM_CACHELINE_H
#define CACHESIM_CACHELINE_H

#include <cmath>

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)

class cacheLine {
private:
    bool validBit;
    unsigned int tag;
    int address;
    int offset;
    int data;

    static int blockSize, numOfBlocks;

public:
    cacheLine();
    void fill(unsigned int addr);
    bool getValidBit();
    unsigned int getTag();

    static void initLines(int p_blockSize);
    ~cacheLine();
};


#endif //CACHESIM_CACHELINE_H
