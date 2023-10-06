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

.PHONY: install_deps
install_deps:
	apt-get install libboost-all-dev

.PHONY: clean
clean:
	rm $(NAME)