.PHONY: clean
all: run

run: compile
	./a1 < input

compile: a1.cpp
	g++ -o a1 a1.cpp

clean:
	rm -f a1 *.o