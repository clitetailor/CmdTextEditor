#pragma once
#include <iostream>

class Line;

class Word
{
private:
	std::string word_string;
public:
	Word() {};
	Word(Word& word);
	
	friend std::istream& operator>> (std::istream& input, Word& word);
	friend std::ostream& operator<< (std::ostream& output, Word& word);
	
	int length();
	
	bool isEndOfFile();
	
	Word split(int position);
	
	friend Line& operator+ (Line& line, Word& word);
};


class Line
{
private:
	char * 	line_string;
	int 	line_width;
	int 	line_length;
public:
	Line();
	Line(int width);
	Line(const Line& line);
	~Line();
	
	friend Line& 			operator+ (Line& line, Word& word);
	friend std::ostream& 	operator<< (std::ostream& output, Line& line);
	
	int length();
	int width();
	
	void flush();
	
	void alignLeft();
	void alignRight();
	void alignCenter();
};