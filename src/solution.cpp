#include "solution.h"
#include "StackDynamicArray.h"

bool openingBracket(char value) {
    switch (value) {
        case '(':
        case '{':
        case '[':
            return true;
    }
    return false;
}

bool closingBracket(char value) {
    switch (value) {
        case ')':
        case '}':
        case ']':
            return true;
    }
    return false;
}

bool correctBrackets(char openingBracket, char closingBracket) {
    if (openingBracket == '(' && closingBracket == ')')
        return true;
    else if (openingBracket == '{' && closingBracket == '}')
        return true;
    else if (openingBracket == '[' && closingBracket == ']')
        return true;
    return false;
}

bool isCorrect(const char *expression) {
    if (!expression)
        return false;

    StackDynamicArray<char> stack;

    for (char value = *expression; value != '\0'; value = *(++expression))
        if (openingBracket(value))
            stack.push(value);
        else if (closingBracket(value))
            if (stack.empty() || !correctBrackets(stack.peek(), value))
                return false;
            else stack.pop();

    return stack.empty();
}
