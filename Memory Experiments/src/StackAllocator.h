#pragma once

#include <memory>
#include <iostream>

#define DEFAULT_SIZE sizeof(unsigned char) * 1024

class StackAllocator
{
public:
	StackAllocator(size_t size = DEFAULT_SIZE);
	~StackAllocator();

	void* Allocate(size_t size);
	void Free(void* from);
private:
	unsigned char* m_Start;
	size_t m_Offset, m_Size;
};