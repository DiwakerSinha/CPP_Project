CXX=clang++
CXX_FLAGS=-std=c++20 -stdlib=libc++ -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc src/kitchen.cc src/bathroom.cc src/living-room.cc src/room.cc
	${CXX} ${CXX_FLAGS} src/main.cc src/kitchen.cc src/bathroom.cc src/living-room.cc src/room.cc -o bin/exec

example: src/example.cc
	${CXX} ${CXX_FLAGS} src/example.cc -o bin/example

bin/tests: tests/tests.cc src/kitchen.cc src/bathroom.cc src/living-room.cc src/room.cc
	${CXX} ${CXX_FLAGS} tests/tests.cc src/kitchen.cc src/bathroom.cc src/living-room.cc src/room.cc -o bin/tests


.DEFAULT_GOAL := exec
.PHONY: clean exec tests


clean:
	rm -fr bin/*
