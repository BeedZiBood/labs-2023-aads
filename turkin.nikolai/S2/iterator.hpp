#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include <utility>
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class Iterator
  {
    public:
      friend class ForwardList< T >;
      using List = OneWayNode< T > *;
      Iterator();
      explicit Iterator(List rhs);
      Iterator(const Iterator< T > & rhs);
      Iterator(Iterator< T > && rhs);
      Iterator< T > & operator=(const Iterator< T > & rhs);
      Iterator< T > & operator=(Iterator< T > && rhs);
      ~Iterator() = delete;
      Iterator< T > & operator++();
      Iterator< T > operator++(int);
      T & operator*();
      T * operator->();
      bool operator==(const Iterator< T > & rhs) const;
      bool operator!=(const Iterator< T > & rhs) const;
    private:
      List cur_;
  };
}

template< typename T >
turkin::Iterator< T >::Iterator():
  cur_(nullptr)
{}

template< typename T >
turkin::Iterator< T >::Iterator(List rhs):
  cur_(rhs)
{}

template< typename T >
turkin::Iterator< T >::Iterator(const Iterator< T > & rhs):
  cur_(new List {rhs.cur_->data, rhs.cur_->next})
{}

template< typename T >
turkin::Iterator< T >::Iterator(Iterator< T > && rhs):
  cur_(rhs.cur_)
{
  rhs.cur_ = nullptr;
}

template< typename T >
turkin::Iterator< T > & turkin::Iterator< T >::operator=(const Iterator< T > & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  delete cur_;
  cur_ = new List {rhs.cur_->data, rhs.cur_->next};
  return * this;
}

template< typename T >
turkin::Iterator< T > & turkin::Iterator< T >::operator=(Iterator< T > && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  delete cur_;
  cur_ = rhs.cur_;
  rhs.cur_ = nullptr;
  return * this;
}

template< typename T >
turkin::Iterator< T > & turkin::Iterator< T >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T >
turkin::Iterator< T > turkin::Iterator< T >::operator++(int)
{
  assert(cur_ != nullptr);
  Iterator< T > result(* this);
  ++(* this);
  return result;
}

template< typename T >
T & turkin::Iterator< T >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
T * turkin::Iterator< T >::operator->()
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T >
bool turkin::Iterator< T >::operator==(const Iterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::Iterator< T >::operator!=(const Iterator< T > & rhs) const
{
  return !(rhs == * this);
}

#endif
