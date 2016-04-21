#include <iostream>

#include "Document.h"

int main()
{
	Word word1, word2;
	
	std::cin >> word1;
	
	word2 = word1.split(3);
	
	std::cout << word2 << word1 << std::endl;
	
	return 0;
}