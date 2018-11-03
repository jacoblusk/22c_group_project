/*+===================================================================
File:      BINARYSEARCHTREE.H
Summary:   Contains an interface for a Binary Search Tree.
Classes:   IBinarySearchTree<T, U>
===================================================================+*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template <typename T, typename U>
class IBinarySearchTree {
public:
  virtual U Search(T key) = 0;
  virtual void Insert(T key, U data) = 0;
  virtual bool Delete(T key) = 0;
  virtual U Minimum() = 0;
  virtual U Maximum() = 0;
  virtual U Successor(T key) = 0;
  virtual U Predecessor(T key) = 0;
  virtual void Print() = 0;
};

#endif