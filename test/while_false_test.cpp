#include <iostream>
#include <fstream>

int main ()
{
	int i = 0;
	do
	{
		std::cin >> i;
		if (i != 1)
		{
			continue;
		}
		
	} while (false);
	
	std::cout << std::endl << "Done!" << std::endl;
	
	return 0;
}