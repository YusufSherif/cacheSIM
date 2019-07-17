#include <iostream>
#include <ctime>
#include "cache.h"

int main()
{
    srand(time(0));

    for(int i=4; i<=512; i*=2)
    {
        cout<< "Cache block size: " << i << endl;
        cache sim(i);
        sim.simulate();
        printf("\n");
    }
}
