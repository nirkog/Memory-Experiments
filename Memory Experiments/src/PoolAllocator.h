#pragma once

#include <memory>
#include <iostream>

class PoolAllocator
{
public:
	PoolAllocator(unsigned int chunkCount, unsigned int chunkSize);
	~PoolAllocator();

	void* GetChunk();
	void FreeChunk(void* chunk);
private:
	unsigned int m_ChunkSize, m_ChunkCount;
	void** m_Start;
	unsigned char* m_Block;
	bool m_Full;
};