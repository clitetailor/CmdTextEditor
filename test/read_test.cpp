#include <iostream>
#include <fstream>

int main ()
{
	std::ifstream what("test.txt", std::ios::ate);
	
	std::size_t size= what.tellg();
	
	what.seekg(std::ios::beg);
	
	char c;
	do
	{
		std::cout << what.get() << std::endl;
		std::cout << "Size: " << what.tellg() << std::endl;
	} while (what.tellg() != -1);
	
	std::cout << "Done!" << std::endl;
	
	return 0;
}