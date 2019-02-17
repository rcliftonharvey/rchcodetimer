//
// RCH::CodeTimer -- demo project
//
// Measures the execution time inside a specific scope of code.
// https://github.com/rcliftonharvey/rchcodetimer
// 
// Copyright © 2019 R. Clifton-Harvey
//
// This source code is released under the MIT license, which means
// you can do anything you want with it, as long as you credit it.
//
// A full version of the license can be found here:
// https://github.com/rcliftonharvey/rchcodetimer/blob/master/LICENSE
//
// Include the RCH::CodeTimer class
#include "../include/rchcodetimer.h"

// Quick demonstration project for RCH::CodeTimer
int main (int argc, char *argv[])
{
    // Instantiate a code timer with an instance ID
    //
    // Since this is instantiated at the beginning of int main,
    // it will be destroyed when int main ends, so it will be
    // measuring the execution time of the entire program, and
    // it will output its result as the last timer, not first.
    //
    RCH::CodeTimer timer1 ("int main");
    
    // Just a number to crunch
    double value = 0.99999;
    
    // Execute some repetitive code
    for (unsigned int delay=0; delay<100000; ++delay)
    {
        value = std::pow(value, value);
    }
    
    // Create a new scope for a second timer with curly braces
    {
        // Instantiate a second code timer with instance ID
        //
        // Since this is created inside a separate scope, it
        // will be destroyed as soon as this section of code
        // goes out of scope, so it will only be measuring
        // the execution time of the code inside the braces.
        //
        RCH::CodeTimer timer2 ("sub scope");
        
        // Execute some repetitive code
        for (unsigned int delay=0; delay<100000; ++delay)
        {
            value = std::sqrt(value);
        }
    } // Scope ends, timer2 is destroyed, time is measured
    
    // Create a result variable for the measured nanoseconds
    // and yet another separate scope for the third timer
    double t3result = 0.0;
    {
        // Instantiate a third timer with pointer to variable
        //
        // Since this is instantiated with a pointer to an
        // external double variable, the calculated result
        // time will be stored in the variable, but it will
        // not be printed to console.
        //
        RCH::CodeTimer timer3 (&t3result);
        
        // Execute some repetitive code
        for (unsigned int delay=0; delay<100000; ++delay)
        {
            value = std::tanh(1.0 / value);
        }
    } // Scope ends, timer3 is destroyed, time is measured
    
    // Since the third timer was instantiated with a pointer
    // to an external double variable, the timed result will
    // only be stored in the external variable, but nothing
    // will be printed to console automatically.
    std::cout << "timer3 finished in " 
              << std::to_string(t3result) 
              << " ns" << std::endl;
    
    return 0;
    
} // int main ends, timer1 is destroyed, elapsed time is measured
