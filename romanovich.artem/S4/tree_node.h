#ifndef TREE_NODE_H
#define TREE_NODE_H
template< typename Key, typename Value >
struct TreeNode
{
  Key key;
  Value value;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
  TreeNode(const Key &key, const Value &value);
};
template< typename Key, typename Value >
TreeNode< Key, Value >::TreeNode(const Key &key, const Value &value):
  key(key),
  value(value),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
{
}
#endif
