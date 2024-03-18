#ifndef DATE_H
#define DATE_H
#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

/**
 * @struct Date
 * @brief Represents the date.
 * @param day
 * @param month
 * @param year
 */
struct Date {
    /**
     * @brief Friend Overloaded insertion operator to output Date object.
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& d);

    /// @brief Day.
    uint16_t day;
    /// @brief Month.
    uint16_t month;
    /// @brief Year.
    int16_t year;
    /**
     * @brief Default constructor.
     * 
     * Creates a new Date object with day, month and year initialized to 1.
     */
    Date();
    /**
     * @brief Constructor.
     * Creates a new Date object.
     * @param d Day.
     * @param m Month.
     * @param y Year.
     */
    Date(uint16_t d, uint16_t m, int16_t y);
    /**
     * @brief Checks if the year of the Date is a leap year.
     * @return True if the year is a leap year, false otherwise.
     */
    bool isLeapYear() const;
    /**
     * @brief Checks if the Date object represents a valid date.
     * 
     * This function validates whether the day, month, and year values of the
     * Date object correspond to a valid date in the Gregorian calendar. 
     * It takes into account the varying number of days in each month and 
     * handles leap years.
     * 
     * @return True if the Date is a valid date, false otherwise.
     */
    bool isValidDate() const;
    /**
     * @brief Less-than overloading.
     * @param other Another Date object.
     * @return Whether the Date is less than other Date.
     */
    bool operator < (const Date& other) const;
    /**
     * @brief Greater-than overloading.
     * @param other Another Date object.
     * @return Whether the Date is greater than other Date.
     */
    bool operator > (const Date& other) const;
    /**
     * @brief Greater-than or Equal To overloading.
     * @param other Another Date object.
     * @return Whether the Date is greater than or equal to other Date.
     */
    bool operator >= (const Date& other) const;
    /**
     * @brief Less-than or Equal To overloading.
     * @param other Another Date object.
     * @return Whether the Date is less than or equal to other Date.
     */
    bool operator <= (const Date& other) const;

};
/**
* @brief Overloaded insertion operator to output Date object.
* @param os The output stream to write the Date object to.
* @param d The Date object to be output.
* @return Reference to the output stream after writing the Date object.
*/
std::ostream& operator<<(std::ostream& os, const Date& d);

/**
 * @brief Retrieves a Date object from user input as a string.
 * 
 * It validates the input, ensuring that the day, month, and 
 * year values are valid and conform to the Gregorian calendar rules. 
 * If the user enters an invalid date, the function prompts for a
 * valid date until one is provided.
 * @throws std::invalid_argument gets thrown and caught if the user
 * enters invalid date
 * @return Dare object representing the valid date entered by the user
 * @note The input is provided through standard input (cin)
*/
Date getstringdate();

#endif // !DATE_H
