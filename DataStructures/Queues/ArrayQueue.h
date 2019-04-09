#pragma once
#include <assert.h>
#include <iostream>

template <class Type>
class ArrayQueue
{
private:
	int queueFront, queueBack, maxQueueSize, count;
	Type *list;

public:
	ArrayQueue(int size = 10)
	{
		if (size <= 0)
		{
			std::cout << "Size of the queue must be positive!" << std::endl << "Creating an array of size 10" << std::endl;
			size = 10;
		}
		else
			maxQueueSize = size;
		queueBack = maxQueueSize-1;
		queueFront = 0;
		count = 0;
		list = new Type[maxQueueSize];
	}
	~ArrayQueue()
	{
		delete[]list;
	}
	bool isEmptyQueue()//return true if queue is empty.
	{
		return (count == 0);
	}
	bool isFullQueue()//return true if queue is full.
	{
		return (count == maxQueueSize);
	}
	bool initializeQueue()//Function to make queue to an empty state
	{
		queueFront = 0;
		queueBack = maxQueueSize - 1;
		count = 0;
	}
	Type front()//Function to return the first element of the queue
	{
		assert(isEmptyQueue() == true);
		return list[queueFront];
	}
	Type back()//Function to return the last element of thr queue
	{
		assert(isEmptyQueue() == true);
		return list[queueBack];
	}
	void addQueue(const Type &item)//Function to add item to the queue
	{
		if (isFullQueue() != true)
		{
			//***//
			queueBack = (queueBack + 1) % maxQueueSize;//use the mod operator to advance queueBack because the array is circular
			count++;
			list[queueBack] = item;
		}
		else
			std::cout << "Cannot add to a full queue" << std::endl;
	}
	void deleteQueue()//Function to remove the first element of the queue
	{
		if (isEmptyQueue() != true)
		{
			count--;
			queueFront = (queueFront + 1) % maxQueueSize; //use the mod operator to advance queueFront because the array is circular
		}
		else
			std::cout << "Cannot remove from an empty queue" << std::endl;
	}
};
