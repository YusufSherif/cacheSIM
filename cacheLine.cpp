//
// Created by Yusuf Sherif on 2019-07-14.
//

#include "cacheLine.h"

cacheLine::cacheLine(int p_blockSize) {
    validBit = false;
    blockSize = p_blockSize;
}

bool cacheLine::getValidBit() {
    return validBit;
}

void cacheLine::fill(unsigned int addr) {
    validBit = true;
    tag  = addr >> (int)log2(CACHE_SIZE/blockSize);
}

unsigned int cacheLine::getTag() {
    return tag;
}

