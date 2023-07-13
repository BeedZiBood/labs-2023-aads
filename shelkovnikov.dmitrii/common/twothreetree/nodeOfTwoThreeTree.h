#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#include "nodeOfTwoThreeTreeOne.h"
#include "nodeOfTwoThreeTreeTwo.h"
namespace dimkashelk
{
  namespace details
  {
    template< typename Key, typename Value >
    class NodeOfTwoThreeTreeOne;
    template< typename Key, typename Value >
    class NodeOfTwoThreeTreeTwo;
    template< typename Key, typename Value >
    class NodeOfTwoThreeTree
    {
    using node_type = NodeOfTwoThreeTree< Key, Value >;
    using data_type = std::pair< const Key, Value >;
    using node_one_type = NodeOfTwoThreeTreeOne< Key, Value >;
    using node_two_type = NodeOfTwoThreeTreeTwo< Key, Value >;
    public:
      NodeOfTwoThreeTree(const Key &k, const Value &v):
        data_(new node_one_type(k, v)),
        size_(1)
      {}
      NodeOfTwoThreeTree(const Key &k1, const Value &v1, const Key &k2, const Value &v2):
        data_(new node_two_type(k1, v1, k2, v2)),
        size_(2)
      {}
      ~NodeOfTwoThreeTree()
      {
        if (size_ == 1)
        {
          delete data_.one_;
        }
        else
        {
          delete data_.two_;
        }
      }
      unsigned getSize() const
      {
        return size_;
      }
      void insert(const Key &k, const Value &v)
      {
        updateNodes(data_.one_->data.first, data_.one_->data.second, k, v);
      }
      void insertFront(const Key &k, const Value &v)
      {
        updateNodes(k, v, data_.one_->data.first, data_.one_->data.second);
      }
      node_type *getFirstChild() const
      {
        if (size_ == 1)
        {
          return data_.one_->first;
        }
        else
        {
          return data_.two_->first;
        }
      }
      void setFirstChild(node_type *node)
      {
        if (size_ == 1)
        {
          data_.one_->first = node;
        }
        else
        {
          data_.two_->first = node;
        }
      }
      node_type *getSecondChild() const
      {
        if (size_ == 1)
        {
          return data_.one_->second;
        }
        else
        {
          return data_.two_->second;
        }
      }
      void setSecondChild(node_type *node)
      {
        if (size_ == 1)
        {
          data_.one_->second = node;
        }
        else
        {
          data_.two_->second = node;
        }
      }
      node_type *getThirdChild() const
      {
        if (size_ == 1)
        {
          return nullptr;
        }
        else
        {
          return data_.two_->third;
        }
      }
      void setThirdChild(node_type *node)
      {
        if (size_ == 1)
        {
          throw std::logic_error("No child!");
        }
        else
        {
          data_.two_->third = node;
        }
      }
      const data_type &getData(unsigned ind_) const
      {
        if (size_ == 1)
        {
          if (ind_ != 0)
          {
            throw std::out_of_range("No element");
          }
          return data_.one_->data;
        }
        else
        {
          if (ind_ > 1)
          {
            throw std::out_of_range("No element");
          }
          return data_.two_->data[ind_];
        }
      }
      data_type &getData(unsigned ind_)
      {
        return const_cast< data_type & >((static_cast< const node_type & >(*this)).getData(ind_));
      }
      node_type *getParent() const
      {
        if (size_ == 1)
        {
          return data_.one_->parent;
        }
        else
        {
          return data_.two_->parent;
        }
      }
      void setParent(node_type *node)
      {
        if (size_ == 1)
        {
          data_.one_->parent = node;
        }
        else
        {
          data_.two_->parent = node;
        }
      }
      node_type *getLastChild() const
      {
        if (size_ == 1)
        {
          return data_.one_->getLastChildren();
        }
        else
        {
          return data_.two_->getLastChildren();
        }
      }
      bool isList() const
      {
        return getFirstChild() == nullptr && getSecondChild() == nullptr && getThirdChild() == nullptr;
      }
      void removeFirst()
      {
        if (size_ == 1)
        {
          size_ = 0;
        }
        else
        {
          size_--;
          updateNodeRemove(1);
        }
      }
      void removeSecond()
      {
        if (size_ == 1)
        {
          throw std::logic_error("No element");
        }
        else
        {
          size_--;
          updateNodeRemove(0);
        }
      }
      void become2Node()
      {
        auto *copy_two = data_.two_;
        delete data_.two_;
        data_.one_ = new NodeOfTwoThreeTreeOne< Key, Value >(copy_two->data[0].first, copy_two->data[0].second);
        data_.one_->first = copy_two->first;
        data_.one_->second = copy_two->second;
        data_.one_->parent = copy_two->parent;
        size_ = 1;
      }
      NodeOfTwoThreeTreeOne< Key, Value > *getOneNode() const
      {
        return data_.one_;
      }
      NodeOfTwoThreeTreeTwo< Key, Value > *getTwoNode() const
      {
        return data_.two_;
      }
    private:
      union
      {
        NodeOfTwoThreeTreeOne< Key, Value > *one_;
        NodeOfTwoThreeTreeTwo< Key, Value > *two_;
      } data_;
      unsigned size_;
      void updateNodes(const Key &k1, const Value &v1, const Key &k2, const Value &v2)
      {
        if (size_ == 2)
        {
          throw std::logic_error("No node with size more 2");
        }
        auto *copy_one = data_.one_;
        delete data_.one_;
        data_.two_ = new NodeOfTwoThreeTreeTwo< Key, Value >(k1, v1, k2, v2);
        data_.two_first = copy_one->first;
        data_.two_->second = copy_one->second;
        data_.two_->parent = copy_one->parent;
        size_ = 2;
      }
      void updateNodeRemove(unsigned ind_)
      {
        auto *copy_two = data_.two_;
        delete data_.two_;
        auto *new_node = NodeOfTwoThreeTreeTwo< Key, Value >(copy_two->data[ind_].first, copy_two->data[ind_].second, Key(), Value());
        new_node->first = copy_two->first;
        new_node->second = copy_two->second;
        new_node->third = copy_two->third;
        new_node->parent = copy_two->parent;
        data_.two_ = new_node;
      }
    };
  }
}
#endif
