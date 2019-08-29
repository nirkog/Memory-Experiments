#pragma once

template<typename T>
struct Node
{
	Node<T>* next;
	Node<T>* prev;
	T value;
};

template<typename T>
class List
{
public:
	List()
		: m_Count(0), m_First(nullptr), m_Last(nullptr)
	{

	}

	inline const unsigned int Count() const { return m_Count; }

	inline Node<T>* GetFirst() const { return m_First; }
	inline Node<T>* GetLast() const { return m_Last; }

	void PushBack(const T& value)
	{
		Node<T>* node = (Node<T>*) malloc(sizeof(Node<T>));
		node->next = nullptr;
		node->value = value;

		if (m_Count == 0)
		{
			node->prev = nullptr;
			m_First = node;
		}
		else
		{
			node->prev = m_Last;
			m_Last->next = node;
		}

		m_Last = node;
		m_Count++;
	}

	void PushFront(const T& value)
	{
		Node<T>* node = (Node<T>*) malloc(sizeof(Node<T>));
		node->prev = nullptr;
		node->value = value;

		if (m_Count == 0)
		{
			node->prev = nullptr;
			m_Last = node;
		}
		else
		{
			node->next = m_First;
			m_First->prev = node;
		}

		m_First = node;
		m_Count++;
	}

	const T& PopBack()
	{
		if (m_Count == 0) return NULL;

		const T value = m_Last->value;

		if (m_Count == 1)
		{
			free(m_Last);
			m_Last = nullptr;
			m_First = nullptr;
		}
		else
		{
			m_Last->prev->next = nullptr;
			Node<T>* newLast = m_Last->prev;
			free(m_Last);
			m_Last = newLast;
		}

		m_Count--;

		return value;
	}

	const T& PopFront()
	{
		if (m_Count == 0) return NULL;

		const T value = m_First->value;

		if (m_Count == 1)
		{
			free(m_First);
			m_First = nullptr;
			m_Last = nullptr;
		}
		else
		{ 
			m_First->next->prev = nullptr;
			Node<T>* newFirst = m_First->next;
			free(m_First);
			m_First = newFirst;
		}

		m_Count--;

		return value;
	}

	void Set(const unsigned int& index, const T& value)
	{
		if (m_Count <= index) return;

		Node<T>* current = m_First;
		for (unsigned int i = 0; i < index; i++)
		{
			current = current->next;
		}

		current->value = value;
	}

	const T& Get(const unsigned int& index)
	{
		if (m_Count <= index) return NULL;

		Node<T>* current = m_First;
		for (unsigned int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current->value;
	}

	void Insert(const unsigned int& index, const T& value)
	{
		if (m_Count <= index || m_Count == 0) return;

		Node<T>* current = m_First;
		for(unsigned int i = 0; i < index - 1; i ++)
		{
			current = current->next;
		}

		Node<T>* node = (Node<T>*) malloc(sizeof(Node<T>));
		node->value = value;
		node->prev = current;
		node->next = current->next;

		current->next->prev = node;
		current->next = node;
	}

	void Print()
	{
		Node<T>* current = m_First;
		for (unsigned int i = 0; i < m_Count + 1; i++)
		{
			std::cout << current->value;
			if (i != m_Count) std::cout << " -> ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	~List()
	{
		Node<T>* next;
		Node<T>* current = m_First;
		while (current != nullptr)
		{
			next = current->next;
			free(current);
			current = next;
		}
	}
private:
	Node<T>* m_First;
	Node<T>* m_Last;
	unsigned int m_Count;
};