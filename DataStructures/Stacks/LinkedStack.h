#pragma once
#include <iostream>
#include <assert.h>

template <class Type>
struct nodeType
{
	Type data;
	nodeType<Type> *link;
};

template <class Type>
class LinkedStack
{
private:
	nodeType<Type> *stackTop; //pointer to the stack

public:
	LinkedStack<Type>()//default constructor:Initializes the stack to an empty state when a stack object is declared
	{
		stackTop = NULL;
	}//default const.
	LinkedStack<Type>(const LinkedStack<Type> &otherStack)
	{
		copyStack(otherStack);
	}//copy const.
	~LinkedStack<Type>()
	{
		initializeStack();
	}//destructor
	/*• In a linked implementation of stacks, function isFullStack does not apply
	    – Logically, the stack is never full
  */
	bool isEmptyStack()
	{
		return (stackTop == NULL);
	}
	bool isFullStack()
	{
		return false;
	}

	/*reinitializes stack to an empty state
   – Must deallocate memory occupied by current element
   – Sets stackTop to NULL
 */
	void initializeStack()
	{
		nodeType<Type> *temp;//pointer to delete node
		while (stackTop != NULL)
		{
			temp = stackTop;
			delete temp;
			stackTop = stackTop->link;
		}
	}
	void push(const Type &item)
	{
		nodeType<Type> *newNode;
		newNode = new nodeType<Type>;
		newNode->data = item;
		newNode->link = stackTop;
		stackTop = newNode;
	}
	Type top() //return the top element of stack
	{
		assert(stackTop != NULL);//if stack is empty terminate the program
		return stackTop->data;
	}
	void pop() // removes the top element of the stack
	{
		nodeType<Type> *temp; //pointer to deallocate memory
		if (stackTop != NULL)
		{
			temp = stackTop;
			stackTop = stackTop->link;
			delete temp;
		}
		else
			std::cout << "Cannot remove from an empty stack." << std::endl;
	}
	void copyStack(const LinkedStack<Type> &otherStack)
	{
		nodeType<Type> *newNode, *current, *last;
		current = new nodeType<Type>;
		last = new nodeType<Type>;

		if (stackTop != NULL)// if stack is not empty make it empty
			initializeStack();
		if (otherStack.stackTop == NULL)
			stackTop = NULL;
		else
		{
			current = otherStack.stackTop; //set current to point to the stack to be copied
			stackTop = new nodeType<Type>; //Create the node
			stackTop->data = current->data; //copy the data
			stackTop->link = NULL;
			last = stackTop;
			current = current->link; //set current to point to the next node of to be copied stack
		}

		//copy the remaining stack
		while (current != NULL)
		{
			newNode = new nodeType<Type>;
			newNode->data = current->data;
			newNode->link = NULL;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}
	}
	LinkedStack<Type> operator = (const LinkedStack<Type> &otherStack)
	{
		if (this != &otherStack)//avoid self copy
			copyStack(otherStack);
		return *this;
	}
	void printStack()
	{
		nodeType<Type> *temp;//pointer to travers in the stack
		if (stackTop != NULL)
		{
			temp = stackTop;
			while (temp != NULL)
			{
				std::cout << temp->data << std::endl;
				temp = temp->link;
			}
		}
		else
			std::cout << "The stack is empty" << std::endl;
	}
};
