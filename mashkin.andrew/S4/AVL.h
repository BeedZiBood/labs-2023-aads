#ifndef S4_AVL_H
#define S4_AVL_H
#include <functional>
#include <utility>
#include "AVL_iterator.h"
#include "AVL_reverse_iter.h"
#include "const_AVL_iterator.h"
#include "const_AVL_reverse_iter.h"
#include "tree.h"

namespace mashkin
{
  template< class K, class V, class C >
  class ConstAVLMapIter;
  template< class K, class V, class C >
  class AVLMapIter;

  template< class K, class V, class C >
  class ConstReverseAVLMapIter;
  template< class K, class V, class C >
  class ReverseAVLMapIter;

  template< class Key, class Value, class Comporator = std::less< Key > >
  class AVL
  {
  public:
    using v_type = std::pair< Key, Value >;
    using iter = AVLMapIter< Key, Value, Comporator >;
    using const_iter = ConstAVLMapIter< Key, Value, Comporator >;
    using riter = ReverseAVLMapIter< Key, Value, Comporator >;
    using const_riter = ConstReverseAVLMapIter< Key, Value, Comporator >;
    using tree = Tree< v_type >;
    AVL();
    AVL(const AVL& lhs);
    AVL(AVL&& rhs) noexcept;
    ~AVL();
    iter begin();
    iter end();
    const_iter cbegin();
    const_iter cend();
    riter rbegin();
    riter rend();
    const_riter crbegin();
    const_riter crend();

    iter insert(const v_type& val);
    iter insert(v_type&& val);
    template< class InputIter >
    iter insert(InputIter first, InputIter last);

    void clear();
    bool empty();

  private:
    void rotate_left(tree* node);
    void rotate_right(tree* node);
    void rotate_RightLeft(tree* node);
    void rotate_LeftRight(tree* node);
    size_t checkHeight(tree* head);
    size_t checkHeightImpl(tree* head, size_t height);
    tree* ins_impl(const v_type& data, tree* root, tree* before);
    void clear_impl(tree* toDel);
    tree* fake_;
    Comporator comp_;
  };
  template< class K, class V, class C >
  AVL< K, V, C >::AVL(AVL&& rhs) noexcept :
    fake_(rhs.fake_),
    comp_(rhs.comp_)
  {
  }

