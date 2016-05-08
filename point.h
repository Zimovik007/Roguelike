#pragma once 

class Point
{
public:
	Point(int _x = 0, int _y = 0);
    friend const Point operator+(const Point& left, const Point& right);
    friend const Point operator-(const Point& left, const Point& right);
    friend const Point operator*(const Point& left, const int& right);
    friend const Point operator/(const Point& left, const int& right);
    friend bool operator==(const Point& left, const Point& right);
    friend bool operator!=(const Point& left, const Point& right);
    
    Point& operator=(const Point& right){
		X = right.X;
		Y = right.Y;
		return *this;
	}
	int get_x();
	int get_y();
	Point move_right();
	Point move_left();
	Point move_up();
	Point move_down();
private:
	int X, Y;
};
