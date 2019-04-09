#pragma once
#include <assert.h>
#include <iostream>
template<class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class LinkedQueue
{
private:
	nodeType<Type> *front, *back;
public:
	LinkedQueue()
	{
		front = NULL;
		back = NULL;
	}
	~LinkedQueue()
	{
		nodeType<Type> *temp;
		while (front != NULL)
		{
			temp = front;
			front = front->link;
			delete temp;
		}
		back = NULL;
	}
	LinkedQueue(LinkedQueue<Type> &otherQ)
	{
		copyQueue(otherQ);
	}
	void copyQueue(LinkedQueue<Type> &otherQ)
	{
		if (otherQ.isEmptyQueue() != true)
		{
			initiliazeQueue();
			nodeType<Type> *temp;
			temp = otherQ.front;
			while (temp!=NULL)
			{
				addQueue(temp->info);
				temp = temp->link;
			}
		}
		else
		{
			initiliazeQueue();//make the queue empty
		}		
	}
	void printQueue()//front to back print
	{
		if (isEmptyQueue() != true)
		{
			nodeType<Type> *temp;
			temp = front;
			while (temp != NULL)
			{
				std::cout << temp->info << "-";
				temp = temp->link;
			}
			std::cout << std::endl;
		}
		else
			std::cout << "Cannot print empty queue" << std::endl;
	}
  
	/**********/
	//TODO: Copy Constructor , Overloading assignment operator(=).
	/*********/

	bool isEmptyQueue()//if front is NULL queue is empty
	{
		return (front == NULL);
	}
	bool isFullQueue()
	{
		return false;
	}
	void initiliazeQueue()
	{
		nodeType<Type> *temp;
		while (front != NULL)
		{
			temp = front;
			front = front->link;
			delete temp;
		}
		back = NULL;
	}
	void addQueue(const Type &item)
	{
		nodeType<Type> *newNode;
		newNode = new nodeType<Type>;
		newNode->info = item;
		newNode->link = NULL;
		if (front == NULL) //if the queue is empty
		{
			front = newNode;
			back = newNode;
		}
		else
		{
			back->link = newNode;
			back = newNode;
		}
	}
	void deleteQueue()
	{
		nodeType<Type> *temp;
		if (isEmptyQueue() != true)
		{
			temp = front;
			front = front->link;
			delete temp;
			if (front == NULL)//if after deletion the queue is empty 
			{
				back = NULL; //set back to NULL
			}
		}
		else
			std::cout << "Canno remove from and empty queue" << std::endl;;
	}
	Type returnFront()
	{
		assert(front!=NULL);
		return front->info;
	}
	Type returnBack()
	{
		assert(back != NULL);
		return back->info;
	}
};
