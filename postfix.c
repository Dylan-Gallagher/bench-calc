#include <stdlib.h>
#include <math.h>
#include "postfix.h"
#include "stack.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {

    struct double_stack * stack = double_stack_new(nargs);
    // for each token in the input string
    for (int i = 0; i < nargs; ++i) {
        // if token is a number
        if ((args[i][0] >= '0' && args[i][0] <= '9') ||
        (args[i][0] == '-' && (args[i][1]  >= '0' && args[i][1] <= '9')))
        {
            // push token onto the stack
            double num = atof(args[i]);
            double_stack_push(stack, num);
        }
        // else if token is an operator
        else if (args[i][0] == '+' || args[i][0] == '-' || args[i][0] == 'X' || args[i][0] == '/' || args[i][0] == '^')
        {
            // apply the operator and store in num1
            double num1 = double_stack_pop(stack);
            double num2 = double_stack_pop(stack);

            if (args[i][0] == '+') {
                num2 += num1;
            }

            if (args[i][0] == '-') {
                num2 -= num1;
            }

            if (args[i][0] == 'X') {
                num2 *= num1;
            }

            if (args[i][0] == '/') {
                num2 /= num1;
            }

            if (args[i][0] == '^') {
                num2 = pow(num2, num1);
            }

            // push the result into the stack
            double_stack_push(stack, num2);
            }
    }
    return double_stack_pop(stack);
}
