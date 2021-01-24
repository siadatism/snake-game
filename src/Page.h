#ifndef PAGE_H_
#define PAGE_H_

#include <string>
#include <vector>

#include "Utilities.h"
#include "Snake.h"

class Page
{
public:
	Page(const std::vector<Snake*>& snakes, const std::vector<Food*>& foods, Point margins);
	bool is_coordinates_snakes(Point point) const;
	Point get_margins() const { return margins; }
	std::vector<Snake*> get_snakes() const { return snakes; }
	std::vector<Food*> get_foods() const { return foods; }
	std::string get_message() const { return message; }
	void move_once();
	void delete_food(Food* food);
	void add_random_food(); 
	void check_crash(Snake* snake);
	void check_end_game();
	bool is_end_game() const { return end_game; }
	Food* food_at(Point point);
	void erase_snake(Snake* snake);

private:
	std::vector<Snake*> snakes;
	std::vector<Food*> foods;
	const Point margins;
	bool end_game;
	std::string message;
};

#endif
