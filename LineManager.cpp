// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished December 2nd 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
//Luca Casola helped me figure out the sorting.
#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <memory>
#include <algorithm>

namespace sdds {
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
        std::ifstream fstr(file);

        //Utils Properties
        Utilities utils; //Utils object to enable getting of tokens
        std::string line; //Line to be read from the file


        try {
            if (!fstr.is_open()) {
                throw std::string("File not found");
            }
            sdds::Utilities::setDelimiter('|');

            while (!fstr.eof()) {
                size_t next_pos = 0; //Starting POS
                bool more = true; //More flag to determine if there are more flags in a line

                std::string station;
                std::string nextStation;

                std::getline(fstr, line);

                //Get the first token
                station = utils.extractToken(line, next_pos, more);
                if (more) {
                    //Get the second token
                    nextStation = utils.extractToken(line, next_pos, more);
                }
                for_each(stations.begin(), stations.end(), [&](Workstation *p_station) {
                    if (p_station->getItemName() == station) {
                        for_each(stations.begin(), stations.end(), [&](Workstation *p_station2) {
                            if (p_station2->getItemName() == nextStation) {
                                p_station->setNextStation(p_station2);
                            }
                        });
                        m_activeLine.push_back(p_station);
                    }
                });

            }
            fstr.close();
        } catch (...) {
            throw std::string("File: ") + file + " not found";
        }


        auto last = std::find_if(m_activeLine.begin(), m_activeLine.end(), [](Workstation *p_station) {
            return p_station->getNextStation() == nullptr;
        });

        std::vector<Workstation *> temp;
        temp.push_back(*last);


        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *p_station1) {
            for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *p_station) {
                if (p_station->getNextStation() == temp.back()) {
                    temp.push_back(p_station);
                }
            });
        });

        m_firstStation = temp.back();
        m_cntCustomerOrder = g_pending.size();

    }

    void LineManager::reorderStations() {
        std::vector<Workstation *> sorted;

        sorted.push_back(m_firstStation);


        //Recieved help from fellow student Luca Casola
        for (size_t j = 1; j <= m_activeLine.size(); j++) {
            if (sorted.back()->getNextStation() == m_activeLine[j-1]) {
                sorted.push_back(m_activeLine[j-1]);
                j = 0;
            }
        }

        m_activeLine = sorted;
    }

    bool LineManager::run(std::ostream &os) {
        static int iterationNum = 0;
        iterationNum++;
        os << "Line Manager Iteration: " << iterationNum << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *p_station) {
            p_station->fill(os);
        });

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *p_station) {
            p_station->attemptToMoveOrder();
        });

        if (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()))
            return true;
        else
            return false;
    }

    void LineManager::display(std::ostream &os) const {
        for (size_t i = 0; i < m_activeLine.size(); i++) {
            m_activeLine[i]->display(os);
        }
    }
} // sdds