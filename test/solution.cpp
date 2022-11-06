#include "catch2/catch_all.hpp"
#include "solution.h"

TEST_CASE("isCorrect() recognizes correct expressions")
{
    SECTION("Empty expression") {
        REQUIRE(isCorrect(""));
    } SECTION("No brackets") {
        REQUIRE(isCorrect("abc"));
    } SECTION("One pair of brackets") {
        REQUIRE(isCorrect("(abc)"));
    } SECTION("Multiple brackets") {
        REQUIRE(isCorrect("(((abc)))"));
    } SECTION("Mixed brackets") {
        REQUIRE(isCorrect("([abc])"));
    } SECTION("Complex expression") {
        REQUIRE(isCorrect("((abc) { abc }(((def)))def)"));
    } SECTION("Single pair of brackets") {
        REQUIRE(isCorrect("()"));
    } SECTION("Brackets-only") {
        REQUIRE(isCorrect("((()))"));
    } SECTION("Brackets next to each other") {
        REQUIRE(isCorrect("{}[](){}[]()"));
    }
}

TEST_CASE("isCorrect() recognizes when an expression is incorrect")
{
    SECTION("No closing bracket") {
        REQUIRE_FALSE(isCorrect("(abc"));
    } SECTION("No closing bracket and multiple brackets") {
        REQUIRE_FALSE(isCorrect("(((abc))"));
    } SECTION("No opening bracket") {
        REQUIRE_FALSE(isCorrect("abc)"));
    } SECTION("No opening bracket and mutliple brackets") {
        REQUIRE_FALSE(isCorrect("(abc))"));
    } SECTION("Single opening bracket") {
        REQUIRE_FALSE(isCorrect("("));
    } SECTION("Single closing bracket") {
        REQUIRE_FALSE(isCorrect(")"));
    } SECTION("Bracket types do not match") {
        REQUIRE_FALSE(isCorrect("{abc]"));
    } SECTION("Overlapping bracket sub-expressions") {
        REQUIRE_FALSE(isCorrect("(abcdef[)]"));
    }
}

TEST_CASE("Testing opening bracket recognition for openingBracket()") {
    SECTION("Testing correctness of function for opening brackets") {
        REQUIRE(openingBracket('('));
        REQUIRE(openingBracket('{'));
        REQUIRE(openingBracket('['));
    }SECTION("Testing correctness of function for non correct arguments") {
        REQUIRE_FALSE(openingBracket(']'));
        REQUIRE_FALSE(openingBracket('}'));
        REQUIRE_FALSE(openingBracket(')'));
        REQUIRE_FALSE(openingBracket('A'));
        REQUIRE_FALSE(openingBracket('C'));
    }
}

TEST_CASE("Testing closing bracket recognition for closingBracket()") {
    SECTION("Testing correctness of function for closing brackets") {
        REQUIRE(closingBracket(')'));
        REQUIRE(closingBracket('}'));
        REQUIRE(closingBracket(']'));
    }SECTION("Testing correctness of function for non correct arguments") {
        REQUIRE_FALSE(closingBracket('['));
        REQUIRE_FALSE(closingBracket('{'));
        REQUIRE_FALSE(closingBracket('('));
        REQUIRE_FALSE(closingBracket('A'));
        REQUIRE_FALSE(closingBracket('C'));
    }
}

TEST_CASE("Testing matching mechanism for brackets with correctBrackets()") {
    SECTION("Testing matching of brackets") {
        REQUIRE(correctBrackets('(', ')'));
        REQUIRE(correctBrackets('{', '}'));
        REQUIRE(correctBrackets('[', ']'));
    }SECTION("Testing non-matching arguments") {
        REQUIRE_FALSE(correctBrackets('[', '}'));
        REQUIRE_FALSE(correctBrackets('(', ']'));
        REQUIRE_FALSE(correctBrackets('{', ')'));
        REQUIRE_FALSE(correctBrackets('A', ']'));
    }
}
