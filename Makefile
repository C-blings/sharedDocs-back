COMPILER = g++
NAME = server

.PHONY: all 
all: 
	$(COMPILER) main.cpp Web/TCPServer/* -o $(NAME)
	./$(NAME)

.PHONY: clean
clean:
	rm $(Name)