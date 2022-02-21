CXX = g++
CFLAGS = -g -Wall -pthread -lpthread
files = "scheduler ParallelScheduler.o Homework4.o"

all: scheduler

scheduler: Homework4.o ParallelScheduler.o
	$(CXX) $(CFLAGS) Homework4.o ParallelScheduler.o -o scheduler

Homework4.o: Homework4.cpp ParallelScheduler.h
	$(CXX) $(CFLAGS) -c Homework4.cpp -o Homework4.o

ParallelScheduler.o: ParallelScheduler.cpp ParallelScheduler.h
	$(CXX) $(CFLAGS) -c ParallelScheduler.cpp -o ParallelScheduler.o

clean:
	rm $(files)