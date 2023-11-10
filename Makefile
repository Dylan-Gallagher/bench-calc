all: main-calc.c infix.c postfix.c stack.c infix.h postfix.h stack.h
	gcc -Wall -O0 -lm -g -o calc main-calc.c infix.c postfix.c stack.c

sanitize_all: main-calc.c infix.c postfix.c stack.c infix.h postfix.h stack.h
	gcc -Wall -O0 -lm -g -o calc -fsanitize=address main-calc.c infix.c postfix.c stack.c

stack: main-stack.c stack.c stack.h
	gcc -Wall -O0 -lm -g -o calc main-stack.c stack.c

sanitize_stack: main-stack.c stack.c stack.h
	gcc -Wall -O0 -lm -g -o calc -fsanitize=address main-stack.c stack.c



test-stack: all
	./calc stack 3 5 2 8
