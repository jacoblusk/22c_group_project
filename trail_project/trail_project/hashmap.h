/*+===================================================================
File:      HASHMAP.H
Summary:   Contains an interface for HashMap.
Classes:   IHashMap<T, U>
===================================================================+*/

#ifndef HASHMAP_H
#define HASHMAP_H

template <typename T, typename U>
class IHashMap {
public:
  U Get(T key) = 0;
  void Set(T key, U data) = 0;
  void Delete(T key) = 0;
  void Empty() = 0;
  bool IsEmpty() = 0;
  bool Contains(T key) = 0;
};

#endif