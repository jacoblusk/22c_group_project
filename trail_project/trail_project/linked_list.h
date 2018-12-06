/*+===================================================================
File:      LINKEDLIST.H
Summary:   Contains template for a LinkedList.
Classes:   LinkedList<T>
===================================================================+*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include "linked_node.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:    LinkedList<T>
Summary:  An implementation of a Linked List.
Methods:  Empty
Empties the list.
Append
Appends a value to the list.
Prepend
Prepends a value to the list.
InsertBefore
Inserts a value before an index `i` in the list.
Pop
Removes and returns the first element in the list.
PopLast
Removes and returns the last element in the list.
Remove
Removes all occurences of element T in the list.
GetLength
Returns the length of the list.
GetHead
Returns the first node in the list.
GetTail
Returns the last node in the list.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
namespace containers {
  template <typename T>
  class linked_list_t {
  protected:
    linked_node_t<T> *m_pHead;
    linked_node_t<T> *m_pTail;
    size_t m_uLength;

  public:
    linked_list_t();
    virtual ~linked_list_t();
    void empty();
    void append(T value);
    bool insert_before(T value, size_t location);
    void prepend(T value);
    void pop(T* pValue);
    void pop_last(T *pValue);
    void remove(T value);
    size_t get_length();
    linked_node_t<T> *get_head();
    linked_node_t<T> *get_tail();
  };

  template <typename T>
  linked_list_t<T>::linked_list_t() {
    this->m_pHead = nullptr;
    this->m_pTail = nullptr;
    this->m_uLength = 0;
  }

  template <typename T>
  linked_list_t<T>::~linked_list_t() {
    this->empty();
  }

  template <typename T>
  void linked_list_t<T>::empty() {
    linked_node_t<T> *pTemp = nullptr;
    for (linked_node_t<T> *pCurrent = this->m_pHead;
      pCurrent != nullptr;) {
      pTemp = pCurrent->get_next();
      delete pCurrent;
      pCurrent = pTemp;
    }

    this->m_pHead = nullptr;
    this->m_pTail = nullptr;
    this->m_uLength = 0;
  }

  template <typename T>
  void linked_list_t<T>::append(T value) {
    linked_node_t<T> *pNode = new linked_node_t<T>(value, nullptr);
    if (this->m_pHead == nullptr) {
      this->m_pHead = pNode;
      this->m_pTail = pNode;
    }
    else {
      this->m_pTail->set_next(pNode);
      this->m_pTail = pNode;
    }

    this->m_uLength++;
  }

  template <typename T>
  bool linked_list_t<T>::insert_before(T value, size_t location) {
    linked_node_t<T> *pCurrent = this->get_head();
    linked_node_t<T> *pPrevious = nullptr;
    size_t i = 0;
    while (i < location) {
      pPrevious = pCurrent;
      pCurrent = pCurrent->get_next();
      ++i;

      if (pCurrent == nullptr) {
        break;
      }
    }

    if (i < location) {
      return false;
    }

    linked_node_t<T> *pNode = new linked_node_t<T>(value, pCurrent);
    if (pPrevious != nullptr) {
      pPrevious->set_next(pNode);
    }
    else {
      this->m_pHead = pNode;
    }

    if (pCurrent == nullptr) {
      this->m_pTail = pNode;
    }

    this->m_uLength++;
    return true;
  }

  template <typename T>
  void linked_list_t<T>::prepend(T value) {
    linked_node_t<T> *pNode = new linked_node_t<T>(value, nullptr);
    if (this->m_pTail == nullptr) {
      this->m_pHead = pNode;
      this->m_pTail = pNode;
    }
    else {
      pNode->set_next(this->m_pHead);
      this->m_pHead = pNode;
    }

    this->m_uLength++;
  }

  template <typename T>
  void linked_list_t<T>::pop(T* pValue) {
    if (this->m_pHead != nullptr) {
      linked_node_t<T> *pTemp = this->m_pHead;
      if (this->m_pHead->get_next() != nullptr) {
        this->m_pHead = this->m_pHead->get_next();
      }
      else {
        this->m_pHead = nullptr;
        this->m_pTail = nullptr;
      }

      if (pValue != nullptr) {
        *pValue = pTemp->get_value();
      }

      delete pTemp;
      this->m_uLength--;
      if (this->get_length() == 1) {
        this->m_pTail = this->m_pHead;
      }
    }
  }

  template <typename T>
  void linked_list_t<T>::pop_last(T *pValue) {
    if (this->m_pTail != nullptr) {
      linked_node_t<T> *pCurrent, *pPrevious = nullptr;
      pCurrent = this->m_pHead;
      while (pCurrent->get_next() != nullptr) {
        pPrevious = pCurrent;
        pCurrent = pCurrent->get_next();
      }

      if (pValue != nullptr) {
        *pValue = pCurrent->get_value();
      }

      delete pCurrent;
      if (pPrevious != nullptr) {
        pPrevious->set_next(nullptr);
      }
      else {
        this->m_pHead = nullptr;
        this->m_pTail = nullptr;
      }

      this->m_uLength--;
      if (this->get_length() == 1) {
        this->m_pHead == this->m_pTail;
      }
    }
  }

  template <typename T>
  void linked_list_t<T>::remove(T value) {
    linked_node_t<T> *pTemp = nullptr;
    linked_node_t<T> *pPrevious = nullptr;
    for (linked_node_t<int> *pCurrent = this->get_head();
      pCurrent != nullptr;) {
      pTemp = pCurrent->get_next();
      if (value == pCurrent->get_value()) {
        if (pPrevious == nullptr) {
          if (this->m_pTail == this->m_pHead) {
            this->m_pTail = pTemp;
          }

          delete pCurrent;
          pCurrent = nullptr;
          this->m_pHead = pTemp;
        }
        else {
          if (pCurrent == this->m_pTail) {
            this->m_pTail = pPrevious;
          }
          pPrevious->set_next(pCurrent->get_next());
          delete pCurrent;
          pCurrent = nullptr;
        }
        this->m_uLength--;
      }
      pPrevious = pCurrent;
      pCurrent = pTemp;
    }
  }

  template <typename T>
  size_t linked_list_t<T>::get_length() {
    return this->m_uLength;
  }

  template <typename T>
  linked_node_t<T> *linked_list_t<T>::get_head() {
    return this->m_pHead;
  }

  template <typename T>
  linked_node_t<T> *linked_list_t<T>::get_tail() {
    return this->m_pTail;
  }
}

#endif