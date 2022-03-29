CC = g++

all: bin

bin: main.cpp
	$(CC) $< -o $@

.PHONY: run clean

run:
	./bin

clean:
	rm bin