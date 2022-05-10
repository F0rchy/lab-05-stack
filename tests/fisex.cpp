#include <gtest/gtest.h>
#include <string>
#include "fisex.hpp"
#include "secex.hpp"

TEST(FirstStack, ConstructorTest) {
  Stack<int> stack(234);
  ASSERT_EQ(stack.head(), 234);
}

TEST(FirstStack, RValuePushTest) {
  Stack<int> stack;
  stack.push(25);
  stack.push(15);
  stack.push(407);
  stack.push(36);
  ASSERT_EQ(stack.head(), 36);
}

static const int firstInt = 11;
static const int secondInt = 22;
static const int thirdInt = 33;
TEST(FirstStack, LValuePushTest) {
  Stack<int> stack;
  stack.push(firstInt);
  stack.push(secondInt);
  stack.push(thirdInt);
  ASSERT_EQ(stack.head(), 33);
}

TEST(FirstStack, popTest) {
  Stack<int> stack;
  stack.push(14);
  stack.push(61);
  stack.push(87);
  stack.push(63);
  stack.pop();
  stack.pop();
  stack.pop();
  ASSERT_EQ(stack.head(), 14);
}

TEST(FirstStack, MovementOperatorTest) {
  Stack<int> stack = Stack<int>(114);
  ASSERT_EQ(stack.head(), 114);
}

class SomeType {
 private:
  int f;
  double ft;

 public:
  SomeType() {
    f = -1;
    ft = -1;
  }

  SomeType(int fi) {
    this->f = fi;
    this->ft = 0;
  }

  SomeType(int fi, double fth) {
    this->f = fi;
    this->ft = fth;
  }

  bool operator!() const {
    if (this->f != -1) {
      return false;
    }
    if (this->ft != -1) {
      return false;
    }
    return true;
  };

  SomeType& operator=(SomeType* right) noexcept {
    f = right->f;
    ft = right->ft;
    return *this;
  }

  SomeType& operator=(const SomeType& right) = default;

  void print() const {
    std::cout << f << " " << ft << std::endl;
  }

  std::string string() const {
    std::string a = std::to_string(f) + " " + std::to_string(ft);
    return a;
  }
};

TEST(Stack2Test, pushEmplaceTest) {
  StackSec<SomeType> stack2(SomeType{11 });
  stack2.push_emplace(22, 22.0);
  stack2.push_emplace(13);
  stack2.push_emplace(33, 33.0);
  ASSERT_EQ(stack2.head().string(), "33 33.000000");
}
