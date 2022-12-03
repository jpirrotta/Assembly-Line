// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished November 10th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Utilities.h"
#include <string>

using namespace std;

namespace sdds {
    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(std::size_t newWidth) {
        m_widthField = newWidth;
    }

    std::size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    string Utilities::extractToken(const string &str, size_t &next_pos, bool &more) {
        string token;

        //If the first char is the delim
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw "No token found"; // NOLINT(hicpp-exception-baseclass)
        }

        //Extract the Token
        if (next_pos >= 0) {
            token = str.substr(next_pos, str.find(m_delimiter, next_pos) - next_pos);
        } else {
            token = str;
        }

        //Erase any leading and trailing spaces from the token
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        if (token.length() > 0) {
            if (token.length() > m_widthField) {
                m_widthField = token.length();
            }
            if (str.find(m_delimiter, next_pos) != string::npos) {
                next_pos = str.find(m_delimiter, next_pos) + 1;
            } else {
                more = false;
                next_pos = -1;
            }
        } else {
            more = false;
            return "No tokens remaining";
        }
        return token;
    }

    void Utilities::setDelimiter(char delimiter) {
        m_delimiter = delimiter;
    }

    const char Utilities::getDelimiter() {
        return m_delimiter;
    }
};
