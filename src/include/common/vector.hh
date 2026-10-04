#ifndef TANGLE_COMMON_VECTOR_TYPES_H
#define TANGLE_COMMON_VECTOR_TYPES_H

#include <cstdint>
#include <stdfloat>

namespace tangle::common {

struct int2 {
    int32_t x, z;
};

struct int3 {
    int32_t x, y, z;
};

struct float2 {
#ifdef __STDCPP_FLOAT32_T__
    float32_t x, y; 
#else
    float x, y;
#endif
};

struct float3 {
#ifdef __STDCPP_FLOAT32_T__
    float32_t x, y, z; 
#else
    float x, y, z;
#endif
};

struct double2 {
#ifdef __STDCPP_FLOAT64_T__
    float64_t x, y; 
#else
    double x, y;
#endif
};

struct double3 {
#ifdef __STDCPP_FLOAT64_T__
    float64_t x, y, z;
#else
    double x, y, z;
#endif
};

}

namespace std {

    using namespace tangle::common;

    template <typename T> struct hash;
    template <> struct hash<int2> {
        std::size_t operator()(const int2& t) {
           return ((t.x << 19)|(t.x >> 13)) ^ t.z; 
        }
    };
}

#endif //TANGLE_COMMON_VECTOR_TYPES_H