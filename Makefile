.PHONY: clean

CPP = g++
CPPFLAGS = -Wall -g

all: hw2 logger

logger.so: hw2.cpp
	$(CPP) $(CPPFLAGS) -c -fPIC $< -o $@

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm -f logger
	rm -f logger.so
