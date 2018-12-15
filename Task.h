
#pragma once
#include <deque>
#include <ostream>
#include <string>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;

public:
	Task(const std::string&);
	// copy / move constructors
	Task(Task&) = delete;
	Task(Task&&) = delete;
	// copy / move operators
	Task& operator=(Task&) = delete;
	Task& operator=(Task&&) = delete;

	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};
