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
    //Depending on the blockSize, the tag is extracted. We first remove the offset bits by dividing by the blockSize.
    //Then, we remove the index bits by dividing by numOfBlocks. We used the idea of right shifting through division
    //that was discussed in the class here.
}

unsigned int cacheLine::getTag() {
    return tag;
}

bool cacheLine::getValidBit() {
    return validBit;
}

cacheLine::~cacheLine() {

}
