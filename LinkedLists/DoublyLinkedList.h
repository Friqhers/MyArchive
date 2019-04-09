#pragma once
#include <iostream>
using namespace std;
template <class Type>
struct nodeType
{
	Type data;
	nodeType<Type> *next;
	nodeType<Type> *back;
};

template <class Type>
class doublyLinkedList
{
private:
	nodeType<Type> *first, *end;
	int count;
public:
	doublyLinkedList<Type>()
	{
		first = NULL;
		end = NULL;
		count = 0;
	}
	void insertLast(Type item)
	{
		nodeType<Type> *newNode;
		newNode = new nodeType<T>;

		newNode->data = item;
		newNode->next = NULL;
		newNode->back = NULL;

		if (first == NULL)//if list is empty
		{
			first = newNode;
			end = newNode;
			count++;
		}
		else//if list is not empty add new node after end
		{
			end->next = newNode;
			newNode->back = end;
			newNode->next = NULL;
			end = newNode;
			count++;
		}
	}
	void insertFirst(Type item)
	{
		nodeType<Type> *newNode;
		newNode = new nodeType<Type>;

		newNode->data = item;
		newNode->back = NULL;
		newNode->next = first;
		if (end == NULL)
			end = newNode;
		else
			first->back = newNode;
		head = newNode;
		count++;
	}
	void insertAt(Type item, int order)
	{
		if (order == 0)
			insertFirst(item);
		else if (order >= (count - 1))
			insertLast(item);
		else
		{
			nodeType<Type> *newNode;
			newNode = new nodeType < Type>;

			newNode->data = item;
			nodeType<Type> *cur = first;
			for (int i = 0;i < order - 1;i++, cur = cur->next);

			newNode->next = cur->next;
			cur->next->back = newNode;
			cur->next = newNode;
			newNode->back = cur;
		}
		count++;
	}
};
