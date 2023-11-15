COMPILER = g++
NAME = server
TESTS_NAME = run_tests
SRC_FILES = $(shell find ./src -name '*.cpp')
TESTS_FILES = $(shell find ./tests -name '*.cpp')
CUSTOM_LIBS = $(shell find ./libs/bin -name '*.a')
TESTING_FLAGS = -lgtest -lcurl
RUN_MAIN_FILE = main.cpp
TEST_MAIN_FILE = tests.cpp
BUILD_FOLDER = build
DEPS = 	g++ valgrind libboost-all-dev libjsoncpp-dev libgtest-dev libcurl4-openssl-dev postgresql postgresql-contrib

.PHONY: all
all: test compile run

.PHONY: compile 
compile: $(RUN_MAIN_FILE)
	mkdir -p $(BUILD_FOLDER)
	$(COMPILER) -g $(RUN_MAIN_FILE) $(CUSTOM_LIBS) $(SRC_FILES) -o $(NAME)
	mv $(NAME) $(BUILD_FOLDER)

.PHONY: run
run:
	valgrind ./$(BUILD_FOLDER)/$(NAME)

.PHONY: install_deps
install_deps:
	sudo apt-get install $(DEPS) -y

.PHONY: clean
clean:
	rm -f $(BUILD_FOLDER)/$(NAME)
	rm -f $(BUILD_FOLDER)/$(TESTS_NAME)

docker_install:
	sudo apt install apt-transport-https ca-certificates curl gnupg2 software-properties-common
	curl -fsSL https://download.docker.com/linux/debian/gpg | sudo apt-key add -
	sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/debian $(lsb_release -cs) stable"
	apt-cache policy docker-ce
	sudo apt install docker-ce

.PHONY: test
test: $(TEST_MAIN_FILE)
	mkdir -p $(BUILD_FOLDER)
	$(COMPILER) -g $(TEST_MAIN_FILE) $(SRC_FILES) $(TESTS_FILES) $(CUSTOM_LIBS) -o $(TESTS_NAME) $(TESTING_FLAGS)
	sudo mv $(TESTS_NAME) $(BUILD_FOLDER)
	valgrind ./$(BUILD_FOLDER)/$(TESTS_NAME)

