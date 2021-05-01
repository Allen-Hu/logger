.PHONY: clean

CPP = g++
CPPFLAGS = -Wall -g

all: hw2 logger

logger.so: hw2.cpp
	$(CPP) $(CPPFLAGS) -shared -fPIC $< -o $@ -ldl

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm -f logger
	rm -f logger.so
