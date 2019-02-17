//
// RCH::CodeTimer
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
#ifndef RCH_CODETIMER_H
#define RCH_CODETIMER_H
#pragma once


// --- INCLUDE DEPENDENCIES BELOW --- //
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
// --- INCLUDE DEPENDENCIES ABOVE --- //


// ---- MODULE DEFINITIONS BELOW ---- //
#define TIMER_CLOCK std::chrono::high_resolution_clock
#define TIMER_STAMP TIMER_CLOCK::time_point
#define TIMER_VALUE double            // timestamp type
#define TIMER_TCAST std::chrono::time_point_cast<std::chrono::nanoseconds>
#define TIMER_PRECI 6                 // post-comma precision
// ---- MODULE DEFINITIONS ABOVE ---- //


namespace RCH
{
// ---- MODULE CODE STARTS BELOW ---- //
//    
//    When a CodeTimer is instantiated, the timer automatically starts.
//    When a CodeTimer is destroyed, the timer automatically stops and
//    calculates the elapsed time since start.
//
//    If an external double pointer is specified at instantiation, the
//    result will automatically be written into the external variable.
//    (Make sure the external variable is outside the tested scope...)
//
//    If no external double pointer is specified at instantiation, the
//    result will automatically be printed to std::cout console.
//
//    If an std::string is passed at instantiation, the result will be
//    automatically printed to the console output using the string as
//    an instance name for easier evaluation.
//
//    Restrict the timer to a specific scope by wrapping code sections
//    in curly braces, possibly something like this:
//
//        double result = 0.0;
//        {
//            RCH::CodeTimer timer (&result);
//            
//            for (unsigned int step=0; step<LOOP_LIMIT; ++step)
//            {
//                /* Code to benchmark */
//            }
//        }
//
//    As soon as the timer in curly braces goes out of scope, the result
//    will be calculated and communicated to console or double pointer.
//
    /** Measures the execution time of a specific code scope */
    class CodeTimer
    {
    private:
        
        // Only used when instantiated without double pointer
        std::string instanceId = "CodeTimer";
        
        // Will contain the time stamps of start and stop events
        TIMER_VALUE started = 0;
        TIMER_VALUE stopped = 0;
        
        // If this is set, the result time will be stored here
        TIMER_VALUE* output = nullptr;
        
        // Creates a timestamp of "right now" as a double value
        const TIMER_VALUE now () const
        {
            // Fetch the nanosecond timestamp for this moment in time
            TIMER_STAMP point = TIMER_TCAST(TIMER_CLOCK::now());
            TIMER_VALUE count = point.time_since_epoch().count();
            
            // Return the correctly scaled timestamp
            return (1e-9 * count);
        }
        
        // Calculates and returns interval between start and stop events
        const TIMER_VALUE result () const
        {
            // Measure time interval between start and stop events
            const TIMER_VALUE difference = stopped - started;
            
            // Factor to scale interval to defined post-comma precision
            const TIMER_VALUE factor = std::pow(10.0, TIMER_PRECI);
            
            // Scale and round the interval to the defined precision
            return (std::round(difference * factor) / factor);
        }
        
    public:
        
        /** Instantiate without instance name or external result storage */
        CodeTimer ()
        {
            // Record the current point in time as the start timestamp
            started = now();
        }
        
        /** Instantiate with instance name for console output */
        CodeTimer (std::string InstanceId)
        {
            // Give this CodeTimer instance a name for easier evaluation
            instanceId = InstanceId;
            
            // Record the current point in time as the start timestamp
            started = now();
        }
        
        /** Instantiate with pointer to external double result variable */
        CodeTimer (TIMER_VALUE* ResultStorage)
        {
            // Store the pointer to the external variable
            output = ResultStorage;
            
            // Record the current point in time as the start timestamp
            started = now();
        }
        
        /** Destructor is called when the instance goes out of scope */
        ~CodeTimer ()
        {
            // Record the time of instance destruction as the stop event
            stopped = now();
            
            // If a pointer to an outside result variable was passed
            if (output != nullptr)
            {
                // Write the result value into the outside double variable
                *output = result();
                
                // Reset the pointer
                output = nullptr;
            }
            // If no pointer to an outside result value was passed
            else
            {
                // Output a string to the text console
                std::cout << instanceId << " finished in " << std::to_string(result()) << " ns" << std::endl;
            }
        }
        
    }; // end class RCH::CodeTimer
    
// ---- MODULE CODE ENDS ABOVE ---- //
} // end namespace RCH


// Just cleaning up
#undef TIMER_CLOCK
#undef TIMER_STAMP
#undef TIMER_VALUE
#undef TIMER_TCAST
#undef TIMER_PRECI


#endif // #ifndef RCH_CODETIMER_H
