COMPILER = g++
NAME = server

SRC_FILES = $(shell find ./src -name '*.cpp' && find ./libs/file_helpers -name '*.cpp' && find ./libs/formats -name '*.cpp')
CUSTOM_LIBS = $(shell find ./libs/bin -name '*.a')
INCLUDE_DIRS = -I ./src -I ./libs -I ./codegen
BUILD_FOLDER = build
DEPS = 	g++ valgrind libboost-all-dev libjsoncpp-dev libgtest-dev libcurl4-openssl-dev postgresql postgresql-contrib libpqxx-dev

TESTS_NAME = run_tests
TESTS_FILES = $(shell find ./tests -name '*.cpp')
TESTING_FLAGS = $(INCLUDE_DIRS) -lgtest -lcurl -ljsoncpp -lpqxx -lpq
TEST_MAIN_FILE = tests.cpp

RUN_FLAGS = $(INCLUDE_DIRS) -ljsoncpp -lpqxx -lpq
RUN_MAIN_FILE = main.cpp

CODEGEN_MAIN_FILE = codegen.cpp
CODEGEN_FILES = $(shell find ./codegen -name '*.cpp')
CODEGEN_FLAGS = $(INCLUDE_DIRS) -ljsoncpp
CODEGEN_NAME = codegen_file

.PHONY: all
all: codegen compile run

.PHONY: compile 
compile: $(RUN_MAIN_FILE)
	mkdir -p $(BUILD_FOLDER)
	$(COMPILER) -g $(RUN_MAIN_FILE) $(CUSTOM_LIBS) $(SRC_FILES) -o $(NAME) $(RUN_FLAGS)
	mv $(NAME) $(BUILD_FOLDER)

.PHONY: run
run:
	valgrind ./$(BUILD_FOLDER)/$(NAME)

.PHONY: codegen
codegen: $(CODEGEN_MAIN_FILE)
	mkdir -p $(BUILD_FOLDER)
	$(COMPILER) -g $(CODEGEN_MAIN_FILE) $(CODEGEN_FILES) $(CUSTOM_LIBS) -o $(CODEGEN_NAME) $(CODEGEN_FLAGS)
	sudo mv $(CODEGEN_NAME) $(BUILD_FOLDER)
	valgrind ./$(BUILD_FOLDER)/$(CODEGEN_NAME)

.PHONY: install_deps
install_deps:
	sudo apt-get install $(DEPS) -y

.PHONY: test
test: $(TEST_MAIN_FILE)
	mkdir -p $(BUILD_FOLDER)
	$(COMPILER) -g $(TEST_MAIN_FILE) $(SRC_FILES) $(TESTS_FILES) $(CUSTOM_LIBS) -o $(TESTS_NAME) $(TESTING_FLAGS)
	sudo mv $(TESTS_NAME) $(BUILD_FOLDER)
	valgrind ./$(BUILD_FOLDER)/$(TESTS_NAME)

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
