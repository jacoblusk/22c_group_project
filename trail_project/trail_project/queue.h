/*+===================================================================
File:      QUEUE.H
Summary:   Contains template for a Queue.
Classes:   Queue<T>
===================================================================+*/

#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:    Queue<T>
Summary:  A Queue implmenetation.
Methods:  Enqueue
Enqueues an element in the queue.
Dequeue
Dequeues an element in the queue (last element).
Peek
Peeks at the next element in the queue to dequeue.
PeekFront
Peeks at the last item placed in the queue.
GetLength
Returns the length of the queue.
Empty
Empties the queue.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

namespace containers {
  template <class T>
  class queue_t : private linked_list_t<T> {
  public:
    queue_t();
    ~queue_t();
    void enqueue(T value);
    T dequeue();
    T peek_last();
    T peek();
    size_t get_length();
    bool is_empty();
    void empty();
  };

  template <class T>
  queue_t<T>::queue_t() {

  }

  template <class T>
  queue_t<T>::~queue_t() {
    this->queue_t::empty();
  }

  template <class T>
  void queue_t<T>::enqueue(T value) {
    this->append(value);
  }

  template <class T>
  T queue_t<T>::dequeue() {
    T value;
    this->pop(&value);
    return value;
  }

  template <class T>
  T queue_t<T>::peek_last() {
    T value;
    value = this->get_tail()->get_value();
    return value;
  }

  template <class T>
  T queue_t<T>::peek() {
    T value;
    value = this->get_head()->get_value();
    return value;
  }

  template <class T>
  size_t queue_t<T>::get_length() {
    return this->linked_list_t<T>::get_length();
  }

  template <class T>
  bool queue_t<T>::is_empty() {
    return this->linked_list_t<T>::get_length() == 0;
  }

  template <class T>
  void queue_t<T>::empty() {
    this->linked_list_t<T>::empty();
  }
}

#endif