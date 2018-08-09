#ifndef GLOBALS_H
#define GLOBALS_H

#include <cassert>

#define DEG_TO_RAD 0.017453292519943295769236907684886127134428718885417254560f
#define RAD_TO_DEG 57.29577951308232087679815481410517033240547246656432155235f
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f

#define APPLOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }

// Configuration from JSON file
#define CONFIGFILE "config.json"

// Ray tracing defines
#define DIELECTRIC_R_COEFFICIENT_PROBABILITY 1
#define GAMMA_CORRECTION 1

// Optimization
#define USE_OOP 1
#define USE_C_ARRAYS 1

// Parallelization
#define USE_OPENMP_PIXEL_LOOP 0

#define USE_CUDA 0
#if USE_CUDA
	#define USE_C_ARRAYS 1
	#define CUDA_DEVICE_CALLABLE __device__
	#define CUDA_HOST_CALLABLE __host__
	#define CUDA_KERNEL	__global__
#else
	#define CUDA_DEVICE_CALLABLE
	#define CUDA_HOST_CALLABLE
	#define CUDA_KERNEL
#endif // USE_CUDA

#if USE_C_ARRAYS
	#define USE_OOP 0
#endif // USE_C_ARRAYS

#endif // !GLOBALS_H