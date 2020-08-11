/**
 * @file Newvector.h
 * @author https://github.com/jsmlau
 * @brief Template definitions for Newvector.  Specifically, include this file
 * to create Newlist classes in a manner similar to STD vectors
 * @version 0.1
 * @date 2019-10-0
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MYVECTOR_H
#define MYVECTOR_H

// ---------------------- Myvector Prototype --------------------------
template <class Object>
class Myvector {
 private:
  int mSize;
  int mCapacity;
  Object* mObjects;

  static const int m_SPARE_CAPACITY = 16;

 public:
  Myvector(int initSize = 0);
  Myvector(const Myvector& rhs);
  ~Myvector() { delete[] mObjects; }

  const Myvector& operator=(const Myvector& rhs);
  void resize(int newSize);
  void reserve(int newCapacity);

  Object& operator[](int index);
  const Object& operator[](int index) const;

  // thrown in for stl vector compatibility
  Object& at(int index) { return (*this)[index]; }
  const Object& at(int index) const { return (*this)[index]; }

  bool empty() const { return mSize == 0; }
  int size() const { return mSize; }
  int capacity() const { return mCapacity; }

  void push_back(const Object& x);
  void pop_back();
  const Object& back() const;
  const Object& front() const;
  void clear() { *this = Myvector<Object>(); }

  typedef Object* iterator;
  typedef const Object* const_iterator;

  iterator begin() { return &mObjects[0]; }
  const_iterator begin() const { return &mObjects[0]; }
  iterator end() { return &mObjects[size()]; }
  const_iterator end() const { return &mObjects[size()]; }

  iterator erase(iterator first, iterator last);
  iterator erase(iterator itemToErase);

 private:
  void setSize(int size);
  void setCapacity(int capacity);

 public:
  // for exception throwing
  class OutOfBoundsException {};
  class VectorEmptyException {};
};

// Myvector method definitions -------------------
// private utilities for member methods
template <class Object>
void Myvector<Object>::setSize(int size) {
  mSize = (size < 0) ? 0 : size;
}

template <class Object>
void Myvector<Object>::setCapacity(int capacity) {
  mCapacity = (capacity <= mSize) ? mSize + m_SPARE_CAPACITY : capacity;
}

// public interface
template <class Object>
Myvector<Object>::Myvector(int initSize) {
  setSize(initSize);
  setCapacity(mSize + m_SPARE_CAPACITY);
  mObjects = new Object[mCapacity];
}

template <class Object>
Myvector<Object>::Myvector(const Myvector<Object>& rhs) {
  mObjects = NULL;  // needed for following
  operator=(rhs);
}

template <class Object>
const Myvector<Object>& Myvector<Object>::operator=(const Myvector& rhs) {
  int k;

  if (this == &rhs) return *this;
  if (mObjects != NULL) delete[] mObjects;

  setSize(rhs.mSize);
  setCapacity(rhs.mCapacity);
  mObjects = new Object[mCapacity];
  for (k = 0; k < mSize; k++) mObjects[k] = rhs.mObjects[k];
  return *this;
}

template <class Object>
void Myvector<Object>::resize(int newSize) {
  if (newSize <= mCapacity) {
    setSize(newSize);
    return;
  }
  reserve(2 * newSize + 1);
  setSize(newSize);
}

template <class Object>
void Myvector<Object>::reserve(int newCapacity) {
  Object* oldObjects;
  int k;

  if (newCapacity < mCapacity) return;

  setCapacity(newCapacity);
  oldObjects = mObjects;
  mObjects = new Object[mCapacity];

  for (k = 0; k < mSize; k++) mObjects[k] = oldObjects[k];
  delete[] oldObjects;
}

template <class Object>
Object& Myvector<Object>::operator[](int index) {
  if (index < 0 || index >= mSize) throw OutOfBoundsException();
  return mObjects[index];
}

template <class Object>
const Object& Myvector<Object>::operator[](int index) const {
  if (index < 0 || index >= mSize) throw OutOfBoundsException();
  return mObjects[index];
}

template <class Object>
void Myvector<Object>::push_back(const Object& x) {
  if (mSize == mCapacity) reserve(2 * mCapacity + 1);
  mObjects[mSize++] = x;
}

template <class Object>
void Myvector<Object>::pop_back() {
  if (mSize > 0) mSize--;
}

template <class Object>
const Object& Myvector<Object>::back() const {
  if (mSize <= 0) throw VectorEmptyException();
  return mObjects[mSize - 1];
}

template <class Object>
const Object& Myvector<Object>::front() const {
  if (mSize <= 0) throw VectorEmptyException();
  return mObjects[0];
}

template <class Object>
Object* Myvector<Object>::erase(iterator first, iterator last) {
  iterator iter1, iter2, retVal, endVal;

  if (first < begin() || last > end() || first >= last) return NULL;

  retVal = first;  // prepare a return value (first element after erase block)
  endVal = end();  // for faster looping

  for (iter1 = first, iter2 = last; iter2 != endVal;)
    *iter1++ = *iter2++;  // objects must have good deep copy management

  setSize(mSize - (last - first));
  return retVal;  // points to first element not erased after block
}

template <class Object>
Object* Myvector<Object>::erase(iterator itemToErase) {
  return erase(itemToErase, itemToErase + 1);
}

#endif