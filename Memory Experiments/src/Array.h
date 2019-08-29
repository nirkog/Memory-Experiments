#pragma once

#include <memory>

template<typename T>
class Array
{
public:
	Array(unsigned int initCapacity = 5)
		: m_Capacity(initCapacity), m_Count(0)
	{
		m_Array = (T*) malloc(sizeof(T) * m_Capacity);
		memset(m_Array, NULL, sizeof(T) * m_Capacity);
	}

	inline const unsigned int Capacity() const
	{
		return m_Capacity;
	}

	inline const unsigned int Count() const
	{
		return m_Count;
	}

	void Push(const T& value)
	{
		if (m_Count >= m_Capacity)
			Resize();

		m_Array[m_Count] = value;
		m_Count++;
	}

	const T& Get(const unsigned int& index)
	{
		if (index < m_Count)
			return m_Array[index];
		
		return NULL;
	}

	void Set(const unsigned int& index, const T& val)
	{
		if (index < m_Count)
			m_Array[index] = val;
	}

	const T& Pop()
	{
		const T val = m_Array[m_Count - 1];
		m_Array[m_Count - 1] = 0;
		m_Count--;
		return val;
	}

	~Array()
	{
		free(m_Array);
	}
private:
	void Resize()
	{
		m_Capacity *= 2;
		m_Array = (T*) realloc(m_Array, sizeof(T) * m_Capacity);
	}
private:
	unsigned int m_Capacity;
	unsigned int m_Count;
	T* m_Array;
};