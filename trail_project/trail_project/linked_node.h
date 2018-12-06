/*+===================================================================
File:      NODE.H
Summary:   Contains template for Node, which is used by LinkedList.
Classes:   Node<T>
===================================================================+*/

#ifndef NODE_H
#define NODE_H

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:    Node
Summary:  A Node used in a LinkedList.
Methods:  GetValue
Returns the value stored in the node.
GetNext
Returns the next element in the LinkedList.
SetValue
Sets the value stored in the node.
SetNext
Sets the next element in the LinkedList.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

namespace containers {
  template <typename T>
  class linked_node_t {
  private:
    T m_value;
    linked_node_t<T> *m_pNext;
  public:
    linked_node_t(T value, linked_node_t<T> *next);
    T get_value();
    linked_node_t<T> *get_next();
    void set_value(T value);
    void set_next(linked_node_t<T> *pNext);
  };

  template<typename T>
  linked_node_t<T>::linked_node_t(T value, linked_node_t<T>* next) {
    this->m_value = value;
    this->m_pNext = next;
  }

  template<typename T>
  T linked_node_t<T>::get_value() {
    return this->m_value;
  }

  template<typename T>
  linked_node_t<T>* linked_node_t<T>::get_next() {
    return this->m_pNext;
  }

  template<typename T>
  void linked_node_t<T>::set_value(T value) {
    this->m_value = value;
  }

  template<typename T>
  void linked_node_t<T>::set_next(linked_node_t<T>* pNext) {
    this->m_pNext = pNext;
  }
}

#endif