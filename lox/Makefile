FLAGS=-std=c++11 -Wall -Werror -Wextra --pedantic -g -O2

token.o: token.cc token.h
	clang++ ${FLAGS} -c token.cc

scanner.o: scanner.cc scanner.h token.o
	clang++ ${FLAGS} -c scanner.cc

lox: main.cc scanner.o
	clang++ ${FLAGS} main.cc scanner.o -o lox
