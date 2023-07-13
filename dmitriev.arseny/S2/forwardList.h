#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "forwardIterator.h"

namespace dmitriev
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ~ForwardList();

    void pushFront(const T& data);
    void pushFront(T&& data);

    const T& front() const;
    T& front();

    void popFront();

    ForwardIterator< T > beforBegin();
    ForwardIterator< T > begin();
    ForwardIterator< T > end();

  private:
    dmitriev::List< T >* fakeNode;
    //  size_t size;

  };
}

template< typename T >
dmitriev::ForwardList< T >::ForwardList():
  fakeNode(new dmitriev::List< T >{T(), nullptr})//����� �� ���� ��� ������
{}

template< typename T >
dmitriev::ForwardList< T >::~ForwardList()
{
  clear(fakeNode->otherList);
}

template< typename T >
void dmitriev::ForwardList< T >::pushFront(const T& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{data, fakeNode->otherList};
  fakeNode->otherList = newHead;
}

template< typename T >
void dmitriev::ForwardList< T >::pushFront(T&& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{std::move(data), fakeNode->otherList};
  fakeNode->otherList = newHead;
}

template< typename T >
const T& dmitriev::ForwardList< T >::front() const
{
  return fakeNode->otherList->data;
}

template< typename T >
T& dmitriev::ForwardList< T >::front()
{
  return fakeNode->otherList->data;
}

template< typename T >
void dmitriev::ForwardList< T >::popFront()
{
  dmitriev::List< T >* newHead = fakeNode->otherList->otherList;
  delete fakeNode->otherList;

  fakeNode->otherList = newHead;
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::beforBegin()
{
  return ForwardIterator< T >(fakeNode);
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::begin()
{
  return ForwardIterator< T >(fakeNode->otherList);
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::end()
{
  return ForwardIterator< T >(nullptr);
}

#endif
