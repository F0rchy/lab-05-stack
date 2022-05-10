//
// Created by forchy on 10.05.22.
//

#ifndef INCLUDE_SECEX_HPP_
#define INCLUDE_SECEX_HPP_
#include <stdexcept>
#include <utility>

#include "fisex.hpp"

template <typename T>
class StackSec {
 private:
  Element<T>* last;
  Element<T>* start;
  bool notDeleted = true;

 public:
  StackSec() {
    this->start = new Element<T>;
    this->last = this->start;
  }

  explicit StackSec(T&& valueStart) {
    this->start = new Element<T>;
    start->value = valueStart;
    start->link = nullptr;
    this->last = this->start;
  }

  explicit StackSec(const T& valueStart) = delete;

  ~StackSec() {
    Element<T>* temp;
    if (this->notDeleted) {
      while (this->start->link) {
        temp = this->start;
        while (temp->link != this->last) {
          temp = temp->link;
        }
        if (last) {
          delete (last);
          temp->link = nullptr;
        }
        this->last = temp;
      }
      if (last) {
        delete (last);
      }
      this->notDeleted = false;
    }
  }

  template <typename... Args>
  void push_emplace(Args&&... args) {
    if (!this->start->value) {
      last->value = {std::forward<Args>(args)...};
      last->link = nullptr;
      return;
    }
    Element<T>* temp = new Element<T>;
    last->link = temp;
    temp->value = {std::forward<Args>(args)...};
    temp->link = nullptr;
    this->last = temp;
  }

  void push(T&& value) {
    if (!this->start->value) {
      last->value = std::move(value);
      last->link = nullptr;
      return;
    }
    Element<T>* temp = new Element<T>;
    temp->value = std::move(value);
    temp->link = nullptr;
    this->last = temp;
  }

  const T& head() const { return this->last->value; }

  T pop() {
    if (!this->start->link) {
      T value = last->value;
      return value;
    } else {
      Element<T>* temp = this->start;
      while (temp->link != this->last) {
        temp = temp->link;
      }
      T value = last->value;
      if (last) {
        delete (last);
        temp->link = nullptr;
      }
      this->last = temp;
      return value;
    }
  }

  Stack<T>& operator=(const Stack<T>& right) = delete;

  Stack<T>& operator=(Stack<T>&& right) {
    if ((this->start != right.start) || (this->last != right.last)) {
      this->~Stack();
      this->start = std::move(right.start);
      this->last = std::move(right.last);
      notDeleted = true;
    }
    return *this;
  }
};

#endif  // INCLUDE_SECEX_HPP_
