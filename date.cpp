#include "date.h"
Date::Date(uint16_t d, uint16_t m, int16_t y)
    : day{ d }, month(m), year(y) {}

Date::Date()
{
    day = 1;
    month = 1;
    year = 1;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.day << "." << d.month << "." << d.year;
    return os;
}

bool Date::isLeapYear() const
{
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool Date::isValidDate() const
{
    if (month < 1 || month > 12) {
        return false;
    }

    uint16_t max_day = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        max_day = 30;
    }
    else if (month == 2) {
        max_day = isLeapYear() ? 29 : 28;
    }

    if (day < 1 || day > max_day) {
        return false;
    }

    if (year <= 0 || year > 9999) {
        return false;
    }

    return true;
}

bool Date::operator < (const Date& other) const
{
    if (year != other.year) {
        return year < other.year;
    }
    else if (month != other.month) {
        return month < other.month;
    }
    else {
        return day < other.day;
    }
}

bool Date::operator > (const Date& other) const
{
    if (year != other.year) {
        return year > other.year;
    }
    else if (month != other.month) {
        return month > other.month;
    }
    else {
        return day > other.day;
    }
}

bool Date::operator>=(const Date& other) const
{
    if (year != other.year) {
        return year >= other.year;
    }
    else if (month != other.month) {
        return month >= other.month;
    }
    else {
        return day >= other.day;
    }
}

bool Date::operator<=(const Date &other) const
{
    if (year != other.year) {
        return year <= other.year;
    }
    else if (month != other.month) {
        return month <= other.month;
    }
    else {
        return day <= other.day;
    }
}

Date getstringdate() {

    int16_t day, month, year;
    while (true) {
        std::cout << "Enter the date (Format: DD MM YYYY): ";
        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        ss >> day >> month >> year;

        try {
            // Check if all three values were converted to integers
            if (ss.fail() || !ss.eof()) {
                throw std::invalid_argument("\033[1;31mError: Please enter a"
                " valid date\n\033[0m");
            }

            // Check if the date is valid
            Date date(day, month, year);
            if (!date.isValidDate()) {
                throw std::invalid_argument("\033[1;31mError: Please enter a"
                " valid date\n\033[0m");
            }
            else {
                return date;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what();
        }
    }
}
