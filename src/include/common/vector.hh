#ifndef TANGLE_COMMON_VECTOR_TYPES_H
#define TANGLE_COMMON_VECTOR_TYPES_H

#include <cstdint>
#include <stdfloat>

namespace tangle::common {

struct int2 {
    int32_t x, z;
    bool operator==(const int2& other) const;
};

inline bool int2::operator==(const int2& other) const {
    return x == other.x && z == other.z;
}

struct int3 {
    int32_t x, y, z;
};

struct float2 {
    float x, y;
    bool operator==(const float2& other) const;
};

inline bool float2::operator==(const float2& other) const {
    return x == other.x && y == other.y;
}

struct float3 {
    float x, y, z;
};

struct double2 {
    double x, y;
    bool operator==(const double2& other) const;
};

inline bool double2::operator==(const double2& other) const {
    return x == other.x && y == other.y;
}

struct double3 {
    double x, y, z;
};

}

namespace std {

    using namespace tangle::common;

    template <typename T> struct hash;
    template <> struct hash<int2> {
        std::size_t operator()(const int2& t) const {
           return ((t.x << 19)|(t.x >> 13)) ^ t.z; 
        }
    };
}

#endif //TANGLE_COMMON_VECTOR_TYPES_H