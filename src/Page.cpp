#include "Page.h"

using namespace std;

Food* Page::food_at(Point point)
{
	for (Food* food : foods)
		if (food->is_in(point))
			return food;

	return nullptr;
}

Page::Page(const vector<Snake*>& snakes, const vector<Food*>& foods, Point margins)
: snakes(snakes)
, foods(foods)
, margins(margins)
, margins_shape('#')
, empty_shape('.')
, end_game(false)
{
}	 

void Page::delete_food(Food* food)
{
	for (int i = 0; i < foods.size(); i++)
		if (foods[i] == food)
		{
			foods.erase(foods.begin() + i);
			break;
		}
	add_food();
}

void Page::move_once()
{
	for (Snake* snake : snakes)
		snake->move(this);
	
	for (Snake* snake : snakes)
		check_crash(snake);

	check_end_game();
}

void Page::erase_snake(Snake* snake)
{	
	for (int i = 0; i < snakes.size(); i++)
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
				cout << snake->get_head().to_string() << endl;
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

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

void Page::print() const
{
	gotoxy(0, 0);

	for (Snake* snake : snakes)
		colorized_print(snake->get_name() + " : " + to_string(snake->get_score()) + "\n", snake->get_color());
	cout << "margins: " << margins.x() << " " << margins.y() << endl;

	for (int y = 0; y <= margins.y(); y++)
	{
		for (int x = 0; x <= margins.x(); x++)
		{
			bool print_empty = true;

			// Margins
			if (x == 0 or y == 0 or x == margins.x() or y == margins.y())
			{
				cout << margins_shape << " ";
				continue;
			}

			// Snakes
			for (Snake* snake : snakes)
			{
				if (Point(x, y) == snake->get_head())
				{
					colorized_print(string(1, snake->get_shape()), WHITE);
					cout << " ";
					print_empty = false;
					break;				
				}

				if (snake->is_body(Point(x, y)))
				{	
					colorized_print(string(1, snake->get_shape()), snake->get_color());
					cout << " ";
					print_empty = false;
					break;				
				}
			}
	
			// Foods
			for (Food* food : foods)
			{
				if (food->is_in(Point(x, y)))
				{
					colorized_print(string(1, food->get_shape()), food->get_color());
					cout << " ";
					print_empty = false;
					break;
				}
			}
	
			if (print_empty)
				cout << empty_shape << " ";
		}
		cout << endl;
	}
	cout << message << endl;
}

bool Page::is_coordinates_snakes(Point point)
{
	for (Snake* snake : snakes)
		if (point == snake->get_head() || snake->is_body(point))
			return true;
	return false;
}

void Page::add_food() 
{
	while (true)
	{
		int x_food = rand() % (margins.x() - 2) + 1;
		int y_food = rand() % (margins.y() - 2) + 1;
		Point point(x_food, y_food);
		
		if (!is_coordinates_snakes(point))
		{
			foods.push_back(new Food(point, 1, '#', YELLOW));
			break;
		}
	}				
}
