#ifndef CACHESIM_CACHELINE_H
#define CACHESIM_CACHELINE_H

#include <cmath>

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)

class cacheLine {
private:
    //Valid bit is used to abstractly represent the valid bit in a cache block. Represented as a bool here.
    bool validBit;
    //The tag field here is used to represent the actual tag that should actually be stored in the block if it were real
    unsigned int tag;
    //Data field is just here for completion.
    int data;

    //These fields are used to help in the extraction of the tag in the fill function.
    static int blockSize, numOfBlocks;

public:
    //Constructor, sets the valid bit to zero. This mimics the behaviour of the real cache as the valid bit of each line
    //is initially set to zero. The constructors of the lines is only called in the constructor of the cache class, so
    //the behaviour should follow the actual behaviour of a cache.
    cacheLine();
    //Fill is used when we get a miss, and it abstractly represents filling the block with the new tag and the new data.
    //However, since we have no data it only extracts the tag from the passed addr and puts assigns it to the tag field.
    //Also, it always sets the valid bit to true just in case the miss was resulting from a cold start.
    void fill(unsigned int addr);
    //The following two functions are no more than getters.
    bool getValidBit();
    unsigned int getTag();
    //static function to set the static field of the class
    static void initLines(int p_blockSize);
    //Destructor
    ~cacheLine();
};


#endif //CACHESIM_CACHELINE_H
