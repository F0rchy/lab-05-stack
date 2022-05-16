// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#ifndef INCLUDE_SECEX_HPP_
#define INCLUDE_SECEX_HPP_
#include <stdexcept>
#include <utility>

#include "first.hpp"

template <typename T>
class StackSec {
 private:
  Element<T>* last;
  Element<T>* start;
  bool notDeleted = true;

 public:
  StackSec() {
    start = new Element<T>;
    last = start;
  }

  explicit StackSec(T&& valueStart) {
    start = new Element<T>;
    start->value = valueStart;
    start->link = nullptr;
    last = start;
  }

  explicit StackSec(const T& valueStart) = delete;

  ~StackSec() {
    Element<T>* temp;
    if (notDeleted) {
      while (start->link) {
        temp = start;
        while (temp->link != last) {
          temp = temp->link;
        }
        if (last) {
          delete (last);
          temp->link = nullptr;
        }
        last = temp;
      }
      if (last) {
        delete (last);
      }
      notDeleted = false;
    }
  }

  template <typename... Args>
  void push_emplace(Args&&... args) {
    if (!start->value) {
      last->value = {std::forward<Args>(args)...};
      last->link = nullptr;
      return;
    }
    Element<T>* temp = new Element<T>;
    last->link = temp;
    temp->value = {std::forward<Args>(args)...};
    temp->link = nullptr;
    last = temp;
  }

  void push(T&& value) {
    if (!start->value) {
      last->value = std::move(value);
      last->link = nullptr;
      return;
    }
    Element<T>* temp = new Element<T>;
    temp->value = std::move(value);
    temp->link = nullptr;
    last = temp;
  }

  const T& head() const { return last->value; }

  T pop() {
    if (!start->link) {
      T value = last->value;
      return value;
    } else {
      Element<T>* temp = start;
      while (temp->link != last) {
        temp = temp->link;
      }
      T value = last->value;
      if (last) {
        delete (last);
        temp->link = nullptr;
      }
      last = temp;
      return value;
    }
  }

  Stack<T>& operator=(const Stack<T>& right) = delete;

  Stack<T>& operator=(Stack<T>&& right) {
    if ((start != right.start) || (last != right.last)) {
      ~StackSec();
      start = std::move(right.start);
      last = std::move(right.last);
      notDeleted = true;
    }
    return *this;
  }
};

#endif  // INCLUDE_SECEX_HPP_