  template< class K, class V, class C >
  AVL< K, V, C >::AVL(const AVL& lhs):
    AVL()
  {
    insert(lhs.cbegin(), lhs.cend());
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_riter AVL< K, V, C >::crend()
  {
    return const_riter(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_riter AVL< K, V, C >::crbegin()
  {
    return const_riter((--cend()).node_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::riter AVL< K, V, C >::rend()
  {
    return riter(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::riter AVL< K, V, C >::rbegin()
  {
    return riter((--end()).node_);
  }

  template< class Key, class Value, class Comporator >
  AVL< Key, Value, Comporator >::AVL():
    fake_(static_cast< tree* >(::operator new(sizeof(tree)))),
    comp_()
  {
    fake_->left_ = nullptr;
    fake_->right_ = nullptr;
    fake_->parent_ = fake_;
  }

  template< class K, class V, class C >
  template< class InputIter >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(InputIter first, InputIter last)
  {
    while (first != last)
    {
      insert(*first);
      first++;
    }
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(v_type&& val)
  {
    return insert(val);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_LeftRight(tree* node)
  {
    rotate_left(node->right_);
    rotate_right(node->parent_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_RightLeft(tree* node)
  {
    rotate_right(node->left_);
    rotate_left(node->parent_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_right(tree* node)
  {
    auto var = node->parent_;
    var->left_ = node->right_;
    if (var->left_)
    {
      var->left_->parent_ = var;
    }
    node->parent_ = var->parent_;
    node->right_ = var;
    if (var->parent_->left_ == var)
    {
      var->parent_->left_ = node;
    }
    else if (var->parent_->right_ == var)
    {
      var->parent_->right_ = node;
    }
    else
    {
      var->parent_->parent_ = node;
    }
    var->parent_ = node;
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_left(tree* node)
  {
    auto var = node->parent_;
    var->right_ = node->left_;
    if (var->right_)
    {
      var->right_->parent_ = var;
    }
    node->parent_ = var->parent_;
    node->left_ = var;
    if (var->parent_->left_ == var)
    {
      var->parent_->left_ = node;
    }
    else if (var->parent_->right_ == var)
    {
      var->parent_->right_ = node;
    }
    else
    {
      var->parent_->parent_ = node;
    }
    var->parent_ = node;
  }

  template< class K, class V, class C >
  size_t AVL< K, V, C >::checkHeightImpl(tree* head, size_t height)
  {
    if (!head)
    {
      return height;
    }
    height++;
    size_t left = checkHeightImpl(head->left_, height);
    size_t right = checkHeightImpl(head->right_, height);
    height = left < right ? right : left;
    return height;
  }

  template< class K, class V, class C >
  size_t AVL< K, V, C >::checkHeight(tree* head)
  {
    size_t height = 0;
    return checkHeightImpl(head, height);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::tree* AVL< K, V, C >::ins_impl(const v_type& data, tree* root, tree* before)
  {
    if (!root)
    {
      return before;
    }
    before = root;
    root = ins_impl(data, comp_(data.first, root->data.first) ? root->left_ : root->right_, before);
    return root;
  }

  template< class K, class V, class C >
  bool AVL< K, V, C >::empty()
  {
    return fake_ == fake_->parent_;
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(const v_type& val)
  {
    iter res;
    if (empty())
    {
      fake_->parent_ = new tree{val, fake_, nullptr, nullptr};
    }
    else
    {
      auto newNode = ins_impl(val, fake_->parent_, fake_->parent_);
      if (comp_(val.first, newNode->data.first))
      {
        newNode->left_ = new tree{val, newNode, nullptr, nullptr};
      }
      else
      {
        newNode->right_ = new tree{val, newNode, nullptr, nullptr};
      }
      res = iter(newNode);
      while (newNode != fake_)
      {
        size_t left = checkHeight(newNode->left_);
        size_t right = checkHeight(newNode->right_);
        if (right - left == 2)
        {
          auto subTree = newNode->right_;
          auto subLeft = checkHeight(subTree->left_);
          auto subRight = checkHeight(subTree->right_);
          if (subLeft <= subRight)
          {
            rotate_left(subTree);
          }
          else
          {
            rotate_RightLeft(subTree);
          }
        }
        else if (left - right == 2)
        {
          auto subTree = newNode->left_;
          auto subLeft = checkHeight(subTree->left_);
          auto subRight = checkHeight(subTree->right_);
          if (subRight <= subLeft)
          {
            rotate_right(subTree);
          }
          else
          {
            rotate_LeftRight(subTree);
          }
        }
        newNode = newNode->parent_;
      }
    }
    return res;
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_iter AVL< K, V, C >::cend()
  {
    return ConstAVLMapIter< K, V, C >(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_iter AVL< K, V, C >::cbegin()
  {
    return const_iter((--crend()).node_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::end()
  {
    return AVLMapIter< K, V, C >(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::begin()
  {
    return iter((--rend()).node_);
  }

  template< class K, class V, class C >
  AVL< K, V, C >::~AVL()
  {
    clear();
    ::operator delete(fake_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::clear_impl(tree* toDel)
  {
    if (!toDel)
    {
      return;
    }
    clear_impl(toDel->left_);
    clear_impl(toDel->right_);
    delete toDel;
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::clear()
  {
    if (fake_ == fake_->parent_)
    {
      return;
    }
    clear_impl(fake_->parent_);
    fake_->parent_ = fake_;
  }
}
#endif
