/*+===================================================================
File:      LINKEDLIST.H
Summary:   Contains template for a LinkedList.
Classes:   LinkedList<T>
===================================================================+*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include "node.h"

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
          Reverse
            Reverses the list.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
template <typename T>
class LinkedList {
protected:
  Node<T> *m_pHead;
  Node<T> *m_pTail;
  size_t m_uLength;

public:
  LinkedList() {
    this->m_pHead = nullptr;
    this->m_pTail = nullptr;
    this->m_uLength = 0;
  }

  virtual ~LinkedList() {
    this->Empty();
  }

  void Empty() {
    Node<T> *pTemp = nullptr;
    for (Node<T> *pCurrent = this->m_pHead;
      pCurrent != nullptr;) {
      pTemp = pCurrent->GetNext();
      delete pCurrent;
      pCurrent = pTemp;
    }

    this->m_pHead = nullptr;
    this->m_pTail = nullptr;
    this->m_uLength = 0;
  }

  void Append(T value) {
    Node<T> *pNode = new Node<T>(value, nullptr);
    if (this->m_pHead == nullptr) {
      this->m_pHead = pNode;
      this->m_pTail = pNode;
    }
    else {
      this->m_pTail->SetNext(pNode);
      this->m_pTail = pNode;
    }

    this->m_uLength++;
  }

  bool InsertBefore(T value, size_t location) {
    Node<T> *pCurrent = this->GetHead();
    Node<T> *pPrevious = nullptr;
    size_t i = 0;
    while (i < location) {
      pPrevious = pCurrent;
      pCurrent = pCurrent->GetNext();
      ++i;

      if (pCurrent == nullptr) {
        break;
      }
    }

    if (i < location) {
      return false;
    }

    Node<T> *pNode = new Node<T>(value, pCurrent);
    if (pPrevious != nullptr) {
      pPrevious->SetNext(pNode);
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

  void Prepend(T value) {
    Node<T> *pNode = new Node<T>(value, nullptr);
    if (this->m_pTail == nullptr) {
      this->m_pHead = pNode;
      this->m_pTail = pNode;
    }
    else {
      pNode->SetNext(this->m_pHead);
      this->m_pHead = pNode;
    }

    this->m_uLength++;
  }

  bool Pop(T* pValue) {
    if (this->m_pHead != nullptr) {
      Node<T> *pTemp = this->m_pHead;
      if (this->m_pHead->GetNext() != nullptr) {
        this->m_pHead = this->m_pHead->GetNext();
      }
      else {
        this->m_pHead = nullptr;
        this->m_pTail = nullptr;
      }

      if (pValue != nullptr) {
        *pValue = pTemp->GetValue();
      }

      delete pTemp;
      this->m_uLength--;
      if (this->GetLength() == 1) {
        this->m_pTail = this->m_pHead;
      }
      return true;
    }
    return false;
  }

  void Reverse() {
    Node<T> *pCurrent = this->GetHead();
    Node<T> *pPrevious = nullptr;
    Node<T> *pNext = nullptr;

    while (pCurrent != nullptr) {
      pNext = pCurrent->GetNext();
      pCurrent->SetNext(pPrevious);
      pPrevious = pCurrent;
      pCurrent = pNext;
    }

    this->m_pHead = pPrevious;
    pCurrent = this->GetHead();
    while (pCurrent != nullptr) {
      pNext = pCurrent->GetNext();
      if (pNext == nullptr) {
        this->m_pTail = pCurrent;
      }
      pCurrent = pNext;
    }
  }

  void Copy(LinkedList<T> *pLinkedList) {
    for (Node<T> *pCurrent = this->GetHead(); pCurrent != nullptr; pCurrent = pCurrent->GetNext()) {
      pLinkedList->Append(pCurrent->GetValue());
    }
  }

  bool PopLast(T *pValue) {
    if (this->m_pTail != nullptr) {
      Node<T> *pCurrent, *pPrevious = nullptr;
      pCurrent = this->m_pHead;
      while (pCurrent->GetNext() != nullptr) {
        pPrevious = pCurrent;
        pCurrent = pCurrent->GetNext();
      }

      if (pValue != nullptr) {
        *pValue = pCurrent->GetValue();
      }

      delete pCurrent;
      if (pPrevious != nullptr) {
        pPrevious->SetNext(nullptr);
      }
      else {
        this->m_pHead = nullptr;
        this->m_pTail = nullptr;
      }

      this->m_uLength--;
      if (this->GetLength() == 1) {
        this->m_pHead == this->m_pTail;
      }
      return true;
    }
    return false;
  }

  void Remove(T value) {
    Node<T> *pTemp = nullptr;
    Node<T> *pPrevious = nullptr;
    for (Node<int> *pCurrent = this->GetHead();
      pCurrent != nullptr;) {
      pTemp = pCurrent->GetNext();
      if (value == pCurrent->GetValue()) {
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
          pPrevious->SetNext(pCurrent->GetNext());
          delete pCurrent;
          pCurrent = nullptr;
        }
        this->m_uLength--;
      }
      pPrevious = pCurrent;
      pCurrent = pTemp;
    }
  }

  size_t GetLength() {
    return this->m_uLength;
  }

  Node<T> *GetHead() {
    return this->m_pHead;
  }

  Node<T> *GetTail() {
    return this->m_pTail;
  }
};

#endif