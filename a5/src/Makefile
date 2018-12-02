# Makefile for compiling the program test_heap
# variable definition

CC = g++
MAINSRCS = a5.cpp
OTHSRCS = graph.cpp
HEADERS = graph.h
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = main #$(MAINSRCS:.cpp=)
MEMCHECKARGS = 

CFLAGS = -g -Wall -O2

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) < ../test/g6.in > result.txt $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
