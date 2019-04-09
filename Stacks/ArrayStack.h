#pragma once
#include <iostream>
#include <cassert>
using namespace std;
template <class Type>
class Stack
{
private:
	Type *list;
	int maxSize;
	int topIndex;
public:
	//constructor 
	Stack<Type>(int mSize=100)
	{
		if (mSize <= 0)
		{
			cout << "Size of the array to hold the stack must "
				<< "be positive." << endl;
			cout << "Creating an array of size 100." << endl;

			maxSize = 100;
		}
		else
			maxSize = mSize;

		list = new Type[maxSize];
		topIndex = 0;
	}
	//destructor
	~Stack<Type>()
	{
		delete[] list;
	}
	//copy constructor
	Stack<Type>(const Stack<Type>& otherStack)
	{
		list = NULL;
		copyStack(otherStack);
	}
	bool isEmpty()
	{
		return (topIndex == 0);//return true if stack is empty
	}
	bool isFull()
	{
		return (maxSize == topIndex);
	}
	void push(const Type newItem)
	{
		if (isFull() != true)
		{
			list[topIndex] = newItem;
			topIndex++;
		}
		else
			cout << "Cannot add to a full stack." << endl;
	}
	void pop()
	{
		if (isEmpty() != true)
		{
			topIndex--;
		}
		else
			cout << "Cannot remove from an empty stack." << endl;
	}
	Type top()
	{
		if (isEmpty() != true)
			return list[topIndex - 1];
		else
			assert(1);
	}
	void copyStack(const Stack<Type> &otherStack)
	{
		delete[] list;
		maxSize = otherStack.maxSize;
		topIndex = otherStack.topIndex;

		list = new Type[maxSize];

		for (int i = 0;i < topIndex;i++)
			list[i] = otherStack[i];
	}
	Stack<Type> operator =(const Stack<Type> &otherStack)
	{
		if (this != &otherStack) //avoid self-copy
			copyStack(otherStack);
		return *this;
	}
};
