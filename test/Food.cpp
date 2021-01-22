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

TEST(FoodFunctionality, is_in)
{
	Point point(2, 3);
	Food food(point, 1, '*', Color::RED);

    EXPECT_TRUE(food.is_in(point));
    EXPECT_FALSE(food.is_in(Point(3, 2)));
}
