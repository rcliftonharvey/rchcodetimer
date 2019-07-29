# RCH::CodeTimer
#### Scoped code execution timer in pure C++

-------------------------------------------------------------------------------------------------------

## Index

1. [Introduction](https://github.com/rcliftonharvey/rchcodetimer/blob/master/README.md#introduction)
2. [How to use](https://github.com/rcliftonharvey/rchcodetimer/blob/master/README.md#how-to-use)
3. [Example project](https://github.com/rcliftonharvey/rchcodetimer/blob/master/README.md#example-project)
4. [License](https://github.com/rcliftonharvey/rchcodetimer/blob/master/README.md#license)

-------------------------------------------------------------------------------------------------------

## Introduction 

This class implements a high-precision timer in pure C++, intended for quick execution time measurements of contained scopes of code.

This class was written with no dependencies, which means you can use it by itself and in any application, without being bound to any 3rd party frameworks.

I have done my best to comment the sources as much as I could (or made sense to me), so by reading through the headers you should get a good enough idea of what things can do or what you need to do with them.

The original repository for RCH::CodeTimer is right here:<br>
[https://github.com/rcliftonharvey/rchcodetimer]

-------------------------------------------------------------------------------------------------------

## How to use

Include the [header file](https://github.com/rcliftonharvey/rchcodetimer/tree/master/include/rchcodetimer.h) in your project.

Depending on your compiler and workspace settings, you will probably have to adjust the include path for this file. But once the include path is sorted out, this is the only line you should need:
```c++
#include "rchcodetimer.h"
```

To avoid possible collisions with other libraries you may be using in your projects, the CodeTimer class resides in the **RCH::** namespace by default. You're of course welcome to change the namespace in the [rchcodetimer.h](https://github.com/rcliftonharvey/rchcodetimer/blob/master/include/rchcodetimer.h#L37) main include.

You don't need to prepare anything, you can just instantiate CodeTimer classes on the fly, anywhere in your running code, when and where you need them.

The CodeTimer handles its own lifetime, so you don't have to (and you can't) start or stop it by hand. As soon as the timer goes out of scope, i.e. the scope it was instantiated in ends, the CodeTimer is destroyed and handles the result.

There are different ways to use the CodeTimer, they can be selected by the way a CodeTimer is instantiated:

* **Anonymous instance**<br>
   Sufficient if you're only interested in a single evaluation. Will not identify the CodeTimer but just print an anonymous message to std::cout when destroyed.   <br>
    ```c++
    RCH::CodeTimer timer;
    // --> "CodeTimer finished in xxxx ns"
    ```
  
* **Named instance**<br>
    Good when you want to compare several different scopes or stages of code. Will identify the CodeTimer in its std::cout message with the std::string name passed into the constructor.<br>
    ```c++
    RCH::CodeTimer timer ("instance name");
    // --> "instance name finished in xxxx ns"
    ```
    
* **Quiet instance**<br>
   If you don't like pre-formatted std::cout messages, you can spawn a quiet instance of CodeTimer by passing a pointer to an external double variable into its constructor. This will prevent any automatic messages to std::cout and give you the possibility to evaluate or further process timer results as you please.<br><br>
   **Important**: make sure the result variable is _outside_ of the timed scope!<br>
    ```c++
    double timedResult = 0.0; // Outside of timed scope
    {
      RCH::CodeTimer timer (&timedResult);
    }
    std::cout << "Completed in " << std::to_string(timedResult / 1000) << " µs" << std::endl;
    // --> "Completed in xxxx µs"
    ```
    <br>
Here's a quick example of how to use the CodeTimer inside a function and have the result reported to an outside variable:
   ```c++
   // Define a test function in e.g. a header
   void runTest (double* Output)
   {
      RCH::CodeTimer timer (Output); // Forward the variable pointer into the constructor
      
      for (unsigned int step=0; step<100000; ++step)
      {
         /* do something testworthy */
      }
      
   } // When runTest() ends, timer is destroyed and writes the measured time into testResult.
   
   // Create an external variable that will hold the measured time
   double testResult = 0.0; 
   
   // Run the test and pass the address to the testResult variable in
   runTest(&testResult);
   
   std::cout << "Test completed in " << std::to_string(testResult) << " ns" << std::endl;
   // --> "Test completed in xxxx ns"
   ```
    
<br>
And that's just about all there's to it.

-------------------------------------------------------------------------------------------------------

## Example project

For a real world example, check out the included [demo project](https://github.com/rcliftonharvey/rchcodetimer/blob/master/demo/demo.cpp). The project runs through a simple program and measures a few useless loops to demonstrate how to instantiate the CodeTimer and evaluate it. 

-------------------------------------------------------------------------------------------------------

## License

This source code is provided under the [MIT License](https://github.com/rcliftonharvey/rchcodetimer/tree/master/LICENSE).<br>
A copy of the MIT license in written form comes in the download of this library.

-------------------------------------------------------------------------------------------------------

Enjoy!

Rob Clifton-Harvey

