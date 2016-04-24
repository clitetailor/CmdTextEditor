#include <iostream>
#include <fstream>
#include <string>
#include <exception>
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
	std::string file_name;
	int			line_width;
	
	std::cout << "Line width:";
	std::cin >> line_width;
	
	std::cin.ignore();
	
	std::cout << "File name:";
	std::getline(std::cin, file_name);
	
	Document document(line_width);
	
	std::ifstream input_file(file_name.c_str());
	
	try
	{
		input_file >> document;
		std::cout << document;
	}
	catch (int)
	{
		std::cout << "Can not open file \"" << file_name << "\" !" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Can not read from file \"" << file_name << "\" !" << std::endl;
	}
	
	return 0;
}