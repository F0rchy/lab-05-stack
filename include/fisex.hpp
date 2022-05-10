// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#ifndef INCLUDE_FISEX_HPP_
#define INCLUDE_FISEX_HPP_
#include <stdexcept>
#include <utility>

template <typename T>
struct Element {
  T value;
  Element* link;
};

template <typename T>
class Stack {
 private:
  Element<T>* last;
  Element<T>* start;
  bool notDeleted;

 public:
  Stack() {
    this->start = new Element<T>;
    this->last = this->start;
    this->notDeleted = true;
  }

  explicit Stack(T&& valueStart) {
    this->notDeleted = true;
    this->start = new Element<T>;
    start->value = valueStart;
    start->link = nullptr;
    this->last = this->start;
  }

  explicit Stack(T& value) = delete;

  ~Stack() {
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

  void push(T&& value) {
    if (!this->start->value) {
      start->value = std::move(value);
      start->link = nullptr;
      this->last = this->start;
      return;
    }
    Element<T>* temp = new Element<T>;
    last->link = temp;
    temp->value = std::move(value);
    temp->link = nullptr;
    this->last = temp;
  }

  void push(const T& value) {
    if (!this->start->value) {
      last->value = value;
      last->link = nullptr;
      this->start = this->last;
      return;
    }
    Element<T>* temp = new Element<T>;
    last->link = temp;
    temp->value = value;
    temp->link = nullptr;
    this->last = temp;
  }

  void pop() {
    if (!this->start->link) {
      return;
    } else {
      Element<T>* temp = this->start;
      while (temp->link != this->last) {
        temp = temp->link;
      }
      if (last) {
        delete (last);
        temp->link = nullptr;
      }
      this->last = temp;
      return;
    }
  }

  const T& head() const { return this->last->value; }

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

auto example() -> void;

#endif  // INCLUDE_FISEX_HPP_
