// Name: Raymond Rambo
// Seneca Student ID: 122082175
// Seneca email: rrambo@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <vector>
#include <iostream>
#include <fstream>
#include "Task.h"
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& str, std::vector<Task*>& tasks, std::vector<CustomerOrder>& custOrders) {
	size_t m_pos = 0;
	bool m_more = true;
	Utilities utilities;
	std::string record;
	bool isStartingPoint = true;
	std::ifstream file(str);


	while (!file.eof()) {
		std::getline(file, record);
		std::string task = "";
		task = utilities.extractToken(record, m_pos, m_more);
		std::string next = "";
		/*for every new token, set the next one*/
		if (m_more)
			next = utilities.extractToken(record, m_pos, m_more);

		for (size_t i = 0u; i < tasks.size(); ++i) {
			if (tasks[i]->getName() == task) {
				if (isStartingPoint) {
					m_firstTask = i;
					isStartingPoint = !isStartingPoint;
				}

				if (!next.empty()) {
					for (size_t j = 0; j < tasks.size(); ++j)
						if (tasks[j]->getName() == next) {
							tasks[i]->setNextTask(*tasks[j]);
							break;
						}
					}
				else 
					m_lastTask = i;

				break;
			}
		}

		m_pos = 0;
		m_more = true;
		task.clear();
		next.clear();
	}
	/*input everything into the queue*/
	for (size_t i = 0u; i < custOrders.size(); ++i)
		ToBeFilled.push_back(std::move(custOrders[i]));
	/*erase everything in the custOrders object*/
	custOrders.erase(custOrders.begin(), custOrders.end());
	/* insert the tasks*/
	AssemblyLine = tasks;
}

bool LineManager::run(std::ostream& os) {
	CustomerOrder temp;
	bool filled = true;

	if (!ToBeFilled.empty()) {
		*AssemblyLine[m_firstTask] += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (size_t i = 0u; i < AssemblyLine.size(); ++i) {
		AssemblyLine[i]->runProcess(os);
	}

	if (AssemblyLine[m_lastTask]->getCompleted(temp))
		Completed.push_back(std::move(temp));

	for (size_t i = 0; i < AssemblyLine.size(); ++i) {
		if (AssemblyLine[i]->moveTask()) {
			filled = false;

		}
	}

	return filled;
}
void LineManager::displayCompleted(std::ostream& os) const {
	if (!Completed.empty())
		for (size_t i = 0; i < Completed.size(); ++i)
			Completed[i].display(os);
}

void LineManager::validateTasks() const {
	if (!AssemblyLine.empty())
		for (size_t i = 0; i < AssemblyLine.size(); ++i)
			AssemblyLine[i]->validate(std::cout);
}