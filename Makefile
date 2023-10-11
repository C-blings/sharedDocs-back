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
install_deps: docker_install
	apt-get intsall g++ -y
	apt-get install valgrind -y
	apt-get install libboost-all-dev

.PHONY: clean
clean:
	rm $(NAME)

docker_install:
	sudo apt install apt-transport-https ca-certificates curl gnupg2 software-properties-common
	curl -fsSL https://download.docker.com/linux/debian/gpg | sudo apt-key add -
	sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/debian $(lsb_release -cs) stable"
	apt-cache policy docker-ce
	sudo apt install docker-ce
