.PHONY: clean pack

CPP = g++
CPPFLAGS = -Wall -g -std=c++11

all: logger logger.so

logger.so: hw2.cpp
	$(CPP) $(CPPFLAGS) -shared -fPIC $< -o $@ -ldl

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm -f logger
	rm -f logger.so

pack: clean
	zip -r 0713407_hw2.zip . -x ".git*" -x ".DS_Store"
