// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished December 2nd 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Workstation.h"

namespace sdds {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &str) : Station(str) {
        m_pNextStation = nullptr;
    }

    void Workstation::fill(std::ostream &os) {
        if (!this->m_orders.empty() && !this->m_orders.front().isOrderFilled()) {
            this->m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (this->m_orders.empty()) { //if there are no orders
            return false;
            //If the order is filled or there is no inventory
        } else if (this->m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) {
            //if there is a next station
            if (this->m_pNextStation != nullptr) {
                *this->m_pNextStation += std::move(this->m_orders.front());
                this->m_orders.pop_front();
                return true;
                //If there isn't an next station
            } else {
                //If the order is completed
                if (m_orders.front().isOrderFilled()) {
                    //add to completed
                    g_completed.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                    //If the order is incomplete
                } else {
                    //add to incomplete
                    g_incomplete.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                }
                return true;
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation *station) {
        this->m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const {
        return this->m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const {
        if (m_pNextStation != nullptr) {
            os << getItemName() << " --> " << m_pNextStation->getItemName() << "\n";

        } else {
            os << getItemName() << " --> End of Line\n";
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) noexcept {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
} // sdds