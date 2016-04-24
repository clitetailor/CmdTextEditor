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
	
	std::cout << "File name:";
	std::getline(std::cin, file_name);
	
	std::cout << "Line width:";
	std::cin >> line_width;
	
	Document document(line_width);
	
	try
	{
		document.readDocumentFromFile(file_name);
		document.printDocument();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Error orcurred!" << std::endl;
	}
	
	return 0;
}