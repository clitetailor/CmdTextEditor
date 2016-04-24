#include <iostream>
#include <fstream>
#include <exception>

int& test()
{
	static int i = 0;
	
	if (i == 0)
	{
		return i;
	}
	else
	{
		std::cout << i;
		return i;
	}
}

int main()
{
	int& i = test();
	
	i = 3;
	
	test();
	
	return 0;
}