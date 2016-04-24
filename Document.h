#pragma once
#include <iostream>
/*/
 *
 *
 *
 *
/*/
#include "LinkList.h"

using namespace hedge;

class Line;
class Document;

class Word
{
private:
	std::string word_string;
	bool word_eof;
	bool word_eol;
public:
	Word();
	Word(Word& word);
	
	friend std::istream& operator>> (std::istream& input, Word& word);
	friend std::ifstream& operator>> (std::ifstream& input, Word& word);
	friend std::ostream& operator<< (std::ostream& output, Word& word);
	
	int length();
	
	bool isEndOfFile();
	bool isEndOfLine();
	
	Word split(int position);
	
	friend Line& operator+ (Line& line, Word& word);
	
	friend class Document;
	friend class Line;
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

class Document
{
private:
	LinkList<Line> document_lines;
	int document_line_width;
public:
	Document();
	Document(int line_width);
	
	Line& newLine();
	
	friend std::istream& operator>> (std::istream& input, Document& document);
	friend std::ifstream& operator>> (std::ifstream& input, Document& document);
	
	void alignLeft();
	void alignCenter();
	void alignRight();
	
	friend std::ostream& operator<< (std::ostream& output, Document& document);
	friend std::ofstream& operator<< (std::ofstream& output, Document& document);
};