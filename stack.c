#include "stack.h"

// create a new empty stack
struct double_stack * double_stack_new(int max_size) {
    struct double_stack * stack = malloc(sizeof(struct double_stack));
    stack->items = calloc(max_size, sizeof(double));
    stack->max_size = max_size;
    stack->top = 0;
    return stack;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
    // put value into the correct position in memory and increments top
    this->items[this->top++] = value;
}

// Check if its empty
int double_stack_is_empty(struct double_stack * this) {
    return this->top == 0;
}


// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
    // decrement top and remove and return top item from stack
    return this->items[--this->top];
}
