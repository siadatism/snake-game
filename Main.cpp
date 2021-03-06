#include <ctime>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include <termios.h>

#include "Utilities.h"
#include "Snake.h"
#include "Page.h"

#define UNUSED(x) (void)(x)

// Key buttons character number
#define UP_ARROW 94
#define DOWN_ARROW 118
#define RIGHT_ARROW 62
#define LEFT_ARROW 60

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

// Colors codes
#define C_RESET       "\033[0m"
#define C_WHITE       "\033[37m"     
#define C_RED         "\033[31m"     
#define C_GREEN       "\033[32m"     
#define C_YELLOW      "\033[33m"     
#define C_BLUE        "\033[34m"     

using namespace std;

char direction_arrow(Direction direction)
{
	switch (direction)
	{
		case LEFT:
			return LEFT_ARROW;
		case RIGHT:
			return RIGHT_ARROW;
		case UP:
			return UP_ARROW;
		case DOWN:
			return DOWN_ARROW;
		default:
			throw std::string("direction_arrow(): Invalid direction");
	}
}

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

void print(const Page& page)
{
	// TODO Add 'system(cls)' mode for unit-tests.

	static bool first_time = true;
	if (first_time)
	{
		int result = system("clear");
		UNUSED(result);
		first_time = false;
	}

	gotoxy(0, 0);

	{
		const int result = system("setterm -cursor off");
		UNUSED(result);
	}

	const char margins_shape = '#';
	const char empty_shape = '.';

	for (Snake* snake : page.get_snakes())
		colorized_print(snake->get_name() + " : " + to_string(snake->get_score()) + "\n", snake->get_color());

	Point margins = page.get_margins();
	for (int y = 0; y <= margins.y; y++)
	{
		for (int x = 0; x <= margins.x; x++)
		{
			bool print_empty = true;

			// Margins
			if (x == 0 or y == 0 or x == margins.x or y == margins.y)
			{
				cout << margins_shape << " ";
				continue;
			}

			// Snakes
			for (Snake* snake : page.get_snakes())
			{
				if (Point(x, y) == snake->get_head())
				{
					//colorized_print(string(1, snake->get_shape()), WHITE);
					colorized_print(string(1, direction_arrow(snake->get_last_direction())), snake->get_color());
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
			for (Food food : page.get_foods())
			{
				if (food == Point(x, y))
				{
					colorized_print(string(1, food.get_shape()), food.get_color());
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
	cout << page.get_message() << endl;

	const int result = system("setterm -cursor on");
	UNUSED(result);
}

int main()
{
	srand(time(0));	

    // Settings
	Point margins(30 , 20);

	vector<Snake*> snakes;
	Snake S1(Point(5, 10), 4, "Soroosh", '0', BLUE, RIGHT, margins);
	Snake S2(Point(25, 10), 4, "Mehran", '0', GREEN, LEFT, margins);
	snakes.push_back(&S1);
	snakes.push_back(&S2);

	// Page setting
	Page page(snakes, margins);
	page.add_random_food();

	while (!page.is_end_game())
	{
		print(page);
		this_thread::sleep_for(chrono::milliseconds(10));
		page.move_once();
	}
}
