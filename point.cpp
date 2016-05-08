#include <iostream>
#include <cstdio>
#include <cmath>

#include "point.h"

Point::Point(int _x, int _y)
{
	X = _x;
	Y = _y;
}

const Point operator+(const Point& left, const Point& right)
{
    return Point(left.X + right.X, left.Y + right.Y);
}

const Point operator-(const Point& left, const Point& right)
{
    return Point(left.X - right.X, left.Y - right.Y);
}

const Point operator*(const Point& left, const int& right)
{
    return Point(left.X * right, left.Y * right);
}

const Point operator/(const Point& left, const int& right)
{
    return Point(left.X / right, left.Y / right);
}

bool operator==(const Point& left, const Point& right)
{
    return ((left.X == right.X) && (left.Y == right.Y));
}

bool operator!=(const Point& left, const Point& right)
{
    return !((left.X == right.X) && (left.Y == right.Y));
}

int Point::get_x()
{
	return X;
}

int Point::get_y()
{
	return Y;
}

Point Point::move_up()
{
	return Point(X, Y - 1);
}

Point Point::move_down()
{
	return Point(X, Y + 1);
}

Point Point::move_right()
{
	return Point(X + 1, Y);
}

Point Point::move_left()
{
	return Point(X - 1, Y);
}
