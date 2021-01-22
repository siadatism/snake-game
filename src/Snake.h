#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>
#include <string>

#include "Utilities.h"

class Page;

class Snake
{
public:
	inline static Point next_step(Point current_point, Direction direction, Point margins);

	Snake(Point head, int size, std::string name, char shape, Color color, Direction direction, Point margins);

	void move(Page* page);
	bool is_body(Point point) const;
	Point get_head() const { return head_and_body.front(); }

	int get_score() const { return score; }
	char get_shape() const { return shape; }
	int get_size() const { return head_and_body.size(); }
	Color get_color() const { return color; }
	Direction get_last_direction() const { return last_direction; }
	std::string get_name() const { return name; }
	
private:
	Direction make_decision(Page* page);

	std::deque<Point> head_and_body;
	int score;
	int increasing_length;
	const char shape;
	const std::string name;
	const Color color;
	Direction last_direction;
};

Point Snake::next_step(Point current, Direction direction, Point margins)
{
	int x = current.x;
	int y = current.y;
	switch (direction)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			throw std::string("Snake::next_step(): Invalid direction");
	}

	if (x <= 0)
		x = margins.x - 1;
	if (x >= margins.x)
		x = 1;
	if (y <= 0)
		y = margins.y - 1;
	if (y >= margins.y)
		y = 1;

	return Point(x, y);
}

#endif
