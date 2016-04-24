#include "Document.h"
#include <iostream>
#include <fstream>
#include <string>

// class Word
Word::Word() : word_eof(false), word_eol(false)
{
	
}

Word::Word(Word& word)
{
	word_string = word.word_string;
	word_eof = word.word_eof;
}

std::istream& operator>> (std::istream& input, Word& word)
{
	word.word_string = std::string("");
	word.word_eof = false;
	word.word_eol = false;
	
	char c;
	
	do
	{
		c = input.get();
	} while (c == ' ' || c == '\t');
	
	input.unget();
	
	c = input.get();
	
	if (c == '\n')
	{
		word.word_eol = true;
		return input;
	}
	else if (c == 4)
	{
		word.word_eof = true;
		return input;
	}
	else
	{
		
		input.unget();
		
		do
		{
			c = input.get();
			
			if (c == ' ')
			{
				input.unget();
				return input;
			}
			else if (c == '\t')
			{
				input.unget();
				return input;
			}
			else if (c == '\n')
			{
				input.unget();
				return input;
			}
			else if (c == 4)
			{
				input.unget();
				return input;
			}
			else
			{
				word.word_string += c;
			}
		} while (1);
	}
	
	return input;
}


void Word::readFromFileStream(std::ifstream& input, std::size_t end_of_file)
{
	word_string = std::string("");
	word_eof = false;
	word_eol = false;
	
	char c;
	
	do
	{
		c = input.get();
	} while (c == ' ' || c == '\t');
	
	input.unget();
	
	c = input.get();
	
	if (c == '\n')
	{
		word_eol = true;
		return;
	}
	else if (input.tellg() == -1)
	{
		word_eof = true;
		return;
	}
	else
	{
		input.unget();
		
		do
		{
			c = input.get();
			
			if (c == ' ')
			{
				input.unget();
				return;
			}
			else if (c == '\t')
			{
				input.unget();
				return;
			}
			else if (c == '\n')
			{
				input.unget();
				return;
			}
			else if (input.tellg() == -1)
			{
				input.unget();
				return;
			}
			else
			{
				word_string += c;
			}
		} while (1);
	}
}

std::ostream& operator<< (std::ostream& output, Word& word)
{
	output << word.word_string;
}

int Word::length()
{
	return word_string.length();
}

bool Word::isEndOfFile()
{
	return word_eof;
}

bool Word::isEndOfLine()
{
	return word_eol;
}

Word Word::split(int position)
{
	Word word;
	word.word_string = std::string(word_string, 0, position);
	word.word_string[position - 1] = '-';
	std::cout << std::endl;
	if (position == 0)
	{
		word_string = std::string(word_string, 0, word_string.length() - position + 1);
		return word;
	}
	
	word_string = std::string(word_string, position - 1, word_string.length() - position + 1);
	
	return word;
}




// class Line
Line::Line() : line_length(0), line_width(0)
{
	line_string = NULL;
}

Line::Line(int width) : line_length(0), line_width(width)
{
	line_string = new char[width + 1];
};

Line::Line(const Line& line)
{
	line_width = line.line_width;
	line_length = line.line_length;
	
	line_string = new char[line_width + 1];
	
	int i;
	for (i = 0; i < line_width + 1; ++i)
	{
		line_string[i] = line.line_string[i];
	}
}

Line::~Line()
{
	delete [] line_string;
}

Line& operator+ (Line& line, Word& word)
{
	int i;
	word.word_string.copy(& line.line_string[line.line_length], word.length(), 0);
	line.line_length += word.length();
	
	if (line.line_length < line.line_width)
	{
		line.line_string[line.line_length] = ' ';
		line.line_length ++;
	}
	
	return line;
}

std::ostream& operator<< (std::ostream& output, Line& line)
{
	int i;
	for (i = 0; i < line.line_length; ++i)
	{
		output << line.line_string[i];
	}
	
	output << std::endl;
}

int Line::length()
{
	return line_length;
}

int Line::width()
{
	return line_width;
}

void Line::flush()
{
	line_length = 0;
	line_string[0] = '\0';
}

void Line::alignLeft()
{
	
}

void Line::alignCenter()
{
	
}

void Line::alignRight()
{
	
}


// class Document
Document::Document()
{
	
}

Document::Document(int line_width) : document_line_width(line_width)
{
	
}

Line& Document::newLine()
{
	document_lines.append(Line(document_line_width));
	
	return document_lines.tail()->content();
}

void Document::readDocumentFromFile(std::string file_name)
{
	std::ifstream input;
	input.open(file_name.c_str(), std::ifstream::ate);
	
	if (false == input.is_open())
	{
		throw -1;
	}
	
	std::size_t file_size = input.tellg();
	input.seekg(std::ifstream::beg);
	
	Word word;
	
	Line * line_pointer = &newLine();
	
	do
	{
		word.readFromFileStream(input ,file_size);
		
		if (false != word.isEndOfLine())
		{
			line_pointer = &newLine();
		}
		else if (false != word.isEndOfFile())
		{
			// Do nothing!
		}
		else 
		{
			if (line_pointer->length() + word.length() < document_line_width)
			{
				(* line_pointer) = (* line_pointer) + word;
			}
			else
			{
				if (word.length() < line_pointer->length())
				{
					line_pointer = &newLine();
					
					(* line_pointer) = (* line_pointer) + word;
				}
				else
				{
					Word frac;
					
					do
					{
						frac = word.split(document_line_width - line_pointer->length());
						
						(* line_pointer) = (* line_pointer) + frac;
						
						line_pointer = &newLine();
					} while (word.length() > document_line_width);
					
					(* line_pointer) = (* line_pointer) + word;
				}
			}
		}
	} while (false == word.isEndOfFile());
}

void Document::readDocumentFromKeyboard()
{
	
}

void Document::printDocument()
{
	std::cout << std::endl;
	
	int i;
	for (i = 0; i < document_line_width; ++i)
	{
		std::cout << "-";
	}
	
	std::cout << std::endl;
	
	LinkList<Line>::Node * temp;
	for (temp = document_lines.head(); temp->isNotTail(); temp = temp->next())
	{
		Line& line = temp->content();
		std::cout << line;
	}
	
	std::cout << std::endl;
	for (i = 0; i < document_line_width; ++i)
	{
		std::cout << "-";
	}
	
	std::cout << std::endl;
}

void Document::saveDocument(std::string file_name)
{
	
}