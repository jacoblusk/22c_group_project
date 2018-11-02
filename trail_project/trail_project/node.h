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
template <typename T>
class Node {
private:
  T m_value;
  Node<T> *m_pNext;
public:
  Node(T value, Node<T> *next) {
    this->m_value = value;
    this->m_pNext = next;
  }

  T GetValue() {
    return this->m_value;
  }

  Node<T> *GetNext() {
    return this->m_pNext;
  }

  void SetValue(T value) {
    this->m_value = value;
  }

  void SetNext(Node<T> *pNext) {
    this->m_pNext = pNext;
  }
};

#endif