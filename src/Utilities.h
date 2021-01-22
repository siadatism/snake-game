#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <iostream>

// Key buttons character number
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

// Colors
#define C_RESET       "\033[0m"
#define C_WHITE       "\033[37m"     
#define C_RED         "\033[31m"     
#define C_GREEN       "\033[32m"     
#define C_YELLOW      "\033[33m"     
#define C_BLUE        "\033[34m"     

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

inline void colorized_print(std::string s, Color c)
{
	std::string code;

	switch (c)
	{
		case RED:
			code = C_RED;
			break;
		case GREEN:
			code = C_GREEN;
			break;
		case YELLOW:
			code = C_YELLOW;
			break;
		case BLUE:
			code = C_BLUE;
			break;
		case WHITE:
			code = C_WHITE;
			break;
		default:
			throw std::string("Unknown color.");
	}

	std::cout << code << s << C_RESET;
}

class Point
{
public:
	Point(int x, int y)
	: my_x(x)
	, my_y(y)
	{}

	Point()
	: Point(0, 0)
	{}

	int x() const { return my_x; }
	int y() const { return my_y; }

	bool operator==(const Point& other) const
	{
		return my_x == other.my_x && my_y == other.my_y;
	}

	std::string to_string() const { return std::to_string(my_x) + ":" + std::to_string(my_y); }

protected:
	const int my_x, my_y;
};

class Food : public Point
{
public:
	Food(Point point, int value, char shape, Color color)
	: point(point)
	, value(value)
	, shape(shape)
	, color(color)
	{}

	Point get_point() const { return point;}
	char get_shape() const { return shape;}
	int get_value() const { return value;}
	Color get_color() const { return color;}
	bool is_in(Point point) const { return point == this->point; }

private:
	const Point point;
	const int value;
	const char shape;
	const Color color;
};

#endif
