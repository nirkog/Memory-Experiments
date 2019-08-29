#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(unsigned int chunkCount, unsigned int chunkSize)
	: m_ChunkCount(chunkCount), m_ChunkSize(chunkSize), m_Full(false)
{
	if (m_ChunkSize < sizeof(void*))
		std::cout << "PROBLEM!" << std::endl;

	m_Block = (unsigned char*) malloc(m_ChunkSize * m_ChunkCount);
	unsigned char* counter = m_Block;

	memset(m_Block, NULL, m_ChunkSize * m_ChunkCount);

	for (unsigned int i = 0; i < m_ChunkCount - 1; i++)
	{
		void** pointer = (void**) counter;
		*pointer = counter + m_ChunkSize;
		counter += m_ChunkSize;

		//std::cout << pointer << ", " << *pointer << std::endl;
	}

	m_Start = (void**) m_Block;
}

void* PoolAllocator::GetChunk()
{
	void* chunk = m_Start;

	if (*m_Start == NULL)
	{
		m_Full = true;
	}
	else
	{
		m_Start = (void**) *m_Start;
	}

	//std::cout << m_Start << ", " << *m_Start << std::endl;

	return chunk;
}

void PoolAllocator::FreeChunk(void* chunk)
{
	if(!m_Full)
	{
		memset(chunk, NULL, m_ChunkSize); // OPTIONAL!
		void** pointer = (void**) chunk;
		*pointer = m_Start;
		m_Start = (void**) chunk;

		//std::cout << m_Start << ", " << *m_Start << std::endl;
	}
	else
	{
		memset(chunk, NULL, m_ChunkSize); // OPTIONAL!
		m_Start = (void**) chunk;
		m_Full = false;
	}
}

PoolAllocator::~PoolAllocator()
{
	free(m_Block);
}