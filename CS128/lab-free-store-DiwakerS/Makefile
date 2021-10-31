CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Iincludes/

.PHONY: clean

part1: src/part1.cc src/util1.cc
	${CXX} ${CXX_FLAGS} src/part1.cc src/util1.cc -o bin/part1

part2: src/part2.cc src/util2.cc src/util1.cc
	${CXX} ${CXX_FLAGS} src/part2.cc src/util2.cc src/util1.cc -o bin/part2

clean:
	rm -rf bin/*
