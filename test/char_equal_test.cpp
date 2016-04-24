#include <iostream>


int main()
{
	const char * c = "\n";
	
	if (false != (c == "\n"))
	{
		std::cout << "true";
	}
	else
	{
		std::cout << "false";
	}
	
	return 0;
}