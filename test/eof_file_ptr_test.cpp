#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


int main()
{
	char c;
	
	int count = 0;
	
	std::ifstream input;
	
	input.open("test.txt", std::ios::in | std::ios::ate | std::ios::binary );
	
	std::size_t size = input.tellg();
	
	std::cout << size;
	
	input.seekg(std::ios::beg);
	
	while (input.tellg() != size)
	{
		input.get();
		count ++;
	}
	
	std::cout << std::endl << count;
	
	return 0;
}