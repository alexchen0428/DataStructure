# Makefile for compiling the program test_heap
# variable definition

CC = g++
MAINSRCS = a3.cpp
OTHSRCS =
HEADERS = priority_queue.h unsorted_heap.h binary_heap.h fib_heap_p.h
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = main #$(MAINSRCS:.cpp=)
MEMCHECKARGS = 

CFLAGS = -g -Wall -o2

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
