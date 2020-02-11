SOURCES:= $(wildcard *.c) $(wildcard *.h)
OBJECTS:= $(wildcard *.c)
OUT:= bin/trade-position
main: $(SOURCES)
	cc -W -Wall -g -o $(OUT) $(OBJECTS)
