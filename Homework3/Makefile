CXX = g++
CFLAGS = -g -Wall
files = "shell ShellService.o Homework3.o"

all: Homework3

Homework3: Homework3.o ShellService.o
	$(CXX) $(CFLAGS) Homework3.o ShellService.o -o shell

Homework3.o: Homework3.cpp ShellService.h
	$(CXX) $(CFLAGS) -c Homework3.cpp -o Homework3.o

ShellService.o: ShellService.cpp ShellService.h
	$(CXX) $(CFLAGS) -c ShellService.cpp -o ShellService.o

clean:
	rm $(files)