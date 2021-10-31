CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: obj/main.o obj/queue.o
	mkdir -p bin
	${CXX} ${CXX_FLAGS} obj/main.o obj/queue.o -o bin/exec

obj/main.o: src/main.cc obj/queue.o includes/queue.hpp
	${CXX} ${CXX_FLAGS} -c src/main.cc -o obj/main.o

bin/tests: obj/catch.o tests/tests.cc obj/queue.o
	mkdir -p bin
	$(CXX) $(CXX_FLAGS) $^ -o $@

obj/catch.o: tests/catch.cc
	mkdir -p obj
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

obj/queue.o: includes/queue.hpp src/queue.cc
	${CXX} ${CXX_FLAGS} -c src/queue.cc -o obj/queue.o


.DEFAULT_GOAL := exec
.PHONY: exec tests clean
clean:
	rm -f bin/* obj/*
