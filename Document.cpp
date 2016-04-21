#include "Document.h"
#include <iostream>


// class Word
Word::Word() {};

Word::Word(Word& word)
{
	String = word.String;
};

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

Word Word::break(int position)
{
	Word word();
	word.String = std::string(String, 0, position);
	word.String[position - 1] = '-';
	String = std::string(String, position - 1, String.length - position + 1);
	
	return word;
}




// class Line
Line::Line(int width) : Width(width), Length(0), Top(0)
{
	Words = new Word[width];
}

Line::~Line()
{
	delete [] Words;
}


Line& operator+ (Line& line, Word& word)
{
	if (line.Top == 0)
	{
		line.Words [line.Top] = word;
		++line.Top;
		
		line.Length += word.Length();
	}
	else
	{
		line.Words [line.Top] = word;
		++line.Top;
		
		line.Length += (word.Length() + 1);
	}
	
	return line;
}

std::ostream& operator<< (std::ostream& output, Line& line)
{
	int i;
	for (i = 0; i < line.Top; ++i)
	{
		if (line.Top != 0)
		{
			output << " ";
		}
		
		output << line.Words[i];
	}
	
	output << std::endl;
}

void Line::flush()
{
	Top = 0;
	Length = 0;
}