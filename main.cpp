#include <iostream>
#include "cache.h"

int main()
{
    cache sim4(4);
    sim4.simulate();

    cache sim8(8);
    sim8.simulate();

    cache sim16(16);
    sim16.simulate();

    cache sim32(32);
    sim32.simulate();

    cache sim64(64);
    sim64.simulate();

    cache sim128(128);
    sim128.simulate();


}
