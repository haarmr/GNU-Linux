CXX = g++
CFLAGS = -g -Wall
files = "ComplexNumber ComplexNumber.o Homework1.o"

all: Homework1

Homework1: Homework1.o ComplexNumber.o
	$(CXX) $(CFLAGS) Homework1.o ComplexNumber.o -o ComplexNumber

Homework1.o: Homework1.cpp
	$(CXX) $(CFLAGS) -c Homework1.cpp -o Homework1.o

ComplexNumber.o: ComplexNumber.cpp
	$(CXX) $(CFLAGS) -c ComplexNumber.cpp -o ComplexNumber.o

clean:
	rm $(files)