.PHONY: clean

CPP = g++
CPPFLAGS = -Wall -g

all: hw2 logger

hw2: hw2.cpp

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm logger
