#include "Document.h"
#include <iostream>
#include <string>

// class Word
Word::Word(Word& word)
{
	word_string = word.word_string;
}

std::istream& operator>> (std::istream& input, Word& word)
{
	input >> word.word_string;
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
	int i;
	for (i = 0; i < word_string.length(); ++i)
	{
		if (word_string[i] == 4)
		{
			return true;
		}
	}
	
	return false;
}

Word Word::split(int position)
{
	Word word;
	word.word_string = std::string(word_string, 0, position);
	word.word_string[position - 1] = '-';
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
	for (i = 0; i < word.word_string.length(); ++i)
	{
		line.line_string[line.line_length + i] = word.word_string[i];
	}
	
	if (line.line_length + i == line.line_width)
	{
		line.line_string [line.line_length + i] = '\0';
		line.line_length += word.length();
	}
	else
	{
		line.line_string [line.line_length + i] = ' ';
		line.line_string[line.line_length + i] = '\0';
		
		line.line_length += word.length() + 1;
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