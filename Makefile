COMPILER = g++
NAME = server

.PHONY: all
all: compile run

.PHONY: compile 
compile: 
	$(COMPILER) main.cpp $(shell find ./src -name '*.cpp') -o $(NAME)
	echo $(shell find ./src -name '*.cpp')

.PHONY: run
run: $(NAME)
	./$^

.PHONY: clean
clean:
	rm $(NAME)