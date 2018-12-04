#pragma once
#include "HashNode.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T, typename U>
class HashMap{
private:
   HashNode<T, U>** table;
   size_t capacity;
   size_t tableSize;

public:
   HashMap();
   HashMap(size_t capacity);
   ~HashMap();

   void insert(T key, U data);
   void remove(T key);
   HashNode<T, U>* find(T key);
   bool contains(T key);
   void clear();
   bool isEmpty();
   void print();

   size_t hash(T key);
   
};

//initialize table to initial size 20, and populate with hashnode pointers
template<typename T, typename U>
 HashMap<T, U>::HashMap(): capacity(20), tableSize(0){
   table = new HashNode<T, U>*[capacity];

   for (int i = 0; i < capacity; i++)
      table[i] = NULL;

   
}

//user defined capacity
template<typename T, typename U>
HashMap<T, U>::HashMap(size_t cap):HashMap(), capacity(cap) {}

template<typename T, typename U>
HashMap<T, U>::~HashMap() {
   delete[] table;
}

//hash the key for index node will be inserted into 
//includes quadratic probing collision resolution
template<typename T, typename U>
void HashMap<T, U>::insert(T key, U data)
{
   HashNode<T, U> *temp = new HashNode<T, U>(key, data);

   // Apply hash function to find index for given key 
   size_t hashIndex = hash(key);
   int quad_probe = 1;
   //collision resolution
   while (table[hashIndex] != NULL && table[hashIndex]->getKey() != key && quad_probe*quad_probe < capacity){
      quad_probe++;
      hashIndex += quad_probe * quad_probe;
      hashIndex % capacity;
   }

   //if new node to be inserted increase the current size 
   if (table[hashIndex] == NULL) tableSize++;
   table[hashIndex] = temp;
}

//removes a hash node from the table, replaces with dummy node
template<typename T, typename U>
void HashMap<T, U>::remove(T key){
   // Apply hash function to find index for given key 
   int hashIndex = hash(key);

   //finding the node with given key 
   while (table[hashIndex] != NULL)
   {
      //if node found 
      if (table[hashIndex]->getKey() == key){
         HashNode<T, U> *temp = table[hashIndex];

         //Insert dummy node here for further use 
         table[hashIndex] = dummy;

         // Reduce size 
         size--;
         delete temp;
      }
      hashIndex++;
      hashIndex %= capacity;

   }

   //If not found return null 
   return NULL;
}

template<typename T, typename U>
HashNode<T, U>* HashMap<T, U>::find(T key){
   bool found = false;
   size_t hashIndex = hash(key);
   int quad_probe = 1;
   while (!found && quad_probe*quad_probe < capacity) {
      found = table[hashIndex]->getKey() == key;
      if (!found) {
         hashIndex += quad_probe * quad_probe;
         quad_probe++;
      }
   }
   if (found) {
      return table[hashIndex];
   }
   else return NULL;
}

template<typename T, typename U>
bool HashMap<T, U>::contains(T key){
   return (find(key)->getKey() != NULL);
}

template<typename T, typename U>
 void HashMap<T, U>::clear() {
    for (int i = 0; i < capacity; i++) {
       table[i] = NULL;
    }
    tableSize = 0;
}

template<typename T, typename U>
 bool HashMap<T, U>::isEmpty(){
    return tableSize == 0;
}

template<typename T, typename U>
 void HashMap<T, U>::print(){
    for (int i = 0; i < capacity; i++) {
       if (table[i] != NULL && table[i] != NULL) {
          cout << table[i] << endl;
       }
    }
}

template<typename T, typename U>
 size_t HashMap<T, U>::hash(T key) {
    const char* keychars = key.c_str();
    size_t hashedkey = 0;
    for (int i = 0; i < (sizeof(keychars) / sizeof(keychars[0])); i++) {
       hashedkey += keychars[i];
    }
    hashedkey %= capacity;
    return hashedkey;
}



