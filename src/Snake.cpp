#include "Snake.h"
#include "Page.h"

using namespace std;

Snake::Snake(Point point, int size, string name, char shape, Color color, Direction direction, Point margins)
: score(0)
, increasing_length(0)
, shape(shape)
, name(name)
, color(color)
{
	head_and_body.push_back(point);
	for(int i = 1; i < size; i++)
	{
		Point temp = next_step(head_and_body.back(), direction, margins);
		cout << "Next part: " << temp.to_string() << endl;
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

void Snake::move(Page* page)
{
	Direction direction = make_decision(page);
	Point new_head = next_step(get_head(), direction, page->get_margins());

	//cout << get_name() << " " << "head: " << get_head().x() << ":" << get_head().y() <<
	//						" new_head: " << new_head.x() << ":" << new_head.y() << endl;

	// Check if food is eaten, increase length if so
	Food* food = page->food_at(new_head);
	if (food != nullptr)
	{
		increasing_length += food->get_value();
		score += food->get_value();
		page->delete_food(food);
	}

	// Move body
	head_and_body.push_front(new_head);
	if (increasing_length > 0)
		increasing_length--;
	else
		head_and_body.pop_back();
}

/*
Direction Page::determine_direction_move_bot_soroosh(Snake *snake)
{
	vector<Direction> candidate;
	for(int direction = Direction(LEFT); direction <= Direction(DOWN); direction++)
	{
		pair<int, int> next = snake->next_move_coordinates(Direction(direction));
		Snake s(next.first, next.second, 5, snake->get_name(), '+', RED, true);	
		Snake *virtual_snake = &s;

		//handle_crash_wall(virtual_snake);

		if(snake->is_coordinates(virtual_snake->get_x_head(), virtual_snake->get_y_head()))
			continue;

		if(check_crash_to_another_snakes_body(virtual_snake))
			continue;

		if(check_crash_to_another_snakes_head(virtual_snake))
			continue; 
		
		if(check_eat_food(virtual_snake))
			return Direction(direction);
		
		candidate.push_back(Direction(direction));
	}

	if(candidate.size() == 0)
		return Direction(UP);
	else	
		return candidate[rand()%candidate.size()];
}
*/

Direction Snake::make_decision(Page* page)
{
	// TODO
	//return UP;

	vector<Direction> candidate;
	for (int direction = Direction(LEFT); direction <= Direction(DOWN); direction++)
	{
		Point next = next_step(get_head(), Direction(direction), page->get_margins());	

		if(page->is_coordinates_snakes(next))
			continue;
		
		candidate.push_back(Direction(direction));
	}

	if (candidate.size() == 0)
		return Direction(UP);
	else	
		return candidate[rand() % candidate.size()];
}
