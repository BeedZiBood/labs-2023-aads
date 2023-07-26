#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <list.h>
#include "forwardIterator.h"
#include "constForwardIterator.h"
namespace fesenko
{
  template< typename T >
  class ForwardList
  {
   public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t &);
    ForwardList(this_t &&);
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    ~ForwardList();
    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    void clear() noexcept;
   private:
    List< T > *fakeNode_;
    List< T > *begin_;
    List< T > *end_;
    size_t size_;
  };

  template< typename T >
  ForwardList< T >::ForwardList():
    fakeNode_(static_cast< List< T > * >(::operator new (sizeof(List< T >)))),
    begin_(nullptr),
    end_(nullptr),
    size_(0)
  {
    fakeNode_->next = nullptr;
  }

  template< typename T >
  ForwardList< T >::ForwardList(const this_t &rhs):
    ForwardList()
  {
    copy(rhs);
  }

  template< typename T >
  ForwardList< T >::ForwardList(this_t &&rhs):
    ForwardList()
  {
    std::swap(fakeNode_, rhs.fakeNode_);
    std::swap(begin_, rhs.begin_);
    std::swap(end_, rhs.end_);
    std::swap(size_, rhs.size_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::before_begin() noexcept
  {
    return iterator(fakeNode_);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbefore_begin() const noexcept
  {
    return const_iterator(fakeNode_);
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    deleteList(begin_);
    end_ = nullptr;
    size_ = 0;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const this_t &rhs)
  {
    if (std::addressof(rhs) != this) {
      clear();
      copy(rhs);
    }
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(this_t &&rhs)
  {
    if (std::addressof(rhs) != this) {
      clear();
      std::swap(fakeNode_, rhs.fakeNode_);
      std::swap(begin_, rhs.begin_);
      std::swap(end_, rhs.end_);
      std::swap(size_, rhs.size_);
    }
    return *this;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fakeNode_);
  }
}
#endif
