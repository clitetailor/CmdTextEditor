#include "Document.h"
#include <iostream>
#include <string>

// class Word
Word::Word(Word& word)
{
	String = word.String;
}

std::istream& operator>> (std::istream& input, Word& word)
{
	input >> word.String;
}

std::ostream& operator<< (std::ostream& output, Word& word)
{
	output << word.String;
}

int Word::length()
{
	return String.length();
}

bool Word::isEndOfFile()
{
	int i;
	for (i = 0; i < String.length(); ++i)
	{
		if (String[i] == 4)
		{
			return true;
		}
	}
	
	return false;
}

Word Word::split(int position)
{
	Word word;
	word.String = std::string(String, 0, position);
	word.String[position - 1] = '-';
	String = std::string(String, position - 1, String.length() - position + 1);
	
	return word;
}




// class Line
Line::Line(int width) : Length(0), Width(width)
{
	String = new char[width + 1];
};

Line::Line(const Line& line)
{
	Width = line.Width;
	Length = line.Length;
	
	String = new char[Width + 1];
	
	int i;
	for (i = 0; i < Width + 1; ++i)
	{
		String[i] = line.String[i];
	}
}

Line::~Line()
{
	delete [] String;
}

Line& operator+ (Line& line, Word& word)
{
	int i;
	for (i = 0; i < word.String.length(); ++i)
	{
		line.String[line.Length + i] = word.String[i];
	}
	
	if (line.Length + i == line.Width)
	{
		line.String[line.Length + i] = '\0';
		line.Length += word.length();
	}
	else
	{
		line.String[line.Length + i] = ' ';
		line.String[line.Length + i] = '\0';
		
		line.Length += word.length() + 1;
	}
	
	return line;
}

std::ostream& operator<< (std::ostream& output, Line& line)
{
	int i;
	for (i = 0; i < line.Length; ++i)
	{
		output << line.String[i];
	}
	
	output << std::endl;
}

int Line::length()
{
	return Length;
}

int Line::width()
{
	return Width;
}

void Line::flush()
{
	Length = 0;
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