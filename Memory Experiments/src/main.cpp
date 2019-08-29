#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

#include "StackAllocator.h"
#include "PoolAllocator.h"
#include "Array.h"
#include "List.h"

int main()
{
	List<int> list;
	list.PushBack(12);
	list.PushBack(20);
	list.PushFront(5);
	list.PushFront(14);
	list.Insert(2, -10);

	list.Print();

	std::cin.get();

	return 0;
}