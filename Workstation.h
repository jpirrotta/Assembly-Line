// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished December 2nd 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef MS3_WORKSTATION_H
#define MS3_WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
    private:
        std::deque<CustomerOrder> m_orders;
        Workstation *m_pNextStation;
    public:
        explicit Workstation(const std::string &str);

        void fill(std::ostream &os);

        bool attemptToMoveOrder();

        void setNextStation(Workstation *station);

        Workstation *getNextStation() const;

        void display(std::ostream &os) const;

        Workstation &operator+=(CustomerOrder &&newOrder) noexcept;
    };

} // sdds

#endif //MS3_WORKSTATION_H
