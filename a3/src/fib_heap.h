#ifndef FIB_HEAP_PP_H
#define FIB_HEAP_PP_H

#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>
#include "priority_queue.h"


// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();
  
  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;
  
private:
  // Note: compare is a functor object
  COMP compare;

private:
  const double phi = 1.618;
  unsigned n;

  struct node_t {
    TYPE key;
    unsigned deg;
    std::list<node_t *> cld;
  };
  typename std::list<node_t *>::iterator min;
  std::list<node_t *> roots;

  void consolidate();
  void link(const decltype(min)&y, node_t *&x);
  void erase_helper(std::list<node_t *>);
  void print_list() const {
      std::cout << "( ";
      for (auto p = roots.begin(); p != roots.end(); ++p) {
        std::cout << (*p)->key << ":" << (*p)->deg << " ";
      }
      std::cout << ")" << std::endl;
    }
};




template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: fib_heap(COMP comp) {
    compare = comp;
    n = 0;
    min = roots.end();
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: ~fib_heap() {
    erase_helper(roots);
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: erase_helper(std::list<node_t *> vic) {
    if (vic.empty()) return;
    for (auto &it : vic) {
        erase_helper(it->cld);
        delete it;
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    node_t *x = new node_t();
    x->deg = 0; x->key = val;
    roots.emplace_front(x);
    if (min == roots.end() || (min != roots.end() && compare(x->key, (*min)->key))) min = roots.begin();
    ++n;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min() {
    TYPE res = (*min)->key;
    auto &z = *min;
    if (z) {
        if (!z->cld.empty())
            roots.splice(roots.begin(), std::move(z->cld));

        delete z;
        roots.erase(min); // min has undefined behavior
        --n;
        if (n == 0) min = roots.end();
        else consolidate();
    }
    return res;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: consolidate() {
    const unsigned Dn = (unsigned)(log(n)/log(phi));
    decltype(min) A[Dn+1];
    for (unsigned i = 0; i <= Dn; ++i) A[i] = roots.end();
    for (auto w = roots.begin(); w != roots.end();) {
        auto x = w++;
        unsigned d = (*x)->deg;
        while (A[d] != roots.end()) {
            auto y = A[d];
            if (compare((*y)->key, (*x)->key)) std::swap(x, y);
            link(y, *x);
            A[d++] = roots.end();
        }
        A[d] = x;
    }
    min = roots.begin();
    for (auto it = roots.begin(); it != roots.end(); ++it)
        if (compare((*it)->key, (*min)->key))
            min = it;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: link(const decltype(min)&y, node_t *&x) {
    node_t *yy = (*y);
    roots.erase(y);
    x->cld.emplace_front(std::move(yy));
    ++x->deg;
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const {
    return (*min)->key;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    return n == 0;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const { 
    return n;
}

#endif //FIB_HEAP_PP_H