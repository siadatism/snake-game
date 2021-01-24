#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <cstdlib>

enum Direction
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

inline static Direction opposite(Direction direction)
{
	switch (direction)
	{
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		case UP:
			return DOWN;
		case DOWN:
			return UP;
		default:
			throw std::string("opposite(): Invalid direction");
	}
}

enum Color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	WHITE
};

inline static int get_random(int min, int max)
{
	if (max < min)
		throw std::string("get_random(): Min is greater than max.");

	return rand() % (max - min + 1) + min;
}

struct Point
{
public:
	inline static Point get_random(Point min, Point max)
	{
		const int x = ::get_random(min.x, max.x);
		const int y = ::get_random(min.y, max.y);

		return Point(x, y);
	}

	Point(int x, int y)
	: x(x)
	, y(y)
	{}

	Point()
	: Point(0, 0)
	{}

	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	std::string to_string() const { return std::to_string(x) + " : " + std::to_string(y); }

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
	int get_value() const { return value;}
	char get_shape() const { return shape;}
	Color get_color() const { return color;}

private:
	const int value;
	const char shape;
	const Color color;
};

#endif
