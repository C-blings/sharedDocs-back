COMPILER = g++

BINARIES_PATH = ./bin
FLAGS = -c

FILE_HELPERS_NAME = file_helpers
FILE_HELPERS_FILES = $(shell find ./file_helpers -name "*.cpp")

LOGGING_NAME = logging
LOGGING_FILES = $(shell find ./logging -name "*.cpp")

FORMATS_NAME = formats
FORMATS_FILES = $(shell find ./formats -name "*.cpp")

.PHONY: all
all: file_helpers logging formats

.PHONY: file_helpers
file_helpers:
	$(COMPILER) $(FLAGS) $(FILE_HELPERS_FILES)
	ar rcs lib$(FILE_HELPERS_NAME).a *.o
	sudo mv lib$(FILE_HELPERS_NAME).a $(BINARIES_PATH)
	rm *.o

.PHONY: logging
logging:
	$(COMPILER) $(FLAGS) $(LOGGING_FILES)
	ar rcs lib$(LOGGING_NAME).a *.o
	sudo mv lib$(LOGGING_NAME).a $(BINARIES_PATH)
	rm *.o

.PHONY: formats
formats:
	$(COMPILER) $(FLAGS) $(FORMATS_FILES)
	ar rcs lib$(FORMATS_NAME).a *.o
	sudo mv lib$(FORMATS_NAME).a $(BINARIES_PATH)
	rm *.o

.PHONY: clean
clean:
	sudo rm *.o
	sudo rm -R -p $(BINARIES_PATH)/*