//
// Created by Yusuf Sherif on 2019-07-14.
//

#include "cacheLine.h"

int cacheLine::blockSize;
int cacheLine::offsetBits;
int cacheLine::indexBits;
int cacheLine::tagBits;

cacheLine::cacheLine() {
    validBit = false;
}

bool cacheLine::getValidBit() {
    return validBit;
}

void cacheLine::fill(unsigned int addr) {
    validBit = true;
    tag  = addr >> (offsetBits+indexBits);
}

unsigned int cacheLine::getTag() {
    return tag;
}

void cacheLine::initLines(int p_blockSize) {
    blockSize = p_blockSize;
    offsetBits = log2(p_blockSize);
    indexBits = log2(CACHE_SIZE/blockSize);
    tagBits = 32-indexBits-offsetBits;
}
