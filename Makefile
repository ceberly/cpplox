# https://nullprogram.com/blog/2023/04/29/
CFLAGS=-O2 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion\
			 -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion\
			 -fsanitize=undefined  -fsanitize=address -fsanitize-trap -std=c++17

SRC=src/lox.cc src/mmap_file.cc src/scanner.cc src/token.cc
HEADERS=src/mmap_file.h src/scanner.h src/token.h

default:
	g++ ${CFLAGS} ${SRC} -o lox

format:
	clang-format -i ${SRC} ${HEADERS}
