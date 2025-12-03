#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cmath>

std::string strip(const std::string &input)
{
    auto start_it = input.begin();
    auto end_it = input.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

struct Point2d
{
    Point2d() : x(0), y(0) {}
    Point2d(int x_, int y_) : x(x_), y(y_) {}
    int x;
    int y;
    int abs() { return std::abs(x) + std::abs(y); }
    int abs() const { return std::abs(x) + std::abs(y); }
    int32_t manhattan()
    {
        return std::abs(x) + std::abs(y);
    }

    Point2d operator+(const Point2d &a) const { return Point2d(a.x + x, a.y + y); }
    Point2d &operator+=(const Point2d &b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    Point2d operator*(const int32_t &a) const { return Point2d(a * x, a * y); }
    Point2d &operator*=(const int32_t &b)
    {
        x *= b;
        y *= b;
        return *this;
    }

    Point2d operator-(const Point2d &a) const { return Point2d(x - a.x, y - a.y); }
    Point2d &operator-=(const Point2d &b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    Point2d operator/(const int div) const { return Point2d(x / div, y / div); }
    Point2d &operator/=(const int div)
    {
        x /= div;
        y /= div;
        return *this;
    }

    int &operator[](int index)
    {
        if (index == 0)
            return x;
        return y;
    }

    bool operator==(const Point2d &a) { return x == a.x && y == a.y; }
};
bool operator==(const Point2d &a, const Point2d &b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point2d &a, const Point2d &b) { return a.x < b.x ? true : (b.x < a.x ? false : (a.y < b.y ? true : false)); }

bool operator>(const Point2d &a, const Point2d &b) { return b < a; }
bool operator!=(const Point2d &a, const Point2d &b) { return !(a == b); }
bool operator<=(const Point2d &a, const Point2d &b) { return !(b < a); }
bool operator>=(const Point2d &a, const Point2d &b) { return !(a < b); }

struct Point3d
{

    Point3d() : x(0), y(0), z(0) {};
    Point3d(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {};
    int x;
    int y;
    int z;

    double length()
    {
        double l2 = x * x + y * y + z * z;
        return sqrt(l2);
    }

    int32_t manhattan()
    {
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    Point3d &operator+=(const Point3d &p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }
    Point3d &operator-=(const Point3d &p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }
    Point3d &operator-=(const int32_t &p)
    {
        x *= p;
        y *= p;
        z *= p;
        return *this;
    }

    Point3d cross(const Point3d &b)
    {
        Point3d result;

        result.x = y * b.z - z * b.y;
        result.y = z * b.x - x * b.z;
        result.z = x * b.y - y * b.x;

        return result;
    }

    int &operator[](int index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        return z;
    }

    int operator[](int index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        return z;
    }

    Point3d operator-() const
    {
        return Point3d(-x, -y, -z);
    }
};

bool operator==(const Point3d &a, const Point3d &b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
bool operator<(const Point3d &a, const Point3d &b) { return a.z != b.z ? a.z < b.z : a.x != b.x ? a.x < b.x
                                                                                                : a.y < b.y; }

bool operator>(const Point3d &a, const Point3d &b) { return b < a; }
bool operator!=(const Point3d &a, const Point3d &b) { return !(a == b); }
bool operator<=(const Point3d &a, const Point3d &b) { return !(b < a); }
bool operator>=(const Point3d &a, const Point3d &b) { return !(a < b); }

Point3d operator+(const Point3d &a, const Point3d &b) { return Point3d(a.x + b.x, a.y + b.y, a.z + b.z); }
Point3d operator-(const Point3d &a, const Point3d &b) { return Point3d(a.x - b.x, a.y - b.y, a.z - b.z); }
Point3d operator*(const Point3d &a, const int32_t &b) { return Point3d(a.x * b, a.y * b, a.z * b); }

int operator*(const Point3d &a, const Point3d &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct Quaternion
{

    Quaternion() : x(0), y(0), z(0), w(0) {};
    Quaternion(int x_, int y_, int z_, int w_) : x(x_), y(y_), z(z_), w(w_) {};
    int x;
    int y;
    int z;
    int w;

    Quaternion &operator+=(const Quaternion &b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    int &operator[](int index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        return w;
    }

    int operator[](int index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        return w;
    }
};
bool operator==(const Quaternion &a, const Quaternion &b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
bool operator<(const Quaternion &a, const Quaternion &b) { return a.z != b.z ? a.z < b.z : a.x != b.x ? a.x < b.x
                                                                                       : a.y != b.y   ? a.y < b.y
                                                                                                      : a.w < b.w; }

bool operator>(const Quaternion &a, const Quaternion &b) { return b < a; }
bool operator!=(const Quaternion &a, const Quaternion &b) { return !(a == b); }
bool operator<=(const Quaternion &a, const Quaternion &b) { return !(b < a); }
bool operator>=(const Quaternion &a, const Quaternion &b) { return !(a < b); }

Quaternion operator+(const Quaternion &a, const Quaternion &b) { return Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
Quaternion operator-(const Quaternion &a, const Quaternion &b) { return Quaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

long long part1_solution_;
long long part2_solution_;

void printSolutionPart1()
{
    std::cout << "Part 1 solution is: " << part1_solution_ << "✅" << std::endl;
}

void printSolutionPart2()
{
    std::cout << "Part 2 solution is: " << part2_solution_ << "✅" << std::endl;
}

#endif