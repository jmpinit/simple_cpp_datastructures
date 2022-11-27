#ifndef H_CIRCULAR_LIST
#define H_CIRCULAR_LIST

#include <stddef.h>
#include <stdbool.h>
#include "optional.hpp"

using nonstd::optional;

template <typename T, size_t N>
class CircularList {
public:
  CircularList() : readIndex(0), writeIndex(0) {}

  bool write(T data) {
    if (isFull()) {
      // List is full, don't overwrite
      return false;
    }

    nodes[writeIndex] = data;

    writeIndex += 1;
    writeIndex %= N;

    itemCount += 1;

    return true;
  }

  optional<T> read() {
    if (isEmpty()) {
      return {};
    }

    T data = nodes[readIndex];

    readIndex += 1;
    readIndex %= N;

    itemCount -= 1;

    return data;
  }

  bool isEmpty() {
    return itemCount == 0;
  }

  bool isFull() {
    return itemCount == N;
  }

private:
  int itemCount;
  size_t length = N;
  T nodes[N];
  int readIndex;
  int writeIndex;
};

#endif
