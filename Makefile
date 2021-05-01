.PHONY: clean

CPP = g++
CPPFLAGS = -Wall -g -std=c++11

all: logger logger.so

logger.so: hw2.cpp
	$(CPP) $(CPPFLAGS) -shared -fPIC $< -o $@

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm -f logger
	rm -f logger.so
