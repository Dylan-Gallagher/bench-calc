#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "postfix.h"
#include "infix.h"

void test_stack(int count, char ** parameters) {
  struct double_stack * stack = double_stack_new(count);
  memset(stack->items, 0, count * sizeof(double));
  double element;
  for (int i = 0; i < count; i++) {
    element = atof(parameters[i]);
    double_stack_push(stack, element);
    printf("Pushed %f to stack\n", element);
  }
  for (int i = count - 1; i >= 0; i--) {
    element = double_stack_pop(stack);
    printf("Popped %f from stack\n", element);
    if ( atof(parameters[i]) != element ) {
      fprintf(stderr, "Error: %f popped from stack, but the original pushed value is %f\n",
	      element, atof(parameters[i]));
    }
  }
}

int main(int argc, char ** argv) {
  if ( argc == 1 ) {
    // command line contains only the name of the program
    printf("Error: No command line parameters provided\n");
    printf("Usage: %s stack <numeric values>\n", argv[0]);
    printf("Usage: %s postfix <postfix expression>\n", argv[0]);
    printf("Usage: %s infix <infix expression>\n", argv[0]);
    exit(1);
  }
  else if ( argc == 2 ) {
    // command line contains name of prog and one other parameter
    printf("Error: Too few command-line parameters\n");
    printf("Usage: %s stack <numeric values>\n", argv[0]);
    printf("Usage: %s postfix <postfix expression>\n", argv[0]);
    printf("Usage: %s infix <infix expression>\n", argv[0]);
    exit(1);
  }
  else {
    // command line has enough parameters for an expression
    double result;
    if ( strcmp(argv[1], "stack") == 0 ) {
      // pass the command line parameters, but with the first two removed
      test_stack(argc - 2, argv + 2);
    }
    else if ( strcmp(argv[1], "postfix") == 0 ) {
      // pass the command line parameters, but with the first two removed
      result = evaluate_postfix_expression(argv+2, argc-2);
      printf("\nResult is %lf\n", result);
    }
    else if ( strcmp(argv[1], "infix") == 0 ) {
      // pass the command line parameters, but with the first two removed
      result = evaluate_infix_expression(argv+2, argc-2);
      printf("\nResult is %lf\n", result);
    }
    else {
      printf("Error: Valid choices are stack, infix or postfix\n");
      printf("Usage: %s stack <numeric values>\n", argv[0]);
      printf("Usage: %s postfix <postfix expression>\n", argv[0]);
      printf("Usage: %s infix <infix expression>\n", argv[0]);
      exit(1);
    }

    return 0;
  }
}
