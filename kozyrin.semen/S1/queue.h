#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"
#include <iostream>

namespace kozyrin {
  template< typename T >
  class Queue {
  public:
    Queue();
    Queue(const Queue< T >& origin);
    Queue(const Queue< T >&& origin) noexcept;
    Queue< T >& operator=(const Queue< T >& other);
    Queue< T >& operator=(Queue< T >&& other) noexcept;
    ~Queue();
    void push(T rhs);
    T& drop();
    void clearBin();
    bool isEmpty();
  private:
    node_t< T >* bin_ = nullptr;
    node_t< T >* head_ = nullptr;
    node_t< T >* tail_ = nullptr;
  };

  template< typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(head_)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T >& origin):
    head_(copy(origin.head_))
  {
    node_t< T >* curr = head_;
    while (curr->next_) {
      curr = curr->next_;
    }
    tail_ = curr;
  }

  template< typename T >
  Queue< T >::Queue(const Queue< T >&& origin) noexcept:
    head_(copy(origin.head_))
  {
    node_t< T >* curr = head_;
    while (curr->next_) {
      curr = curr->next_;
    }
    tail_ = curr;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue< T >& other)
  {
    if (this == other) {
      return *this;
    }
    head_ = copy(other.head_);
    node_t< T >* curr = head_;
    while (curr->next_) {
      curr = curr->next_;
    }
    tail_ = curr;
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    if (this == other) {
      return *this;
    }
    head_ = copy(other.head_);
    node_t< T >* curr = head_;
    while (curr->next_) {
      curr = curr->next_;
    }
    tail_ = curr;
    return *this;
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    while (head_ != nullptr) {
      node_t< T >* next = head_->next_;
      delete head_;
      head_ = next;
    }
    clearBin();
  }

  template< typename T >
  void Queue< T >::push(const T rhs)
  {
    node_t< T >* tail = new node_t< T >{rhs};
    if (head_ == nullptr) {
      head_ = tail;
      tail_ = tail;
      return;
    }
    tail_->next_ = tail;
    tail_ = tail;
  }

  template<typename T >
  T& Queue< T >::drop()
  {
    if (head_ == nullptr) {
      throw std::length_error("Nothing to drop");
    }

    node_t< T >* head = head_->next_;
    head_->next_ = bin_;
    bin_ = head_;
    head_ = head;
    return bin_->value_;
  }

  template< typename T >
  void Queue< T >::clearBin()
  {
    while (bin_ != nullptr) {
      node_t< T >* next = bin_->next_;
      delete bin_;
      bin_ = next;
    }
  }

  template< typename T >
  bool Queue< T >::isEmpty()
  {
    return head_ == nullptr;
  }
}

#endif
