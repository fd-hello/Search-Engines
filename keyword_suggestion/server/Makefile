CC = g++

RM = rm -rf

SRCS_OFFLINE = $(wildcard src/offline/*.cc)
SRCS_ONLINE = $(wildcard src/online/*.cc)
SRCS_MYTASK = $(wildcard src/online/myTask/*.cc)

BIN_OFFLINE = bin/dictionary
BIN_ONLINE = bin/server

FLAGS = -lpthread -g -Wall
REDIS = -lredis++ -lhiredis
JSON = -ljson

all: $(BIN_OFFLINE) $(BIN_ONLINE)

$(BIN_OFFLINE): $(SRCS_OFFLINE)
	$(CC) $^ -o $@ $(FLAGS)

$(BIN_ONLINE): $(SRCS_ONLINE) $(SRCS_MYTASK)
	$(CC) $^ -o $@ $(FLAGS) $(REDIS) $(JSON)

.PHONY: clean
clean:
	$(RM) $(BIN_OFFLINE)
	$(RM) $(BIN_ONLINE)
