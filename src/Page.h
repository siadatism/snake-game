#ifndef PAGE_H_
#define PAGE_H_

#include <list>
#include <string>
#include <vector>

#include "Utilities.h"
#include "Snake.h"

class Page
{
public:
	Page(const std::vector<Snake*>& snakes, Point margins);
	bool is_coordinates_snakes(Point point) const;
	Point get_margins() const { return margins; }
	std::vector<Snake*> get_snakes() const { return snakes; }
	const std::list<Food>& get_foods() const { return foods; }
	std::string get_message() const { return message; }
	bool is_end_game() const { return end_game; }

	void move_once();
	std::list<Food>::iterator find_food(Point point);
	void delete_food(const std::list<Food>::iterator& food);
	void add_random_food(); 
	void check_crash(Snake* snake);
	void check_end_game();
	void erase_snake(Snake* snake);

private:
	std::vector<Snake*> snakes;
	//std::vector<Food> foods;
	std::list<Food> foods;
	const Point margins;
	bool end_game;
	std::string message;
};

#endif
