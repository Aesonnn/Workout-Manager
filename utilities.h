#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <type_traits>
#include <cctype>
#include <sstream>
#include <algorithm>
#include "fort.hpp"


/**
 * @enum Difficulty
 * @brief Represents the difficulty levels of exercises/workouts.
 */
enum class Difficulty {
    /// Easy difficulty level.
    EASY,
    /// Medium difficulty level.
    MEDIUM,
    /// Hard difficulty level.
    HARD,
    /// Unknown difficulty level.
    UNKNOWN
};

/**
 * @enum Sortcon
 * @brief Sorting conditions which determine the output of workouts.
 * 
 * Workouts are sorted and then outputted according to one of the sorting 
 * conditions.
 * 
 * @see printWorkouts(std::vector<Workout>& allworkouts, 
 * std::vector<Exercise>& allexercises, std::vector<Training>& trainings, 
 * Sortcon sc)
 *
 */
enum class Sortcon { 
    /// Sort alphabetically.
    ALPHA,
    /// Sort by ID.
    ID,
    /// Sort by difficulty.
    DIFF,
    /// Sort by duration.
    DURAT,
    /// Sort by calories burnt.
    CALOR,
    /// Sort by date.
    DATE
};

/**
 * @brief Color the output red
 * @param s The text to color.
 * @return String colored red.
 */
std::string color_outpt(const std::string&& s);

/**
 * @brief Overloaded extraction operator to read 
 * a Difficulty value from an input stream.
 * 
 * It also checks the user input.
 * 
 * @param is The input stream to read the Difficulty value from.
 * @param c Reference to the Difficulty object where the value will be stored.
 * @return Reference to the input stream after reading the Difficulty value.
*/
std::istream& operator>>(std::istream& is, Difficulty& c);
/**
 * @brief Overloaded insertion operator to output Difficulty object.
 * @param os The output stream to write the Difficulty object to.
 * @param c The Difficulty object to be output.
 * @return Reference to the output stream after writing the Difficulty object.
*/
std::ostream& operator<<(std::ostream& os, const Difficulty& c);


/**
 * @brief Get the input from user Yes/No.
 *
 * Checks the user input. Only 1 or 2 is accepted.
 * 1 sets boolean to true, 2 to false.
 *
 * @param input The bool to change.
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct
*/
void getstringYesNo(bool& input, std::string s);


/**
 * @brief Get the ID of workout/exercise from user.
 *
 * Checks the user input. Only positive integers accepted.
 * Checks if the ID of object exists, if not asks for it again
 * or allows to exit.
 *
 * @tparam objects The vector of either exercises or workouts.
 * @param s The prompt to output.
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct.
 * @return ID of the object
*/
template <typename L>
int getID(const std::vector<L>& objects, const std::string &&s) {
    int32_t input = 0;
    std::cout << s;
    while (true) {
        std::string inpstream;
        std::getline(std::cin, inpstream);

        std::stringstream ss(inpstream);

        if (inpstream == "q" || inpstream == "Q") {
            break;
        }
        try
        {
            ss >> input;
            if (ss.fail() || !ss.eof() || input <= 0 
                || input > std::numeric_limits<int32_t>::max()) {
                throw std::invalid_argument(color_outpt("Invalid input."
                "Please enter a non - negative integer value not greater "
                "than 2,147,483,647\n"));
            }
            else {
                bool id_exists = false;
                for (const auto& c : objects) {
                    if (c.id == input) {
                        id_exists = true;
                        return input;
                    }
                }
                if (id_exists) {
                    break;
                }
                else {
                    throw std::invalid_argument(color_outpt("This id does not "
                    "exist, please enter another one or type [q] to exit.\n"));
                }
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what();
        }
    }
    return 0;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Gets string or integer input from user and validates it.
 *
 * If the input is a string the function check whether it is too long
 * as well as removes all spaces before and after the string, as well
 * as any repetitive spaces between the words.
 * If the input is an integer the function checks whether it is
 * negative, contains non-numbers or input fails due to overflow
 * or other reasons. If so, it asks for the input again until
 * it is correct.
 *
 * @tparam input Template parameter - integer or string.
 * @param s The prompt to output.
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct
*/
template <typename T>
void getInput(T& input, const std::string&& s = "Enter an integer value: ") {
    if constexpr (std::is_same<T, std::string>::value) {
        std::cout << s;
        while (true) {
            getline(std::cin, input);
            if (input.size() > 35) {
                std::cout << color_outpt("Please enter a more concise name "
                          "(not more than 35 symbols, including spaces)\n");
                continue;
            }
            bool osstr = true;
            for (char& c : input) {
                if (!std::isspace(c)) {
                    osstr = false;
                    break;
                }
            }
            if (!osstr) {
                break;
            }
        }
        long long n = input.length();
        bool space = false;
        long long j = 0;

        while (j < n && (input[j] == ' ' || input[j] == '\t')) {
            j++;
        }
        long long upt = j;

        for (long long i = j; i < n; i++) {
            if (input[i] == ' ' || input[i] == '\t') {
                if (!space) {
                    input[j++] = ' ';
                    space = true;
                }
            }
            else {
                input[j++] = input[i];
                space = false;
            }
        }

        while (j > 0 && (input[j - 1] == ' ' || input[j - 1] == '\t')) {
            j--;
        }

        input.resize(j);
        input.erase(0, upt);
        

    }
    else {
        std::cout << s;
        while (true) {
            std::string impstream;
            std::getline(std::cin, impstream);

            std::stringstream ss(impstream);
            ss >> input;

            try {
                if (ss.fail() || !ss.eof() || input <= 0 
                    || input > std::numeric_limits<T>::max()) {
                    throw std::invalid_argument(color_outpt("Invalid input. "
                    "Please enter a non-negative integer value not greater"
                    " than "
                    + std::to_string(std::numeric_limits<T>::max()) + ".\n"));
                }
                else {
                    break;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << e.what();
            }
        }
    }

}
#endif // !UTILITIES_H
