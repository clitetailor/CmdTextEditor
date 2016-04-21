all:
	g++ -c Document.cpp main.cpp
	g++ -o main.exe main.o Document.o