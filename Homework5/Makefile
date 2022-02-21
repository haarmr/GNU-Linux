CXX = g++
CFLAGS = -pthread  -lpthread
files = "pipe_ipc IPCService.o Homework5.o"

all: pipe_ipc

pipe_ipc: Homework5.o IPCService.o
	$(CXX) $(CFLAGS) Homework5.o IPCService.o -o pipe_ipc

Homework5.o: Homework5.cpp IPCService.h
	$(CXX) $(CFLAGS) -c Homework5.cpp -o Homework5.o

IPCService.o: IPCService.cpp IPCService.h
	$(CXX) $(CFLAGS) -c IPCService.cpp -o IPCService.o

clean:
	rm $(files)