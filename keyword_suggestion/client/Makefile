CC = g++

RM = rm -rf

SRCS = $(wildcard src/*.cc)

BIN = bin/client

FLAGS = -lpthread -g -Wall
REDIS = -lredis++ -lhiredis
JSON = -ljson

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $^ -o $@ $(FLAGS) $(JSON)

.PHONY: clean
clean:
	$(RM) $(BIN)
