
#include "Task.h"

Task::Task(const std::string& str) : Item(str) {m_pNextTask = nullptr;}
/*if the m_orders object isn't empty, make sure the fill state is ok, then pop in the input*/
void Task::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		if (!m_orders.back().getOrderFillState()) {
			while (!m_orders.back().getItemFillState(getName())) {
				m_orders.back().fillItem(*this, os);
			}
		}
	}
}
/*moves the next task into the back of m_orders*/
bool Task::moveTask() {
	if (!m_orders.empty()) {
		if (m_pNextTask) {
			if (m_orders.back().getItemFillState(getName())) {
				*m_pNextTask += std::move(m_orders.back());
				m_orders.pop_back();
			}
		}
		return true;
	}
	else
		return false;
}

void Task::setNextTask(Task& nextTask) { m_pNextTask = &nextTask; }

bool Task::getCompleted(CustomerOrder& custOrder) {
	if (!m_orders.empty() && m_orders.front().getOrderFillState()) {
		custOrder = std::move(m_orders.front());
		m_orders.pop_front();
		return true;
	}
	else
		return false;
}

void Task::validate(std::ostream& os) {
	os << getName() << " --> ";
	os << (m_pNextTask ? m_pNextTask->getName() : "END OF LINE");
	os << std::endl;
}

Task& Task::operator+=(CustomerOrder&& custOrder) {
	m_orders.push_front(std::move(custOrder));

	return *this;
}
