CXX = g++
CFLAGS = -pthread  -lpthread
files = "matrix ParallelMatrix.o Homework4.o"

all: matrix

matrix: Homework4.o ParallelMatrix.o
	$(CXX) $(CFLAGS) Homework4.o ParallelMatrix.o -o matrix

Homework4.o: Homework4.cpp
	$(CXX) $(CFLAGS) -c Homework4.cpp -o Homework4.o

ParallelMatrix.o: ParallelMatrix.cpp
	$(CXX) $(CFLAGS) -c ParallelMatrix.cpp -o ParallelMatrix.o

clean:
	rm $(files)