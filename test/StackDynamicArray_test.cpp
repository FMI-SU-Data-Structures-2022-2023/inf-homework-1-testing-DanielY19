#include "catch2/catch_all.hpp"
#include "StackDynamicArray.h"

TEST_CASE("Testing the functionality of my implementation of a Stack(DynamicArray)!") {
    StackDynamicArray<int> stack;
    SECTION("When a stack is defined(with default ctor), it should be empty!") {
        REQUIRE(stack.empty());
        REQUIRE_THROWS_AS(stack.peek(), std::logic_error);
        REQUIRE_THROWS_AS(stack.pop(), std::logic_error);
    }SECTION("When we push elements into the stack, the most recent element we pushed, should be on peek()") {
        stack.push(1);
        stack.push(2);
        stack.push(3);
        REQUIRE(stack.peek() == 3);
        REQUIRE_FALSE(stack.empty());
    }SECTION(
            "When we push elements into the stack and the top element is popped, the second top element should be on peek()") {
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.pop();
        REQUIRE(stack.peek() == 3);
        REQUIRE_FALSE(stack.empty());
    }SECTION("When we define a stack(with the copy ctor), it should be exactly as the copied stack!") {
        stack.push(1);
        stack.push(2);
        stack.push(3);
        StackDynamicArray<int> copyStack(stack);
        REQUIRE_FALSE(copyStack.empty());

        while (!copyStack.empty()) {
            REQUIRE(copyStack.peek() == stack.peek());
            copyStack.pop();
            stack.pop();
        }

        REQUIRE(copyStack.empty());
        REQUIRE(stack.empty());
    }SECTION(
            "When we have defined a que(with the default ctor), and then use the assignment operator, it should be exactly as the copied stack!") {
        StackDynamicArray<int> copyStack;

        stack.push(1);
        stack.push(2);
        stack.push(3);

        copyStack = stack;
        REQUIRE_FALSE(copyStack.empty());

        while (!copyStack.empty()) {
            REQUIRE(copyStack.peek() == stack.peek());
            copyStack.pop();
            stack.pop();
        }

        REQUIRE(copyStack.empty());
        REQUIRE(stack.empty());
    }
}

