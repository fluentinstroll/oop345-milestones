
#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "Task.h"
#include "CustomerOrder.h"


class LineManager {
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	size_t m_firstTask;
	size_t m_lastTask;

public:
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};
