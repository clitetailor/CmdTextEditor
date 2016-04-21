#pragma once
#include <iostream>

class Word
{
private:
	std::string String;
public:
	Word() {};
	Word(Word& word);
	
	friend std::istream& operator>> (std::istream& input, Word& word);
	friend std::ostream& operator<< (std::ostream& output, Word& word);
	
	int length();
	
	bool isEndOfFile();
	
	Word break(int position);
};


class Line
{
private:
	Word * Words;
	int Width;
	int Length;
	int Top;
public:
	Line(int width);
	Line(Line line) : ()
	~Line();
	
	friend Line& operator+ (Line& line, Word& word);
	friend std::ostream& operator<< (std::ostream& output, Line& line);
	
	int length();
	
	void flush();
	
	void alignLeft();
	void alignRight();
	void alignCenter();
};