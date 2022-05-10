// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <stdexcept>

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

 public:
  Stack(){
    this->last = (Element<T>*)malloc(sizeof(Element<T>));
    this->start = (Element<T>*)malloc(sizeof(Element<T>));
  };

  Stack(T valueStart) {
    this->last = (Element<T>*)malloc(sizeof(Element<T>));
    this->start = (Element<T>*)malloc(sizeof(Element<T>));
    last->value = valueStart;
    last->link = NULL;
    this->start = this->last;
  }

  void push(T&& value) {
    if (!this->start->value) {
      last->value = std::move(value);
      last->link = NULL;
      this->start = this->last;
      return;
    }
    Element<T>* temp;
    Element<T>* oldlink;
    temp = (Element<T>*)malloc(sizeof(Element<T>));
    oldlink = last->link;
    last->link = temp;
    temp->value = std::move(value);
    temp->link = oldlink;
    this->last = temp;
  };

  void push(const T& value) {
    Element<T>* temp;
    Element<T>* oldlink;
    temp = (Element<T>*)malloc(sizeof(Element<T>));
    oldlink = last->link;
    last->link = temp;
    temp->value = value;
    temp->link = oldlink;
    this->last = temp;
  };

  void pop() {
    Element<T>* temp;
    temp = this->start;
    while (temp->link != this->last) {
      temp = temp->link;
    }
    temp->link = last->link;
    free(last->link);
    this->last = temp;
  };
  const T& head() const {
    return this->last->value;
  }
};

auto example() -> void;

#endif // INCLUDE_EXAMPLE_HPP_
