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
	
	/* Line width */
	bool success = false;
	do
	{
		std::cout << "Line width (20-200):";
		
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
				std::cout << "Line width too short !" << std::endl << std::endl;
				throw -1;
			}
			
			if (line_width > 200)
			{
				std::cout << "Line width too long !" << std::endl << std::endl;
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
	
	/* Open and read document from file */
	success = false;
	do
	{
		std::cout << "File name:";
		if (std::cin.get() != '\n')
		{
			std::cin.unget();
		}
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
		
		input_file.close();
		
		success = true;
	} while (false == success);
	
	/* Read successfully */
	
	/* Write document to console */
	std::cout << document;
	
	/* Align document */
	
	/* Ask whether the user want to save file */
	std::string accept;
	success = false;
	do
	{
		std::cout << "Save file? (yes/no):";
		if (std::cin.get() != '\n')
		{
			std::cin.unget();
		}
		std::getline(std::cin, accept);
		
		if (accept != "yes" && accept != "no")
		{
			std::cout << "Invalid option \"" << accept << "\" !" << std::endl;
			std::cout << std::endl;
			continue;
		}
		
		success = true;
	} while (false == success);
	
	std::cout << std::endl;
	
	/* Save file */
	if (accept == "yes")
	{
		std::ofstream output_file;
		
		success = false;
		do
		{
			/* Get file name */
			std::cout << "File name:";
		
			std::string output_file_name;
			if (std::cin.get() != '\n')
			{
				std::cin.unget();
			}
			std::getline(std::cin, output_file_name);
			
			/* Append or rewrite */
			std::string app_or_out;
			do
			{
				std::cout << "Append or rewrite? (app/out):";
				
				if (std::cin.get() != '\n')
				{
					std::cin.unget();
				}
				std::getline(std::cin, app_or_out);
				
				if (app_or_out != "app" && app_or_out != "out")
				{
					std::cout << "Invalid option \"" << app_or_out << "\" !" << std::endl;
				}
			} while (app_or_out != "app" && app_or_out != "out");
			
			if (app_or_out == "out")
			{
				output_file.open(output_file_name.c_str(), std::ios::out);
			}
			else
			{
				output_file.open(output_file_name.c_str(), std::ios::out | std::ios::app | std::ios::binary);
			}
			
			/* Can not open file */
			if (false == output_file.is_open())
			{
				std::cout << "Can not open file \"" << output_file_name << "\" !" << std::endl;
				std::cout << std::endl;
				/* Ask user to open another file */
				do
				{
					std::cout << "Do you want to continue? (yes/no):";
					if (std::cin.get() != '\n')
					{
						std::cin.unget();
					}
					std::getline(std::cin, accept);
					
					if (accept != "yes" && accept != "no")
					{
						std::cout << "Invalid option \"" << accept << "\" !" << std::endl;
					}
				} while (accept != "yes" && accept != "no");
				
				std::cout << std::endl;
				
				if (accept == "no")
				{
					output_file.close();
					break;
				}
				
				continue;
			} /* Can not open file */
			
			/* File is successfully opened */
			
			/* Write document to file */
			try
			{
				output_file << document;
			}
			catch (...)
			{
				std::cout << "File corrupt !" << std::endl;
			}
			
			output_file.close();
			success = true;
		} while (false == success);
	}
	
	std::cout << std::endl << "Done!" << std::endl;
	
	return 0;
}