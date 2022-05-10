#include <example.hpp>
#include "iostream"

int main() {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  stack.push(40);
  std::cout << stack.head() << std::endl;
  stack.pop();
  std::cout << stack.head() << std::endl;
  stack.pop();
  std::cout << stack.head() << std::endl;
  stack.pop();
  std::cout << stack.head() << std::endl;
}