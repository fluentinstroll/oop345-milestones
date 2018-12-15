// Name: Raymond Rambo
// Seneca Student ID: 122082175
// Seneca email: rrambo@myseneca.ca
// Date of completion: 2018/11/25
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

char Utilities::m_delimiter = ' ';

void Utilities::setFieldWidth(size_t width) { m_widthField = width; }// set field width width received width

size_t Utilities::getFieldWidth() const { return m_widthField; }// simply return the current field width

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string extractedToken = str.substr(next_pos);
	size_t pos = extractedToken.find(m_delimiter);
	if (pos != std::string::npos) {
		extractedToken = extractedToken.substr(0, pos);
		next_pos += pos + 1;
		if (extractedToken == "")
			throw "There is not any token between delimiters";
		more = true;
	}
	else {
		more = false;
	}
	if (extractedToken.length() > m_widthField)
		setFieldWidth(extractedToken.length());

	return extractedToken;
	
}

void Utilities::setDelimiter(const char& rec) { m_delimiter = rec; }

const char Utilities::getDelimiter() const { return m_delimiter; }