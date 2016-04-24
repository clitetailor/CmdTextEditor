#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>
/*/
 *
 *
 *
 *
 *
/*/
#include "Document.h"
#include "LinkList.h"

using namespace hedge;

int main()
{
	std::cout << std::endl;
	
	std::string file_name;
	int			line_width;
	
	bool success = false;
	do
	{
		std::cout << "Line width:";
		
		std::string line_width_string;
		std::getline(std::cin, line_width_string);
		
		try
		{
			int i;
			for (i = 0; i < line_width_string.length(); ++i)
			{
				if ((line_width_string[i] < 48 || line_width_string[i] > 57) && line_width_string[i] != ' ')
				{
					std::cout << "Invalid \"" << line_width_string << "\" !" << std::endl << std::endl;
					throw -1;
				}
			}
			
			std::istringstream(line_width_string) >> line_width;
			
			if (line_width < 20)
			{
				throw -1;
			}
		}
		catch (int)
		{
			continue;
		}
		
		success = true;
	} while (false == success);
	
	
	std::ifstream 	input_file;
	Document 		document(line_width);
	
	success = false;
	do
	{
		std::cout << "File name:";
		std::getline(std::cin, file_name);
		
		input_file.open(file_name.c_str());
		
		if (false == input_file.is_open())
		{
			std::cout << "Can not open file \"" << file_name << "\" !" << std::endl;
			std::cout << std::endl;
			continue;
		}
		
		try
		{
			input_file >> document;
		}
		catch (...)
		{
			std::cout << "Can not read from file \"" << file_name << "\" !" << std::endl;
			std::cout << std::endl;
			continue;
		}
		
		success = true;
	} while (false == success);
	
	std::cout << document;
	std::cout << "Save file? (yes/no):";
	
	std::cout << std::endl << "Done!" << std::endl;
	
	return 0;
}