// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef MS1_STATION_H
#define MS1_STATION_H

#include <iostream>
#include <string>

namespace sdds {
    class Station {
    private:
        int m_id;
        std::string m_name;
        std::string m_description;
        size_t m_serial;
        size_t m_amountInStock;

        static size_t m_widthField;
        static size_t id_generator;
    public:
        explicit Station(const std::string &str);

        const std::string &getItemName() const;

        size_t getNextSerialNumber();

        size_t getQuantity() const;

        void updateQuantity();

        void display(std::ostream &os, bool full) const;
    };

} // sdds

#endif //MS1_STATION_H
