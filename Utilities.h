// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef MS1_UTILITIES_H
#define MS1_UTILITIES_H

#include <iostream>

namespace sdds {
    //Instance Variables

    class Utilities {
    private:
        static char m_delimiter;
        std::size_t m_widthField = 0;
    public:
        void setFieldWidth(std::size_t newWidth);

        std::size_t getFieldWidth() const; // NOLINT(modernize-use-nodiscard) [CLION WARNING IGNORE]

        std::string extractToken(const std::string &str, std::size_t &next_pos, bool &more);

        static void setDelimiter(const char delimiter);

        static const char getDelimiter();
    };
}
#endif //MS1_UTILITIES_H
