#include <stdbool.h>
#include "infix.h"

// create a new empty character stack
struct char_stack {
    char *items;
    int max_size;
    int top;
};

// create a new empty stack
struct char_stack * char_stack_new(int max_size) {
    struct char_stack * stack = malloc(sizeof(struct char_stack));
    stack->items = calloc(max_size, sizeof(char)); // allocate memory for chars
    stack->max_size = max_size;
    stack->top = 0;
    return stack;
}

// push a value onto the stack
void char_stack_push(struct char_stack * this, char value) {
    if (this->top < this->max_size) { // Ensure we don't overflow the stack
        // put value into the correct position in memory and increments top
        this->items[this->top++] = value;
    }
    // else handle the error for stack overflow
}

// Check if its empty
int char_stack_is_empty(struct char_stack * this) {
    return this->top == 0;
}

// pop a value from the stack
char char_stack_pop(struct char_stack * this) {
    if (!char_stack_is_empty(this)) { // Ensure we don't underflow the stack
        // decrement top and remove and return top item from stack
        return this->items[--this->top];
    }
    // else handle the error for stack underflow
    return 0; // return a null character or handle error appropriately
}

// Peek at the top value of the stack without removing it
char char_stack_peek(struct char_stack *this) {
    if (!char_stack_is_empty(this)) { // Ensure the stack is not empty
        // Return the top item from stack without decrementing top
        return this->items[this->top - 1];
    }
    // else handle the error for an empty stack
    return 0; // return a null character or handle error appropriately
}


bool isNumber(char * token) {
    // loop through token
    int i = 0;
    while (token[i] != '\0') {
        if (!(token[i] >= '0' && token[i] <= '9'))
        {
            return false;
        }
        i++;
    }
    return true;
}

bool isOperator(char character) {
    switch (character) {
        case '+':
        case '-':
        case '/':
        case 'X':
        case '^':
            return true;
        default:
            return false;
    }
}

int assignPrecedence(char a)
{
    switch (a) {
        case '+':
        case '-':
            return 1;
        case 'X':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool hasHigherOrEqualPrecedence(char a, char b) {
    int a_precedence = assignPrecedence(a);
    int b_precedence = assignPrecedence(b);

    if (a_precedence >= b_precedence) {
        return true;
    }
    return false;
}


// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
    struct char_stack * stack = char_stack_new(nargs);
    char * outputString = "";

    printf("got here\n");

    // loop through the input expression one character at a time
    for (int i = 0; i < nargs; ++i) {
        printf("got here 2\n");
        if (args[i][0] == ' ') {
            continue;
        }


        char * token = (char *)malloc(100 * sizeof(char));

//        if (token == NULL) {
//            printf("string init failed\n");
//            return 1;
//        }
        while (args[i][0] != ' ') {
            printf("got here ch = %c\n", args[i][0]);
            char temp[2] = {args[i][0], '\0'};
            strcat(token, temp);
            printf("%s\n", token);
            i++;
        }
        printf("got here 4\n");

        // DEBUG
        printf("DEBUG: ");
        printf("%s\n", token);

        // if token is a number
        if (isNumber(token))
        {
            // append to output string
            strcat(outputString, token);
        }
        else if (token[0] == '(') {
            // push bracket to stack
            char_stack_push(stack, '(');
        }
        else if (isOperator(token[0])) {
            while (true) {
                char op = char_stack_peek(stack);
                bool op_on_top_of_stack = isOperator(op);
                bool op_has_higher_or_equal_precedence = hasHigherOrEqualPrecedence(op, token[0]);
                if (op_on_top_of_stack && op_has_higher_or_equal_precedence) {
                    char temp[2] = {char_stack_pop(stack), '\0'};
                    strcat(outputString, temp);
                }
                else {
                    break;
                }
            }

            char_stack_push(stack, token[0]);
        }
        else if (token[0] == ')') {
            while (char_stack_peek(stack) != '(') {
                char temp[2] = {char_stack_pop(stack), '\0'};
                strcat(outputString, temp);
            }
            char_stack_pop(stack);
        }
    }

    while (!char_stack_is_empty(stack)) {
        char temp[2] = {char_stack_pop(stack), '\0'};
        strcat(outputString, temp);
    }
    return evaluate_postfix_expression(&outputString, strlen(outputString));
}


