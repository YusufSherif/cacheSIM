main.cpp:
Contains the main function of the program.

cache.h & cahce.cpp:
The class implementation for the chache. This class recieves the required blockSize in the constructor and the simulate method is used to simulate the cache behaviour depending on which memGen was selected. 

cacheLine.h & cacheLine.cpp:
The class implementation for a line in the cache. This class is used by the cache class as the template type of the vector of cache lines. All the required cache lines are constructed from the cahce calss constructor, setting the valid bit to zero. So, in the end, we have a fully initialized cache as we would have in reality.

Note: This cache does not actually store any data, rather it simulates storing the data in the cache by storing the tag in each line object in the tag field. This program is used to simulate the cache behaviour and get expected hit ratio from the memGen functions.

