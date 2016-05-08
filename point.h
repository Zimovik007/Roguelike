#pragma once 

class Point
{
public:
	Point(int x, int y);
    friend const Point operator+(const Point& left, const Point& right);
    friend const Point operator-(const Point& left, const Point& right);
    friend const Point operator*(const Point& left, const int& right);
    friend const Point operator/(const Point& left, const int& right);
    friend bool operator==(const Point& left, const Point& right);
    friend bool operator!=(const Point& left, const Point& right);
    
    Point& operator=(const Point& right){
		x = right.x;
		y = right.y;
		return *this;
	}
private:
	int x, y;
};
