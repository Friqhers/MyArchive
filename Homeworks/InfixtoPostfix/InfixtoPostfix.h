#pragma once
#include <string>  
#include <iostream>
#include <assert.h>
using namespace std;

template <class Type>
struct nodeType
{
	Type data;
	nodeType<Type> *link;
};


//For stack operations in convertToPostfix funct.
template <class Type>
class LinkedListStack
{
private:
	nodeType<Type> *stackTop; //pointer to the stack

public:
	LinkedListStack<Type>()//default constructor:Initializes the stack to an empty state when a stack object is declared
	{
		stackTop = NULL;
	}//default const.
	LinkedListStack<Type>(const LinkedListStack<Type> &otherStack)
	{
		copyStack(otherStack);
	}//copy const.
	~LinkedListStack<Type>()
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
			stackTop = stackTop->link;
			delete temp;
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
	void copyStack(const LinkedListStack<Type> &otherStack)
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

		//copty the remaining stack
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
	LinkedListStack<Type> operator = (const LinkedListStack<Type> &otherStack)
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


//Returns precedence of operators
int opPrecedence(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

class infixToPostfix
{
public:
	void setInfix(string infX)
	{
		infx = infX;
	}
	void showInfix()
	{
		cout << "Infix Expression: " << infx << endl;
	}
	void showPostfix()
	{
		convertToPostfix();
		cout << "Postfix Expression: " << pfx << endl;
		pfx.erase();//Delete pfx after printing it.Becasue it will print previous line's pfx + present line's pfx
	}
private:
	void convertToPostfix()
	{
		LinkedListStack<char> stack;
		int length = infx.length();
		stack.push('L');

		for (int i = 0;i < length;i++)
		{
			//If sym is an operand, append sym to pfx
			if ((infx[i] >= 'a' && infx[i] <= 'z') || (infx[i] >= 'A' && infx[i] <= 'Z'))
			{
				pfx=pfx+infx[i];
			}
			//If sym is (, push sym into the stack.
			else if (infx[i] == '(')
			{
				stack.push('(');
			}
			//If sym is )
			else if (infx[i]==')')
			{
				//pop and append all of the symbols from the stack until the most recent left parentheses.
				while (stack.top() !='L' && stack.top() != '(')
				{
					char x = stack.top();
					stack.pop();
					pfx = pfx + x;
				}
				//Pop and discard the left parentheses.
				if (stack.top() == '(')
				{
					char c = stack.top();
					stack.pop();
				}
			}
			//If sym is an operator
			else
			{
				/*Pop and append all of the operators from the stack to pfx that are above the most recent left
                parentheses and have precedence greater than or equal to sym.*/
				while (stack.top() != '(' && opPrecedence(infx[i]) <= opPrecedence(stack.top()))
				{
					char x = stack.top();
					stack.pop();
					pfx = pfx + x;
				}
				//Push sym onto the stack.
				stack.push(infx[i]);
			}
		}
		//After processing infx, some operators might be left in the stack. Pop and append to pfx everything from the stack
		while (stack.top() != 'L')
		{
			char x = stack.top();
			stack.pop();
			pfx = pfx + x;
		}
		stack.initializeStack();//make the stack empty
	}
	string  infx;
	string  pfx;
};
