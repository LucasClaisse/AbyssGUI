#pragma once

#include "Matrix.hpp"

#include <utility>

template <typename T>
class Vector3 {
public:
    T x{0};
    T y{0};
    T z{0};

    Vector3<T>  operator+(const Vector3<T> &vec) const;
    Vector3<T>  operator-(const Vector3<T> &vec) const;
    Vector3<T>  operator*(const Vector3<T> &vec) const;
    Vector3<T>  operator/(const Vector3<T> &vec) const;
    Vector3<T> &operator+=(const Vector3<T> &vec);
    Vector3<T> &operator-=(const Vector3<T> &vec);
    Vector3<T> &operator*=(const Vector3<T> &vec);
    Vector3<T> &operator/=(const Vector3<T> &vec);
    Vector3<T>  operator+(T val) const;
    Vector3<T>  operator-(T val) const;
    Vector3<T>  operator*(T val) const;
    Vector3<T>  operator/(T val) const;
    Vector3<T> &operator+=(T val);
    Vector3<T> &operator-=(T val);
    Vector3<T> &operator*=(T val);
    Vector3<T> &operator/=(T val);

    T    length();
    T    distance(const Vector3<T> &vec);
	T	 dotProduct(const Vector3<T> &vec);
    auto toScreen(const Matrix<float, 4, 4> &matrix, const Vector3<int> &screen) -> std::pair<bool, Vector3<int>>;
};

template <typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T> &vec) const
{
    return {x + vec.x, y + vec.y, z + vec.z};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T> &vec) const
{
    return {x - vec.x, y - vec.y, z - vec.z};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator*(const Vector3<T> &vec) const
{
    return {x * vec.x, y * vec.y, z * vec.z};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator/(const Vector3<T> &vec) const
{
    return {x / vec.x, y / vec.y, z / vec.z};
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator/=(const Vector3<T> &vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

template <typename T>
inline Vector3<T> Vector3<T>::operator+(T val) const
{
    return {x + val, y + val, z + val};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator-(T val) const
{
    return {x - val, y - val, z - val};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator*(T val) const
{
    return {x * val, y * val, z * val};
}

template <typename T>
inline Vector3<T> Vector3<T>::operator/(T val) const
{
    return {x / val, y / val, z / val};
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator+=(T val)
{
    x += val;
    y += val;
    z += val;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator-=(T val)
{
    x -= val;
    y -= val;
    z -= val;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator*=(T val)
{
    x *= val;
    y *= val;
    z *= val;
    return *this;
}

template <typename T>
inline Vector3<T> &Vector3<T>::operator/=(T val)
{
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

template <typename T>
inline T Vector3<T>::length()
{
    return sqrt(x * x + y * y + z * z);
}

template <typename T>
inline T Vector3<T>::distance(const Vector3<T> &vec)
{
    return (*this - vec).length();
}

template <typename T>
inline T Vector3<T>::dotProduct(const Vector3<T> &vec)
{
	return x * vec.x + y * vec.y + z * vec.z;
}

template <typename T>
inline std::pair<bool, Vector3<int>> Vector3<T>::toScreen(const Matrix<float, 4, 4> &matrix, const Vector3<int> &screen)
{
    float fl{matrix.m[3][0] * x + matrix.m[3][1] * y + matrix.m[3][2] * z + matrix.m[3][3]};
    if (fl <= 0.001f)
        return {false, {}};

    float t{1.0f / fl};
    auto  result{std::pair<bool, Vector3<int>>{true, {}}};
    result.second.x = static_cast<int>((screen.x / 2) + (0.5f * ((matrix.m[0][0] * x + matrix.m[0][1] * y + matrix.m[0][2] * z + matrix.m[0][3]) * t) * screen.x + 0.5f));
    result.second.y = static_cast<int>((screen.y / 2) - (0.5f * ((matrix.m[1][0] * x + matrix.m[1][1] * y + matrix.m[1][2] * z + matrix.m[1][3]) * t) * screen.y + 0.5f));
    return result;
}
