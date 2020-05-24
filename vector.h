#pragma once

#include "redner.h"
#include <cmath>
#include <iostream>

template <typename T>
struct TVector2 {
    DEVICE TVector2() {}

    template <typename T2>
    DEVICE
    TVector2(T2 x, T2 y) : x(T(x)), y(T(y)) {}

    template <typename T2>
    DEVICE
    TVector2(const TVector2<T2> &v) : x(T(v.x)), y(T(v.y)) {}

    DEVICE T& operator[](int i) {
        return *(&x + i);
    }

    DEVICE T operator[](int i) const {
        return *(&x + i);
    }

    T x, y;
};

template <typename T>
struct TVector3 {
    DEVICE TVector3() {}

    template <typename T2>
    DEVICE
    TVector3(T2 x, T2 y, T2 z) : x(T(x)), y(T(y)), z(T(z)) {}

    template <typename T2>
    DEVICE
    TVector3(const TVector3<T2> &v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}

    DEVICE T& operator[](int i) {
        return *(&x + i);
    }

    DEVICE T operator[](int i) const {
        return *(&x + i);
    }

    T x, y, z;
};

template <typename T>
struct TVector4 {
    DEVICE TVector4() {}

    template <typename T2>
    DEVICE
    TVector4(T2 x, T2 y, T2 z, T2 w) : x(T(x)), y(T(y)), z(T(z)), w(T(w)) {}

    template <typename T2>
    DEVICE
    TVector4(const TVector4<T2> &v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}


    DEVICE T& operator[](int i) {
        return *(&x + i);
    }

    DEVICE T operator[](int i) const {
        return *(&x + i);
    }

    T x, y, z, w;
};

using Vector2f = TVector2<float>;
using Vector2d = TVector2<double>;
using Vector2i = TVector2<int>;
using Vector2 = TVector2<Real>;
using Vector3i = TVector3<int>;
using Vector3f = TVector3<float>;
using Vector3d = TVector3<double>;
using Vector3 = TVector3<Real>;
using Vector4f = TVector4<float>;
using Vector4d = TVector4<double>;
using Vector4 = TVector4<Real>;

