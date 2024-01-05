#include "Simulator.h"

#include <iostream>

int main()
{
    Simulator simulator;
    
    simulator.setUp();
    simulator.run();
    simulator.exit();

    return 0;
}