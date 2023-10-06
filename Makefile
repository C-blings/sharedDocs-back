COMPILER = g++
NAME = server

.PHONY: all
all: compile run

.PHONY: compile 
compile: 
	$(COMPILER) -g main.cpp $(shell find ./src -name '*.cpp') -o $(NAME)

.PHONY: run
run: $(NAME)
	valgrind ./$^

.PHONY: clean
clean:
	rm $(NAME)