template <typename T0, typename T1>
DEVICE
inline auto operator+(const TVector2<T0> &v0,
                      const TVector2<T1> &v1) {
    return TVector2<decltype(v0[0]+v1[0])>{
        v0[0] + v1[0], v0[1] + v1[1]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator+(const T0 &v0,
                      const TVector3<T1> &v1) {
    return TVector3<decltype(v0 + v1[0])>{
        v0 + v1[0], v0 + v1[1], v0 + v1[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator+(const TVector3<T0> &v0,
                      const T1 &v1) {
    return TVector3<decltype(v0[0] + v1)>{
        v0[0] + v1, v0[1] + v1, v0[2] + v1};
}

template <typename T0, typename T1>
DEVICE
inline auto operator+(const TVector3<T0> &v0,
                      const TVector3<T1> &v1) {
    return TVector3<decltype(v0[0] + v1[0])>{
        v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto& operator+=(TVector2<T0> &v0,
                        const TVector2<T1> &v1) {
    v0[0] += v1[0];
    v0[1] += v1[1];
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto& operator+=(TVector3<T0> &v0,
                        const TVector3<T1> &v1) {
    v0[0] += v1[0];
    v0[1] += v1[1];
    v0[2] += v1[2];
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto& operator+=(TVector3<T0> &v0,
                        const T1 &v1) {
    v0[0] += v1;
    v0[1] += v1;
    v0[2] += v1;
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto operator-(const T0 &v0,
                      const TVector3<T1> &v1) {
    return TVector3<decltype(v0 - v1[0])>{
        v0 - v1[0], v0 - v1[1], v0 - v1[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator-(const TVector2<T0> &v0,
                      const TVector2<T1> &v1) {
    return TVector2<decltype(v0[0] - v1[0])>{
        v0[0] - v1[0], v0[1] - v1[1]};
}

template <typename T>
DEVICE
inline auto operator-(const TVector3<T> &v) {
    return TVector3<T>{-v[0], -v[1], -v[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator-(const TVector3<T0> &v0,
                      const TVector3<T1> &v1) {
    return TVector3<decltype(v0[0] - v1[0])>{
        v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto& operator-=(TVector3<T0> &v0,
                        const TVector3<T1> &v1) {
    v0[0] -= v1[0];
    v0[1] -= v1[1];
    v0[2] -= v1[2];
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const TVector2<T0> &v0,
                      const T1 &s) {
    return TVector2<decltype(v0[0] * s)>{
        v0[0] * s, v0[1] * s};
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const T0 &s,
                      const TVector2<T1> &v0) {
    return TVector2<decltype(s * v0[0])>{
        s * v0[0], s * v0[1]};
}

template <typename T0, typename T1>
DEVICE
inline TVector2<T0> operator*=(TVector2<T0> &v0,
                               const T1 &s) {
    v0[0] *= s;
    v0[1] *= s;
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const TVector2<T0> &v0,
                      const TVector2<T1> &v1) {
    return TVector2<decltype(v0[0] * v1[0])>{
        v0[0] * v1[0], v0[1] * v1[1]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const TVector3<T0> &v0,
                      const T1 &s) {
    return TVector3<decltype(v0[0] * s)>{
        v0[0] * s, v0[1] * s, v0[2] * s};
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const T0 &s,
                      const TVector3<T1> &v0) {
    return TVector3<decltype(s * v0[0])>{
        s * v0[0], s * v0[1], s * v0[2]};
}

template <typename T0, typename T1>
DEVICE
inline TVector3<T0> operator*=(TVector3<T0> &v0,
                               const T1 &s) {
    v0[0] *= s;
    v0[1] *= s;
    v0[2] *= s;
    return v0;
}

template <typename T0, typename T1>
DEVICE
inline auto operator*(const TVector3<T0> &v0,
                      const TVector3<T1> &v1) {
    return TVector3<decltype(v0[0] * v1[0])>{
        v0[0] * v1[0], v0[1] * v1[1], v0[2] * v1[2]};
}

template <typename T0, typename T1>
DEVICE
inline auto operator/(const TVector2<T0> &v0,
                      const T1 &s) {
    auto inv_s = 1.f / s;
    return v0 * inv_s;
}

template <typename T0, typename T1>
DEVICE
inline auto operator/(const TVector3<T0> &v0,
                      const T1 &s) {
    auto inv_s = 1.f / s;
    return v0 * inv_s;
}

template <typename T>
DEVICE
inline TVector2<T> get_normal(const TVector2<T> &v) {
    return TVector2<T>{v.y, -v.x};
}

template <typename T>
DEVICE
inline T length_squared(const TVector2<T> &v0) {
    return square(v0[0]) + square(v0[1]);
}

template <typename T>
DEVICE
inline TVector3<T> d_length_squared(const TVector2<T> &v0, const T &d_l_sq) {
    //l_sq = square(v0[0]) + square(v0[1])
    return 2 * d_l_sq * v0;
}

template <typename T>
DEVICE
inline T length(const TVector2<T> &v0) {
    return sqrt(length_squared(v0));
}

template <typename T>
DEVICE
inline T length_squared(const TVector3<T> &v0) {
    return square(v0[0]) + square(v0[1]) + square(v0[2]);
}

template <typename T>
DEVICE
inline TVector3<T> d_length_squared(const TVector3<T> &v0, const T &d_l_sq) {
    //l_sq = square(v0[0]) + square(v0[1]) + square(v0[2])
    return 2 * d_l_sq * v0;
}

template <typename T>
DEVICE
inline T length(const TVector3<T> &v0) {
    return sqrt(length_squared(v0));
}

template <typename T>
DEVICE
inline TVector3<T> d_length(const TVector3<T> &v0, const T &d_l) {
    auto l_sq = length_squared(v0);
    auto l = sqrt(l_sq);
    auto d_l_sq = 0.5f * d_l / l;
    return d_length_squared(v0, d_l_sq);
}

template <typename T0, typename T1>
DEVICE
inline auto distance_squared(const TVector3<T0> &v0,
                     const TVector3<T1> &v1) {
    return length_squared(v1 - v0);
}

template <typename T0, typename T1>
DEVICE
inline auto distance(const TVector3<T0> &v0,
                     const TVector3<T1> &v1) {
    return length(v1 - v0);
}

template <typename T0, typename T1>
DEVICE
inline auto distance(const TVector2<T0> &v0,
                     const TVector2<T1> &v1) {
    return length(v1 - v0);
}

template <typename T>
DEVICE
inline TVector2<T> normalize(const TVector2<T> &v0) {
    return v0 / length(v0);
}

template <typename T>
DEVICE
inline TVector3<T> normalize(const TVector3<T> &v0) {
    return v0 / length(v0);
}

template <typename T>
DEVICE
inline TVector3<T> d_normalize(const TVector3<T> &v0, const TVector3<T> &d_n) {
    auto l = length(v0);
    auto n = v0 / l;
    auto d_v0 = d_n / l;
    auto d_l = -(d_n[0] * n[0] + d_n[1] * n[1] + d_n[2] * n[2]) / l;
    return d_v0 + d_length(v0, d_l);
}

template <typename T0, typename T1>
DEVICE
inline auto dot(const TVector3<T0> &v0, const TVector3<T1> &v1) {
    return v0[0] * v1[0] +
           v0[1] * v1[1] +
           v0[2] * v1[2];
}

template <typename T0, typename T1>
DEVICE
inline auto cross(const TVector3<T0> &v0, const TVector3<T1> &v1) {
    return TVector3<decltype(v0[1] * v1[2] - v0[2] * v1[1])>{
        v0[1] * v1[2] - v0[2] * v1[1],
        v0[2] * v1[0] - v0[0] * v1[2],
        v0[0] * v1[1] - v0[1] * v1[0]};
}

template <typename T>
DEVICE
inline void d_cross(const TVector3<T> &v0, const TVector3<T> &v1, const TVector3<T> &d_output,
                    TVector3<T> &d_v0, TVector3<T> &d_v1) {
    d_v0 += cross(v1, d_output);
    d_v1 += cross(d_output, v0);
}

template <typename T>
DEVICE
inline auto luminance(const TVector3<T> &v) {
    return 0.212671f * v[0] +
           0.715160f * v[1] +
           0.072169f * v[2];
}

template <typename T>
DEVICE
inline auto sum(const TVector2<T> &v) {
    return v[0] + v[1];
}

template <typename T>
DEVICE
inline auto sum(const TVector3<T> &v) {
    return v[0] + v[1] + v[2];
}

template <typename T>
DEVICE
void coordinate_system(const TVector3<T> &n, TVector3<T> &x, TVector3<T> &y) {
    if (n[2] < -1.f + 1e-6f) {
        x = TVector3<T>{T(0), T(-1), T(0)};
        y = TVector3<T>{T(-1), T(0), T(0)};
    } else {
        auto a = 1.f / (1.f + n[2]);
        auto b = -n[0] * n[1] * a;
        x = TVector3<T>{1.f - square(n[0]) * a, b, -n[0]};
        y = TVector3<T>{b, 1.f - square(n[1]) * a, -n[1]};
    }
}

template <typename T>
DEVICE
void d_coordinate_system(const TVector3<T> &n, const TVector3<T> &d_x, const TVector3<T> &d_y,
                         TVector3<T> &d_n) {
    if (n[2] < -1.f + 1e-6f) {
        //x = TVector3<T>{T(0), T(-1), T(0)};
        //y = TVector3<T>{T(-1), T(0), T(0)};
        // don't need to do anything
    } else {
        auto a = 1.f / (1.f + n[2]);
        // auto b = -n[0] * n[1] * a;
        // x = TVector3<T>{1.f - square(n[0]) * a, b, -n[0]}
        d_n[0] -= 2.f * n[0] * d_x[0] * a;
        auto d_a = -square(n[0]) * d_x[0];
        auto d_b = d_x[1];
        d_n[0] -= d_x[2];
        // y = TVector3<T>{b, 1.f - square(n[1]) * a, -n[1]}
        d_b += d_y[0];
        d_n[1] -= 2.f * d_y[1] * n[1] * a;
        d_a -= d_y[1] * square(n[1]);
        d_n[1] -= d_y[2];
        // b = -n[0] * n[1] * a
        d_n[0] -= d_b * n[1] * a;
        d_n[1] -= d_b * n[0] * a;
        d_a -= d_b * n[0] * n[1];
        // a = 1 / (1 + n[2])
        d_n[2] -= d_a * a / (1 + n[2]);
    }
}

DEVICE
inline bool isfinite(const Vector2 &v) {
    return std::isfinite(v.x) &&
           std::isfinite(v.y);
}

DEVICE
inline bool isfinite(const Vector3 &v) {
    return std::isfinite(v.x) &&
           std::isfinite(v.y) &&
           std::isfinite(v.z);
}

DEVICE
inline bool is_zero(const Vector3 &v) {
    return v.x == 0 && v.y == 0 && v.z == 0;
}

template <typename T>
DEVICE
inline TVector2<T> atomic_add(TVector2<T> &target, const TVector2<T> &source) {
    atomic_add(target[0], source[0]);
    atomic_add(target[1], source[1]);
    return target;
}

template <typename T>
DEVICE
inline TVector3<T> atomic_add(TVector3<T> &target, const TVector3<T> &source) {
    atomic_add(target[0], source[0]);
    atomic_add(target[1], source[1]);
    atomic_add(target[2], source[2]);
    return target;
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const TVector2<T> &v) {
    return os << "(" << v[0] << ", " << v[1] << ")";
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const TVector3<T> &v) {
    return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}
