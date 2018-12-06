/*
* MERGED BST_NODE FILE
*
* Initial: Jacob -> Lab 5
* Merger: Connor
* Remove Function: Connor
*
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>

#include "Query.h"
#include "queue.h"
#include "bst_node.h"

namespace containers {
  template <typename U>
  class bst_node_t {
  private:
    U data;
    bst_node_t<U> *left;
    bst_node_t<U> *right;

  public:
    bst_node_t(U data);

    void set_left(bst_node_t<U> *left);

    void set_right(bst_node_t<U> *right);

    void set_data(U data);

    bst_node_t<U> *get_left(void);

    bst_node_t<U> *get_right(void);

    U get_data(void);

  };

  template<typename U>
  bst_node_t<U>::bst_node_t(U data)
  {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
  }

  template<typename U>
  void bst_node_t<U>::set_left(bst_node_t<U>* left)
  {
    this->left = left;
  }

  template<typename U>
  void bst_node_t<U>::set_right(bst_node_t<U>* right)
  {
    this->right = right;
  }

  template<typename U>
  void bst_node_t<U>::set_data(U data)
  {
    this->data = data;
  }

  template<typename U>
  bst_node_t<U>* bst_node_t<U>::get_left(void)
  {
    return this->left;
  }

  template<typename U>
  bst_node_t<U>* bst_node_t<U>::get_right(void)
  {
    return this->right;
  }

  template<typename U>
  U bst_node_t<U>::get_data(void)
  {
    return this->data;
  }
}