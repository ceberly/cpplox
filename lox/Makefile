FLAGS=-std=c++17 -Wall -Werror -Wextra --pedantic -g -O2

format:
	clang-format -i *.cc *.h

token.o: token.cc token.h
	clang++ ${FLAGS} -c token.cc

scanner.o: scanner.cc scanner.h
	clang++ ${FLAGS} -c scanner.cc

lox: main.cc token.o scanner.o
	clang++ ${FLAGS} lox.cc main.cc scanner.o token.o -o lox

expr_gen: expr_gen.cc
	clang++ ${FLAGS} expr_gen.cc -o expr_gen
