// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Station.h"
#include "Utilities.h"
#include <iomanip>

using namespace std;

namespace sdds {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 1;

    Station::Station(const std::string &str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(str, next_pos, more);
        if (m_name.length() > m_widthField) {
            m_widthField = m_name.length();
        }
        if (more) {
            m_serial = std::stoi(util.extractToken(str, next_pos, more));
            if (more) {
                m_amountInStock = std::stoi(util.extractToken(str, next_pos, more));
                if (more) {
                    m_description = util.extractToken(str, next_pos, more);
                }
            }

        }
        m_id = int(id_generator++);
    }

    const std::string &Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        m_serial++;
        return m_serial - 1;
    }

    size_t Station::getQuantity() const {
        return m_amountInStock;
    }

    void Station::updateQuantity() {
        if (m_amountInStock > 0)
            m_amountInStock--;
    }

    void Station::display(std::ostream &os, bool full) const {
        os << setw(3) << setfill('0') << right << m_id << " | ";
        os << setw(int(m_widthField)) << setfill(' ') << left << m_name << "  | ";
        os << setw(6) << setfill('0') << right << m_serial << " | ";
        if (full) {
            os << setw(4) << setfill(' ') << m_amountInStock << " | " << m_description;
        }
        os << endl;
    }
} // sdds