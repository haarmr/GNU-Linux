CXX = g++
CFLAGS = -g -Wall
files = "cpService CopyService.o Homework2.o"

all: Homework2

Homework2: Homework2.o CopyService.o
	$(CXX) $(CFLAGS) Homework2.o CopyService.o -o cpService

Homework2.o: Homework2.cpp
	$(CXX) $(CFLAGS) -c Homework2.cpp -o Homework2.o

CopyService.o: CopyService.cpp
	$(CXX) $(CFLAGS) -c CopyService.cpp -o CopyService.o

clean:
	rm $(files)