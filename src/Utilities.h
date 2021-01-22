#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <iostream>

enum Direction
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

enum Color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	WHITE
};

struct Point
{
public:
	Point(int x, int y)
	: x(x)
	, y(y)
	{}

	Point()
	: Point(0, 0)
	{}

	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	std::string to_string() const { return std::to_string(x) + ":" + std::to_string(y); }

	const int x, y;
};

class Food : public Point
{
public:
	Food(Point point, int value, char shape, Color color)
	: Point(point)
	, value(value)
	, shape(shape)
	, color(color)
	{}

	Point get_point() const { return *this;}
	char get_shape() const { return shape;}
	int get_value() const { return value;}
	Color get_color() const { return color;}
	bool is_in(Point point) const { return  *this == point; }

private:
	const int value;
	const char shape;
	const Color color;
};

#endif
