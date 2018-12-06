#pragma once

#include <iostream>
#include <string>

namespace containers {

  bool __is_prime(size_t p)
  {
    if (p == 2 || p == 3)
      return true;
    if (p % 2 == 0 || p % 3 == 0)
      return false;

    size_t divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= p) {
      if (p % (divisor - 1) == 0)
        return false;
      if (p % (divisor + 1) == 0)
        return false;
      divisor += 6;
    }

    return true;
  }

  size_t __next_prime(size_t p) {
    while (!__is_prime(++p));
    return p;
  }

  template <typename T, typename U>
  struct bucket_t {
    T key;
    U data;
    bool empty;
    bucket_t<T, U> *next;
  };

  struct hash_map_diagnositics_t {
    size_t iterations;
    size_t links_traversed;
  };

  template <typename T, typename U>
  class hash_map_t {
  public:
    typedef size_t(*hash_fn)(T, size_t);
    typedef bool(*cmp_fn)(T, T);
  private:
    hash_fn h_f;
    cmp_fn cmp_f;
    size_t capacity;
    bucket_t<T, U> *data;
    hash_map_diagnositics_t diagnositics;
  public:
    hash_map_t(hash_fn hf, cmp_fn cf, size_t capacity);
    bool put(T key, U data);
    bool find(T key, U *out);
    void print(void);
    bool remove(T key);
    size_t get_capacity(void);

    bucket_t<T, U> *get_buckets(void);
    double get_load_factor(void);
    void reset_last_diagnostics(void);
    hash_map_diagnositics_t get_last_diagnositics(void);
    void resize(void);

    template <typename W>
    void foreach_data(void(*map_fn)(U, W), W user_data) {
      for (size_t i = 0; i < this->capacity; i++) {
        bucket_t <T, U> *cb = &this->data[i];
        if (!cb->empty) {
          for (; cb; cb = cb->next) {
            map_fn(cb->data, user_data);
          }
        }
      }
    }
  };

  template <typename T, typename U>
  hash_map_t<T, U>::hash_map_t(hash_fn hf, cmp_fn cf, size_t capacity) {
    this->h_f = hf;
    this->cmp_f = cf;
    this->capacity = capacity;
    this->data = new bucket_t<T, U>[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
      this->data[i].empty = true;
      this->data[i].next = nullptr;
    }
  }

  template <typename T, typename U>
  void hash_map_t<T, U>::reset_last_diagnostics(void) {
    this->diagnositics.iterations = 0;
    this->diagnositics.links_traversed = 0;
  }

  template <typename T, typename U>
  hash_map_diagnositics_t hash_map_t<T, U>::get_last_diagnositics(void) {
    return this->diagnositics;
  }

  template <typename T, typename U>
  size_t hash_map_t<T, U>::get_capacity(void) {
    return this->capacity;
  }

  template<typename T, typename U>
  bucket_t<T, U>* hash_map_t<T, U>::get_buckets(void)
  {
    return this->data;
  }

  template <typename T, typename U>
  double hash_map_t<T, U>::get_load_factor(void) {
    size_t count = 0;
    for (size_t i = 0; i < this->capacity; i++) {
      bucket_t <T, U> *cb = &this->data[i];
      if (!cb->empty) {
        for (; cb; cb = cb->next) {
          ++count;
        }
      }
    }

    return static_cast<double>(count) / this->capacity;
  }


  template <typename T, typename U>
  void hash_map_t<T, U>::resize(void) {
    size_t new_capacity = __next_prime(this->capacity * 2);
    bucket_t<T, U> *old_data = this->data;
    this->data = new bucket_t<T, U>[new_capacity];
    for (size_t i = 0; i < new_capacity; i++) {
      this->data[i].empty = true;
      this->data[i].next = nullptr;
    }

    for (size_t i = 0; i < this->capacity; i++) {
      ++this->diagnositics.iterations;
      bucket_t <T, U> *cb = &old_data[i];
      if (!cb->empty) {
        for (; cb; cb = cb->next) {
          ++this->diagnositics.links_traversed;
          this->put(cb->key, cb->data);
        }
      }
    }

    this->capacity = new_capacity;
    delete[] old_data;
  }

  template <typename T, typename U>
  bool hash_map_t<T, U>::put(T key, U data) {
    if (this->get_load_factor() > 0.5) {
      this->resize();
    }

    this->reset_last_diagnostics();

    size_t i = this->h_f(key, this->capacity);
    bucket_t<T, U> *cb = &this->data[i];
    ++this->diagnositics.iterations;
    if (cb->empty || this->cmp_f(cb->key, key)) {
      cb->data = data;
      cb->key = key;
      cb->empty = false;
    }
    else {
      for (; cb; cb = cb->next) {
        ++this->diagnositics.links_traversed;
        if (cb->next == nullptr) {
          break;
        }
        if (this->cmp_f(cb->key, key)) {
          return false;
        }
      }

      bucket_t<T, U> *new_b = new bucket_t<T, U>;
      new_b->data = data;
      new_b->key = key;
      new_b->empty = false;
      new_b->next = nullptr;
      cb->next = new_b;
    }
    return true;
  }

  template <typename T, typename U>
  bool hash_map_t<T, U>::remove(T key) {
    this->reset_last_diagnostics();
    size_t i = this->h_f(key, this->capacity);
    bucket_t<T, U> *cb = &this->data[i];
    ++this->diagnositics.iterations;
    if (!cb->empty) {
      bucket_t<T, U> *cb2 = cb;
      bucket_t<T, U> *cbp = nullptr;
      for (; cb2 && !this->cmp_f(cb2->key, key); cb2 = cb2->next) {
        cbp = cb2;
        ++this->diagnositics.links_traversed;
      }
      if (cb2) {
        if (cbp) {
          //delete by skipping over it.
          cbp->next = cb2->next;
          return true;
        }
        else {
          cb->empty = true;
          return true;
        }
      }
    }
    return false;
  }

  template <typename T, typename U>
  bool hash_map_t<T, U>::find(T key, U *out_d) {
    this->reset_last_diagnostics();
    size_t i = this->h_f(key, this->capacity);
    bucket_t<T, U> *cb = &this->data[i];
    this->diagnositics.iterations++;
    if (!cb->empty) {
      for (; cb; cb = cb->next) {
        this->diagnositics.links_traversed++;
        if (this->cmp_f(cb->key, key)) {
          *out_d = cb->data;
          return true;
        }
      }
    }

    return false;
  }

  template <typename T, typename U>
  void hash_map_t<T, U>::print(void) {
    this->reset_last_diagnostics();
    size_t count = 0;
    for (size_t i = 0; i < this->capacity; i++) {
      this->diagnositics.iterations++;
      bucket_t <T, U> *cb = &this->data[i];
      if (!cb->empty) {
        bucket_t <T, U> *cbp = nullptr;
        for (; cb; cb = cb->next) {
          if (cbp) {
            this->diagnositics.links_traversed++;
          }
          std::cout << "[" << count++ << "] " << *cb->data << std::endl;
          cbp = cb;
        }
      }
    }
  }
}