#pragma once

#ifdef __NVCC__ 
    #define DEVICE __device__ __host__ 
#else
    #define DEVICE
#endif

#ifndef __NVCC__
    #include <cmath>
    namespace {
        inline float fmodf(float a, float b) {
            return std::fmod(a, b);
        }
        inline double fmod(double a, double b) {
            return std::fmod(a, b);
        }
    }
#endif

// We use Real for most of the internal computation.
// However, for PyTorch interfaces, Optix Prime and Embree queries
// we use float
using Real = double;

template <typename T>
DEVICE
inline T square(const T &x) {
    return x * x;
}

template <typename T>
DEVICE
inline T cubic(const T &x) {
    return x * x * x;
}

template <typename T>
DEVICE
inline T clamp(const T &v, const T &lo, const T &hi) {
    if (v < lo) return lo;
    else if (v > hi) return hi;
    else return v;
}

DEVICE
inline int modulo(int a, int b) {
    auto r = a % b;
    return (r < 0) ? r+b : r;
}

DEVICE
inline float modulo(float a, float b) {
    float r = ::fmodf(a, b);
    return (r < 0.0f) ? r+b : r;
}

DEVICE
inline double modulo(double a, double b) {
    double r = ::fmod(a, b);
    return (r < 0.0) ? r+b : r;
}


template <typename T>
DEVICE
inline T max(const T &a, const T &b) {
    return a > b ? a : b;
}

template <typename T>
DEVICE
inline T min(const T &a, const T &b) {
    return a < b ? a : b;
}

/// Return ceil(x/y) for integers x and y
inline int idiv_ceil( int x, int y ) {
  return (x + y-1) / y;
}

template <typename T>
DEVICE
inline void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
