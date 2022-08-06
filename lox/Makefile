FLAGS=-std=c++17 -Wall -Werror -Wextra --pedantic -g -O2

lox.o: lox.cc lox.h
	clang++ ${FLAGS} -c lox.cc

token.o: token.cc token.h
	clang++ ${FLAGS} -c token.cc

scanner.o: scanner.cc scanner.h token.o
	clang++ ${FLAGS} -c scanner.cc

lox: main.cc lox.o scanner.o
	clang++ ${FLAGS} main.cc lox.o scanner.o -o lox
