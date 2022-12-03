// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef MS2_CUSTOMERORDER_H
#define MS2_CUSTOMERORDER_H


#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Station.h"

namespace sdds {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src) {};
    };

    class CustomerOrder {
    private:
        //Instance variables
        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        //Item **m_lstItem; //Changed to vector
        //std::vector<Item *> m_lstItem; //Changed to smrtptr after too many mem leaks
        std::vector<std::unique_ptr<Item>> m_lstItem;

        //Class Variables
        static size_t m_widthField;
    public:
        CustomerOrder() = default;

        explicit CustomerOrder(const std::string &str);

        CustomerOrder(const CustomerOrder &cpy [[maybe_unused]]) {
            throw std::string("Copy Constructor is not allowed");
        };

        CustomerOrder operator=(const CustomerOrder &cpy) = delete;

        CustomerOrder(CustomerOrder &&mv) noexcept;

        CustomerOrder &operator=(CustomerOrder &&mv) noexcept;

        bool isOrderFilled() const;

        bool isItemFilled(const std::string &itemName) const;

        void fillItem(Station &station, std::ostream &os);

        void display(std::ostream &os) const;


    };

} // sdds

#endif //MS2_CUSTOMERORDER_H
