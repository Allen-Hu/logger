.PHONY: clean pack

CPP = g++
CPPFLAGS = -Wall -g -std=c++11
ZIPNAME = 0713407_hw2.zip

all: logger logger.so

logger.so: hw2.cpp
	$(CPP) $(CPPFLAGS) -shared -fPIC $< -o $@ -ldl

logger: logger.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm -f logger
	rm -f logger.so
	rm -f $(ZIPNAME)

pack: clean
	zip -r $(ZIPNAME) . -x ".git*" -x ".DS_Store"
