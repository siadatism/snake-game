#include "Snake.h"
#include "Page.h"

using namespace std;

Snake::Snake(Point head_start_point, unsigned int size, const string& name, char shape, Color color,
		Direction direction, Point margins)
: score(0)
, increasing_length(0)
, shape(shape)
, name(name)
, color(color)
, last_direction(direction)
{
	// Add head
	head_and_body.push_back(head_start_point);

	// Add body
	for (unsigned int i = 1; i < size; i++)
	{
		Point temp = next_step(head_and_body.back(), opposite(direction), margins);
		head_and_body.push_back(temp);
	}
}

bool Snake::is_body(Point point) const 
{
	bool head_skipped = false;
	for (const Point& body_part : head_and_body)
	{
		if (!head_skipped)
		{
			head_skipped = true;
			continue;
		}

		if (body_part == point)
			return true;
	}
	return false;
}

void Snake::move(Page& page)
{
	last_direction = make_decision(page);
	Point new_head = next_step(get_head(), last_direction, page.get_margins());

	// Check if food is eaten, increase length if so
	list<Food>::iterator found_food = page.find_food(new_head);
	if (found_food != page.get_foods().end())
	{
		increasing_length += found_food->get_value();
		score += found_food->get_value();
		page.delete_food(found_food);
	}

	// Move body
	head_and_body.push_front(new_head);
	if (increasing_length > 0)
		increasing_length--;
	else
		head_and_body.pop_back();
}

Direction Snake::make_decision(const Page& page)
{
	// TODO
	//return UP;

	vector<Direction> candidate;
	for (int direction = Direction(LEFT); direction <= Direction(DOWN); direction++)
	{
		Point next = next_step(get_head(), Direction(direction), page.get_margins());

		if(page.is_coordinates_snakes(next))
			continue;
		
		candidate.push_back(Direction(direction));
	}

	if (candidate.size() == 0)
		return Direction(UP);
	else	
		return candidate[rand() % candidate.size()];
}
