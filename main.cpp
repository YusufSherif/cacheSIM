#include <iostream>
#include "cache.h"

int main()
{
    for(int i=4; i<=512; i*=2)
    {
        cout<< "Cache block size: " << i << endl;
        cache sim(i);
        sim.simulate();
        printf("\n");
    }
}
