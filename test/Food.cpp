#include <string>

#include <gtest/gtest.h>

#include "Utilities.h"

using namespace std;

TEST(FoodFunctionality, get_point)
{
	Point point(2, 3);
	Food food(point, 1, '*', Color::RED);

    EXPECT_EQ(point, food.get_point());
}

TEST(FoodFunctionality, equality_with_point)
{
	Point point(2, 3);
	Food food(point, 1, '*', Color::RED);

	EXPECT_TRUE(food == point);
	EXPECT_TRUE(point == food);
	EXPECT_TRUE(food == Point(2, 3));
	
	EXPECT_FALSE(food == Point(3, 3));
}
