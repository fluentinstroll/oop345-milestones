#pragma once
#include <string>
// Name: Raymond Rambo
// Seneca Student ID: 122082175
// Seneca email: rrambo@myseneca.ca
// Date of completion: 2018/11/25
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include <iomanip>
#include "Item.h"
#include "Utilities.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name; //customer name
	std::string m_product; //product name
	unsigned int m_cntItem; //number of items
	ItemInfo** m_lstItem = nullptr;//array of items
	static size_t m_widthField; // widthfield width

public:
	CustomerOrder();
	CustomerOrder(std::string);

	/*DOES NOT ALLOW COPY OPERATIONS*/
	CustomerOrder(const CustomerOrder&) { throw "*** COPIES ARE NOT ALLOWED ***"; }
	CustomerOrder& operator = (CustomerOrder&) = delete;

	CustomerOrder(CustomerOrder&&) noexcept; // move constructor
	CustomerOrder& operator = (CustomerOrder&&); // move operator

	~CustomerOrder();
	/*defined in CustomerOrder.cpp*/
	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream& os);
	void display(std::ostream& os) const;
};
