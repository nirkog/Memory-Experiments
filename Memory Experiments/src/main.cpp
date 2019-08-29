#include <iostream>
#include <chrono>
#include <ctime>

#include "StackAllocator.h"
#include "PoolAllocator.h"

struct Color
{
	unsigned int r, g, b;
};

void printColor(Color color, const char* name)
{
	std::cout << name << ": " << color.r << ", " << color.g << ", " << color.b << std::endl;
}

int main()
{
	PoolAllocator allocator(3, sizeof(Color));

	Color* red = (Color*) allocator.GetChunk();
	red->r = 200;
	red->g = 20;
	red->b = 20;

	Color* green = (Color*) allocator.GetChunk();
	green->r = 20;
	green->g = 200;
	green->b = 20;

	allocator.FreeChunk(red);

	Color* blue = (Color*) allocator.GetChunk();
	blue->r = 20;
	blue->g = 25;
	blue->b = 225;

	red = (Color*) allocator.GetChunk();
	red->r = 220;
	red->g = 15;
	red->b = 25;

	printColor(*red, "Red");
	printColor(*green, "Green");
	printColor(*blue, "Blue");

	std::cin.get();

	return 0;
}