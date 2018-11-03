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
  virtual U Get(T key) = 0;
  virtual void Set(T key, U data) = 0;
  virtual void Delete(T key) = 0;
  virtual void Empty() = 0;
  virtual bool IsEmpty() = 0;
  virtual bool Contains(T key) = 0;
  virtual void Print() = 0;
};

#endif