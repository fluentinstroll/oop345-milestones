#pragma once
// Name: Raymond Rambo
// Seneca Student ID: 122082175
// Seneca email: rrambo@myseneca.ca
// Date of completion: 2018/11/25
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>

class Item {
	std::string m_name;
	std::string m_description;
	unsigned int m_serialNumber;
	unsigned int m_quantity;
	unsigned int static m_widthField;
public:
	Item(const std::string&);
	const std::string& getName() const;
	const unsigned int getSerialNumber();
	const unsigned int getQuantity();
	void updateQuantity();
	void display(std::ostream&, bool) const;
};