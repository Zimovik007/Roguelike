#include <iostream>
#include <cstdio>
#include <cmath>

#include "point.h"

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

const Point operator+(const Point& left, const Point& right)
{
    return Point(left.x + right.x, left.y + right.y);
}

const Point operator-(const Point& left, const Point& right)
{
    return Point(left.x - right.x, left.y - right.y);
}

const Point operator*(const Point& left, const int& right)
{
    return Point(left.x * right, left.y * right);
}

const Point operator/(const Point& left, const int& right)
{
    return Point(left.x / right, left.y / right);
}

bool operator==(const Point& left, const Point& right)
{
    return ((left.x == right.x) && (left.y == right.y));
}

bool operator!=(const Point& left, const Point& right)
{
    return !((left.x == right.x) && (left.y == right.y));
}
