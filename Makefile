COMPILER = g++
NAME = server

.PHONY: all
all: compile run

.PHONY: compile 
compile: 
	$(COMPILER) main.cpp $(shell find /src -name '*.cpp') -o $(NAME)

.PHONY: run
run: $(NAME)
	./$^

.PHONY: clean
clean:
	rm $(NAME)