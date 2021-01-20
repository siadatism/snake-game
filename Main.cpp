#include <ctime>
#include <deque>
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

// Sleep time between moves
#define EASY 300
#define MEDIUM 200
#define HARD 100

using namespace std;

int main()
{
	system("clear"); 
	srand(time(0));	

    // Setting
	int LEVEL = EASY;
	Point margins(30 , 20);

	vector<Snake*> snakes;
	vector<Food*> foods;

	Snake S1(Point(22, 3), 5, "Soroosh", '0', BLUE, LEFT, margins);
	Snake S2(Point(3, 3), 5, "Mehran", '0', GREEN, LEFT, margins);
	snakes.push_back(&S1);
	snakes.push_back(&S2);

	Food f(Point(15, 10), 1, '1', YELLOW);
	foods.push_back(&f);

	// Page setting
	Page page(snakes, foods, margins);

	while (!page.is_end_game())
	{
		page.print();
		this_thread::sleep_for(chrono::milliseconds(20));
		page.move_once();

		//this_thread::sleep_for(chrono::seconds(2));
		//S1.move(&page);
	}
}
