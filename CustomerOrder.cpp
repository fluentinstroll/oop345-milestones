
#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"
#include "Item.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;
// blank constructor sets to safe empty state
CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0u;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string str) {
	size_t m_count = 0u;
	size_t m_pos = 0u;
	bool m_more = true;
	size_t i_cnt = 0u;
	size_t i_pos = 0u;
	Utilities utilities;
	/*move each token into name, product*/
	while (m_more) {
		if (m_count == 0)
			m_name = utilities.extractToken(str, m_pos, m_more);
		else if (m_count == 1)
			m_product = utilities.extractToken(str, m_pos, m_more);
		else if (m_count == 2) {
			i_pos = m_pos;
			while (m_more) {
				utilities.extractToken(str, i_pos, m_more);
				i_cnt++;
			}
			m_cntItem = i_cnt;
			i_cnt = 0u;
			m_more = true;
			m_lstItem = new ItemInfo*[m_cntItem];
		}
		else {
			m_lstItem[i_cnt] = new ItemInfo(utilities.extractToken(str, m_pos, m_more));
			i_cnt++;
		}
		m_count++;
	}

	if (utilities.getFieldWidth() > m_widthField) {
		m_widthField = utilities.getFieldWidth();
	}

}

// move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& rec) noexcept : CustomerOrder() { *this = std::move(rec); }

/*move operator, updated for dec 2nd(milestone 3)*/
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rec) {
	if (&rec != this) {
		this->m_name = rec.m_name;
		this->m_product = rec.m_product;

		/*clear current object*/
		if (m_lstItem)
			for (unsigned int i = 0; i < m_cntItem; i++) { delete this->m_lstItem[i]; }
		delete[] this->m_lstItem;
		/*move the recieved object into the current object*/
		this->m_cntItem = rec.m_cntItem;
		this->m_lstItem = rec.m_lstItem;

		rec.m_lstItem = nullptr;
	}

	return *this;
}
/*updated destructor for dec 2nd(milestone 3)*/
CustomerOrder::~CustomerOrder() {
	if (m_lstItem) {
		for (size_t i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
	}

	delete[] m_lstItem;
	m_lstItem = nullptr;
}
/*updated for dec 2nd(milestone 3)*/
bool CustomerOrder::getItemFillState(std::string rec) const {
	bool filled = true; // default to true
	
	for (unsigned int i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_itemName == rec) {
			if (!this->m_lstItem[i]->m_fillState) {
				filled = false;
				break;
			}
		}
	}

	return filled; // return whether or not the item is filled
}

bool CustomerOrder::getOrderFillState() const {
	for (size_t i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_fillState == false)
			return false;
	}
	return true;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (unsigned int i = 0; i < m_cntItem; ++i) {
		// check fillState too, there could be more than one of the same item
		if (m_lstItem[i]->m_itemName == item.getName() && !m_lstItem[i]->m_fillState) {
			if (item.getQuantity() > 0) {
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				item.updateQuantity();
				m_lstItem[i]->m_fillState = true;
				os << "Filled ";
			}
			else {
				os << "Unable to fill ";
			}

			os << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			return;
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (unsigned int i = 0; i < m_cntItem; i++) {
	os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
	<< std::setfill(' ') << "] " << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName
		<< " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING") << std::endl;
	}
}
