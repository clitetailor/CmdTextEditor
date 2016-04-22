all:
	g++ -o main.exe main.cpp Document.cpp
	
test:
	g++ -o main.exe test.cpp Document.cpp