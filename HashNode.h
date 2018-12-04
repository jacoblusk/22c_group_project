#pragma once
#include <iostream>
#include <string>

template <typename T, typename U>
class HashNode {
private:
   T key;
   U data;
   bool deleted;
public:
   HashNode();
   HashNode(T key, U data);
   ~HashNode();
   T getKey();
   void setKey(T k);
   U getData();
   void setData(U d);
};

template <typename T, typename U>
HashNode<T, U>::HashNode<T, U>(): key(NULL), data(NULL), deleted(false) {}

template <typename T, typename U>
HashNode<T, U>::HashNode<T, U>(T k, U d):key(k), data(d), deleted(false){}

template <typename T, typename U>
HashNode<T, U>::~HashNode<T, U>(){}

template <typename T, typename U>
T HashNode<T, U>::getKey() {
   return key;
}

template <typename T, typename U>
void HashNode<T, U>::setKey(T k) {
   key = k;
}

template <typename T, typename U>
U HashNode<T, U>::getData() {
   return data;
}

template <typename T, typename U>
void HashNode<T, U>::setData(U d) {
   data = d;
}