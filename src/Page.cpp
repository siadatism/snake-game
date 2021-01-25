#include "Page.h"

#include <iostream>
#include <algorithm>

using namespace std;

Page::Page(const vector<Snake*>& snakes, Point margins)
: snakes(snakes)
, margins(margins)
, end_game(false)
{
}	 

void Page::add_random_food() 
{
	constexpr unsigned int MAX_TRY = 10;
	for (unsigned int i = 0; i < MAX_TRY; i++)
	{
		const Point random_point = Point::get_random(Point(1, 1), margins);
		
		if (!is_coordinates_snakes(random_point))
		{
			foods.push_back(Food(random_point, 1, '#', YELLOW));
			return;
		}
	}
	throw string("Page::add_random_food(): No empty space found");
}

list<Food>::iterator Page::find_food(Point point)
{
	return find(foods.begin(), foods.end(), point);
}

void Page::delete_food(const list<Food>::iterator& food)
{
	//foods.erase(foods.begin() + 1);
	foods.erase(food);
	add_random_food();
}

void Page::move_once()
{
	for (Snake* snake : snakes)
		snake->move(*this);
	
	for (Snake* snake : snakes)
		check_crash(snake);

	check_end_game();
}

void Page::erase_snake(Snake* snake)
{	
	for (unsigned int i = 0; i < snakes.size(); i++)
		if (snakes[i] == snake)
		{
			snakes.erase(snakes.begin() + i);
			break;
		}	
}

void Page::check_crash(Snake* snake)
{
	for (Snake* other : snakes)
	{
		if (other == snake)
		{
			if (snake->is_body(snake->get_head()))
			{
				cout << snake->get_name() << " self crash." << endl;
				erase_snake(snake);
				break;
			}
			continue;
		}

		if (other->get_head() == snake->get_head())
		{
			if (other->get_size() >= snake->get_size())
			{
				cout << snake->get_name() << " head-to-head to " << other->get_name() << endl;
				erase_snake(snake);
				break;
			}
		}

		if (other->is_body(snake->get_head()))
		{
			cout << snake->get_name() << " head-to-body to " << other->get_name() << endl;
			erase_snake(snake);
			break;
		}
	}
}

void Page::check_end_game()
{
	if (snakes.size() == 1)
	{
		message = snakes[0]->get_name() +  " WIN";
		end_game = true;
	}
	else if (snakes.size() == 0)
	{
		message = "EQAUL";
		end_game = true;
	}
}

bool Page::is_coordinates_snakes(Point point) const
{
	for (Snake* snake : snakes)
		if (point == snake->get_head() || snake->is_body(point))
			return true;
	return false;
}
