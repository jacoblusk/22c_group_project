/*
* MERGED BST FILE
*
* Initial: Jacob -> Lab 5
* Vertical Print: Elizabeth
* Merger: Connor
* Horizontal Print: Connor
*
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>

#include "queue.h"
#include "bst_node.h"

#define space 5

namespace containers {
  struct binary_tree_diagnositics_t {
    size_t comparisons;
    size_t iterations;
  };

  template <typename T, typename U>
  struct __pair {
    T a;
    U b;
  };

  template<typename T>
  bool __bst_default_comparator(T a, T b) {
    return a >= b;
  }

  template<typename T>
  class binary_search_tree_t {
  public:
    typedef bool(*bst_comparator)(T, T);

  private:
    binary_tree_diagnositics_t diagnositics;
    bst_node_t<T> *root;
    size_t size;
    binary_search_tree_t::bst_comparator comparator;

    bst_node_t<T> *insert(bst_node_t<T> *parent, T data);

    template<typename U>
    void inorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data);

    template<typename U>
    void preorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data);

    template<typename U>
    void postorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data);

    void verticalPrint(bst_node_t<T> *root, std::vector<std::string> &output, int left, int top, int width);

    void horizontalPrint(bst_node_t<T> *tree, int depth, char *path, int right);

    void InitialHorizontalPrint(bst_node_t<T> *tree);

    int getPrintHeight(bst_node_t<T> *root);

    int maximum(int a, int b);

  public:

    binary_search_tree_t(typename binary_search_tree_t::bst_comparator comparator);

    binary_search_tree_t(void);

    void insert(T data);

    template<typename U>
    void breadth_first(void(*map_fn)(T, U), U data);

    template<typename U>
    void inorder(void(*map_fn)(T, U), U data);

    template<typename U>
    void preorder(void(*map_fn)(T, U), U data);

    template<typename U>
    void postorder(void(*map_fn)(T, U), U data);

    void verticalPrint(std::ostream& os);

    bool remove(T key);

    size_t get_size(void);

    bst_node_t<T> *get_root(void) const;

    void reset_last_diagnositics(void);
    binary_tree_diagnositics_t get_last_diagnositics(void);
  };

  /*================================= Private BST Function Definitions=================================*/

  template<typename T>
  bst_node_t<T> *binary_search_tree_t<T>::insert(bst_node_t<T> *parent, T data) {
    this->diagnositics.iterations++;
    if (parent == nullptr) {
      return new bst_node_t<T>(data);
    }

    this->diagnositics.comparisons++;
    if (!this->comparator(data, parent->get_data())) {
      parent->set_left(this->insert(parent->get_left(), data));
    }
    else {
      parent->set_right(this->insert(parent->get_right(), data));
    }

    return parent;
  }

  template<class T>
  void binary_search_tree_t<T>::verticalPrint(bst_node_t<T> *proot, std::vector<std::string> &output, int left, int top,
    int width) {
    std::stringstream sstream;

    sstream << *(proot->get_data());
    std::string nodeStr = sstream.str().substr(0, 5);
    //output data
    int left_shift = 1 - (nodeStr.length() - 1) / 2;
    int x;
    for (size_t i = 0; i < nodeStr.length() && ((left + width / 2 + i) < output[top].length()); i++) {
      x = left + width / 2 + left_shift + i;
      output[top][x] = nodeStr[i];
    }

    //calc '/' and '\' offsets
    int branchOffset = (width + 3) >> 3;

    //LEFT CHILD;
    int center = left + width / 2;
    int leftcenter = left + (width / 2 - 1) / 2;
    int rightcenter = left + width / 2 + 2 + (width / 2 - 1) / 2;

    if (proot->get_left() != NULL) {
      int branchPosition = center - branchOffset + 1;
      //left upper branch
      for (int curr_pos = center + left_shift - 2; curr_pos > branchPosition; curr_pos--) {
        output[top][curr_pos] = '_';
      }
      //draw left
      output[top + 1][branchPosition] = '/';
      //draw left lower branch
      for (int curr_pos = branchPosition - 1; curr_pos > leftcenter + 2; curr_pos--) {
        output[top + 1][curr_pos] = '_';
      }
      //draw left subtree
      verticalPrint(proot->get_left(), output, left, top + 2, width / 2 - 1);
    }
  }

  template<class T>
  void binary_search_tree_t<T>::verticalPrint(std::ostream& os) {

    if (root == NULL) {
      return;
    }
    // Make a character matrix for outputting the tree onto
    int root_height = getPrintHeight(root);
    size_t print_matrix_width = ((4 << root_height) - 3);

    size_t print_matrix_height = 2 * root_height + 1;

    // Initialize this matrix to be filled with spaces
    std::vector<std::string> output(print_matrix_height);
    for (size_t i = 0; i < output.size(); ++i) {
      output[i] = std::string(print_matrix_width, ' ');
    }
    std::string a = std::string(print_matrix_width, ' ');

    // Recursively print each node
    verticalPrint(root, output, 0, 0, print_matrix_width);

    // Output the matrix
    for (int row = 0; row < print_matrix_height; ++row)
      os << output[row] << std::endl;
  }

  template<typename T>
  binary_search_tree_t<T>::binary_search_tree_t(typename binary_search_tree_t::bst_comparator comparator) {
    this->comparator = comparator;
    this->root = nullptr;
  }

  template<typename T>
  binary_search_tree_t<T>::binary_search_tree_t(void) {
    this->comparator = __bst_default_comparator;
    this->root = nullptr;
  }

  template<typename T>
  size_t binary_search_tree_t<T>::get_size(void) {
    return this->size;
  }

  template <typename T>
  bst_node_t<T> *binary_search_tree_t<T>::get_root(void) const {
    return this->root;
  }

  template<typename T>
  void binary_search_tree_t<T>::reset_last_diagnositics(void)
  {
    this->diagnositics.iterations = 0;
    this->diagnositics.comparisons = 0;
  }

  template<typename T>
  binary_tree_diagnositics_t binary_search_tree_t<T>::get_last_diagnositics(void)
  {
    return this->diagnositics;
  }

  template<typename T>
  void binary_search_tree_t<T>::insert(T data) {
    this->size++;
    this->reset_last_diagnositics();
    if (this->root == nullptr) {
      this->root = this->insert(this->root, data);
    }
    else {
      this->insert(this->root, data);
    }
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::inorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data) {
    if (node != nullptr) {
      this->inorder<U>(node->get_left(), map_fn, data);
      map_fn(node->get_data(), data);
      this->inorder<U>(node->get_right(), map_fn, data);
    }
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::preorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data) {
    if (node != nullptr) {
      map_fn(node->get_data(), data);
      this->preorder<U>(node->get_left(), map_fn, data);
      this->preorder<U>(node->get_right(), map_fn, data);
    }
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::postorder(bst_node_t<T> *node, void(*map_fn)(T, U), U data) {
    if (node != nullptr) {
      this->postorder<U>(node->get_left(), map_fn, data);
      this->postorder<U>(node->get_right(), map_fn, data);
      map_fn(node->get_data(), data);
    }
  }


  /*=================================Print Function Definitions=================================*/

  //Max number of nodes at level L in a binary tree is 2^L
  //So max width of tree is 2^height
  //


  template<class T>
  void binary_search_tree_t<T>::horizontalPrint(bst_node_t<T> *tree, int depth, char *path, int right) {
    //Stopping condition
    if (tree == NULL)
      return;

    //Increase spacing
    depth++;

    //Start with right node
    horizontalPrint(tree->right, depth, path, 1);

    //Set | Draw map
    path[depth - 2] = 0;

    if (right)
      path[depth - 2] = 1;

    if (tree->left)
      path[depth - 1] = 1;

    //Print root after spacing
    std::cout << ("\n");

    for (int i = 0; i < depth - 1; i++) {
      if (i == depth - 2)
        std::cout << ("+");
      else if (path[i])
        std::cout << ("|");
      else
        std::cout << (" ");

      for (int j = 1; j < space; j++)
        if (i < depth - 2)
          std::cout << (" ");
        else
          std::cout << ("-");
    }

    std::cout << ("%d\n", tree->value);

    //Vertical spacers
    for (int i = 0; i < depth; i++) {
      if (path[i])
        std::cout << ("|");
      else
        std::cout << (" ");

      for (int j = 1; j < space; j++)
        std::cout << (" ");
    }

    //Go to left node
    horizontalPrint(tree->left, depth, path, 0);

  }

  //Primary
  template<class T>
  void binary_search_tree_t<T>::InitialHorizontalPrint(bst_node_t<T> *tree) {
    char path[255] = {};

    //initial depth is 0
    horizontalPrint(tree, 0, path, 0);
  }


  template<class T>
  int binary_search_tree_t<T>::getPrintHeight(bst_node_t<T> *proot) {
    if (proot == NULL) {
      return 0;
    }

    int l_height = getPrintHeight(proot->get_left());
    int r_height = getPrintHeight(proot->get_right());
    return 1 + maximum(l_height, r_height);
  }

  template<class T>
  int binary_search_tree_t<T>::maximum(int a, int b) {
    int max = (a >= b) ? a : b;
    return max;
  }


  /*================================= Public BST Function Definitions=================================*/

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::breadth_first(void(*map_fn)(T, U), U data) {
    queue_t<bst_node_t<T> *> queue;
    bst_node_t<T> *temp_node = this->root;
    while (temp_node != nullptr) {
      map_fn(temp_node->get_data(), data);

      if (temp_node->get_left() != nullptr)
        queue.enqueue(temp_node->get_left());
      if (temp_node->get_right() != nullptr)
        queue.enqueue(temp_node->get_right());

      if (!queue.is_empty()) {
        temp_node = queue.dequeue();
      }
      else {
        temp_node = nullptr;
      }
    }
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::inorder(void(*map_fn)(T, U), U data) {
    this->inorder<U>(this->root, map_fn, data);
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::preorder(void(*map_fn)(T, U), U data) {
    this->preorder<U>(this->root, map_fn, data);
  }

  template<typename T>
  template<typename U>
  void binary_search_tree_t<T>::postorder(void(*map_fn)(T, U), U data) {
    this->postorder<U>(this->root, map_fn, data);
  }

  //NODE DELETE
  template<typename T>
  bool binary_search_tree_t<T>::remove(T key) {
    if (root == NULL)
      return false;
    else {

      if (this->bst_comparator(root->get_value(), value)) {
        bst_node_t<U> auxRoot;;
        auxRoot.setLeftChild(root);
        bst_node_t<U>* removedNode = root->remove(value, &auxRoot);
        root = auxRoot.getLeft();
        if (removedNode != NULL) {
          delete removedNode;
          return true;
        }
        else
          return false;
      }
      else {
        bst_node_t<U>* removedNode = root->remove(value, NULL);
        if (removedNode != NULL) {
          delete removedNode;
          return true;
        }
        else
          return false;
      }
    }
  }

}