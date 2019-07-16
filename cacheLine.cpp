#include "cacheLine.h"

int cacheLine::blockSize;
int cacheLine::numOfBlocks;

void cacheLine::initLines(int p_blockSize) {
    blockSize = p_blockSize;
    numOfBlocks = CACHE_SIZE/p_blockSize;
}

cacheLine::cacheLine() {
    validBit = false;
}

void cacheLine::fill(unsigned int addr) {
    validBit = true;
    tag  = addr / numOfBlocks / blockSize;
}

unsigned int cacheLine::getTag() {
    return tag;
}

bool cacheLine::getValidBit() {
    return validBit;
}

cacheLine::~cacheLine() {

}
