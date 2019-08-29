#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t size)
	: m_Offset(0), m_Size(size)
{
	m_Start = (unsigned char*) malloc(m_Size);
}

void* StackAllocator::Allocate(size_t size)
{
	size_t* header = (size_t*)(m_Start + m_Offset);
	*header = size;

	m_Offset += sizeof(size_t) + size;

	if (m_Offset > m_Size)
	{
		m_Offset -= sizeof(size_t) + size;
		std::cout << "Allocator unable to allocate " << size << " bytes!" << std::endl;
		return nullptr;
	}

	return (void*) (m_Start + m_Offset - size);
}

void StackAllocator::Free(void* from)
{
	size_t* header = (size_t*)from;
	header--;
	size_t size = *header;

	m_Offset -= size - sizeof(size_t);
}

StackAllocator::~StackAllocator()
{
	free(m_Start);
}