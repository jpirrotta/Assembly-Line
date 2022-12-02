// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>


namespace sdds {

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string &str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        Item *temp[this->m_cntItem];
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        m_cntItem = 0;
        while (more) {
            //Copy the current item into the temp array
            for (int i = 0; i < m_cntItem; i++) {
                temp[i] = m_lstItem[i];
            }

            //Create a new item with one more element
            m_lstItem = new Item *[m_cntItem + 1];

            //Copy the temp array back into our array
            for (int i = 0; i < m_cntItem; i++) {
                m_lstItem[i] = temp[i];
            }

            //Add the newest item to the last array
            m_lstItem[m_cntItem + 1] = new Item(util.extractToken(str, next_pos, more));

            //Increment the counter
            m_cntItem++;
        }

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&mv) noexcept {
        *this = std::move(mv);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&mv) noexcept {
        if (this != &mv) {
            m_name = std::move(mv.m_name);
            m_product = std::move(mv.m_product);
            m_cntItem = std::move(mv.m_cntItem);
            m_lstItem = std::move(mv.m_lstItem);
            mv.m_name = "";
            mv.m_product = "";
            mv.m_cntItem = 0;
            mv.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        bool filled = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                filled = false;
            } else
                filled = true;
        }
        return filled;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const {
        bool filled = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                filled = m_lstItem[i]->m_isFilled;
            }
        }
        return filled;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os) {
        bool filled = false;
        for (size_t i = 0; i < m_cntItem && !filled; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]"
                       << std::endl;
                    filled = true;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName
                       << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField);
            os << std::setfill(' ') << m_lstItem[i]->m_itemName << "   - ";
            if (m_lstItem[i]->m_isFilled) {
                os << "FILLED" << std::endl;
            } else {
                os << "TO BE FILLED" << std::endl;
            }
            os << std::endl;
        }
    }


} // sdds