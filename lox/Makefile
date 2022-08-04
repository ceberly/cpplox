FLAGS=-std=c++11 -Wall -Werror -Wextra --pedantic -g -O2

token.o: token.cc token.h
	clang++ ${FLAGS} -c token.cc

lox: main.cc
	clang++ ${FLAGS} main.cc -o lox
