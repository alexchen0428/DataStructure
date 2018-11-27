# Makefile for compiling the program test_heap
# variable definition

CC = g++
MAINSRCS = a4.cpp
OTHSRCS = trade.cpp
HEADERS = trade.h
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
	valgrind --leak-check=full ./$(TARGETS) -v -m -p -t --ttt AMZN < test.txt > result.txt $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
