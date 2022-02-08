CXX = g++
CFLAGS = -g -Wall
files = "shell ShellService.o Homework3.o"

all: Homework1

Homework1: Homework3.o ShellService.o
	$(CXX) $(CFLAGS) Homework3.o ShellService.o -o shell

Homework1.o: Homework3.cpp
	$(CXX) $(CFLAGS) -c Homework3.cpp -o Homework3.o

ShellService.o: ShellService.cpp
	$(CXX) $(CFLAGS) -c ShellService.cpp -o ShellService.o

clean:
	rm $(files)