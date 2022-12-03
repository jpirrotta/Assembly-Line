//
// Created by jesse on 2022-12-02.
//

#ifndef MS3_LINEMANAGER_H
#define MS3_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace sdds {

    class LineManager {
    private:
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation *m_firstStation;
    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);

        void reorderStations();

        bool run(std::ostream &os);

        void display(std::ostream &os) const;
    };

} // sdds

#endif //MS3_LINEMANAGER_H
