#include <iostream>
#include <string>

#include "Document.h"

int main()
{
	Word word1;
	Word word2;
	Word word3;
	Line line(30);
	
	std::cin >> word1 >> word2 >> word3;
	
	line = line + word1 + word2 + word3;
	
	std::cout << line << std::endl;
	
	Line newLine(line);
	
	std::cout << line << std::endl;
	
	return 0;
}