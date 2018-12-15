#pragma once
// Name: Raymond Rambo
// Seneca Student ID: 122082175
// Seneca email: rrambo@myseneca.ca
// Date of completion: 2018/11/25
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>

class Utilities {
	size_t m_widthField = 1;
	static char m_delimiter;
public:
	// function definitions located in Utilities.cpp
	Utilities() {};
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char&);
	const char getDelimiter() const;
};