#ifndef STACK_H
#define STACK_H

#include "list.h"
#include <iomanip>

template< typename T >
class Stack
{
public:
	Stack();
	~Stack();

	void push(T rhs);
	void popBack();
	T getTopData();

	T unsafeGetTopAndPop();

	bool isEmpty();

private:
	List< T >* top;
};

template< typename T >
Stack< T >::Stack() :
	top(nullptr)
{

}

template< typename T >
Stack<T>::~Stack()
{

}

template< typename T >
void Stack<T>::push(T rhs)
{
	List< T >* newTop = new List< T >(rhs, top);
	top = newTop;
}

template< typename T >
void Stack< T >::popBack()
{
	if (top == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	List< T >* currentList = top;
	top = top->otherList;

	delete currentList;
}

template< typename T >
T Stack< T >::getTopData()
{
	if (top == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	return top->data;
}

template< typename T >
T Stack< T >::unsafeGetTopAndPop()
{
	T currentData = getTopData();
	popBack();

	return currentData;
}

template< typename T >
bool Stack< T >::isEmpty()
{
	return top == nullptr;
}

#endif
