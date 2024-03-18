#ifndef USER_H
#define USER_H

#include "utilities.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

/**
 * @class User
 * @brief Represents the User account.
 * @param ID
 * @param username
 * @param password
 * @param user_count
 * @param name
 * @param age
 */
class User
{
    /// @brief User ID.
    int32_t id;
    /// @brief Username.
    std::string username;
    /// @brief password.
    std::string password;

public:
    /// @brief Number of users.
    static int32_t user_count;
    /// @brief Name.
    std::string name;
    /// @brief Age.
    int16_t age;

    /**
     * @brief Getter. Returns the ID of the User.
     * @return The ID of the User.
     */
    int32_t get_id();
    /**
     * @brief Setter. Sets the User's ID.
     * @param us_id The ID to set for the User
     */
    void set_id(int32_t &us_id);
    /**
     * @brief Setter. Sets the username.
     * @param n The name to set for the User
     */
    void set_username(std::string &n);
    /**
     * @brief Setter. Sets the passwod.
     * @param n The password to set for the User
     */
    void set_password(std::string &p);
    /**
     * @brief Getter. Returns the username of the User.
     * @return The username of the User.
     */
    std::string get_username();
    /**
     * @brief Getter. Returns the password of the User.
     * @return The password of the User.
     */
    std::string get_password();

    /**
     * @brief Default constructor.
     *
     * Creates a new User object with id and age initialized to 0 .
     */
    User();
    /**
     * @brief Constructor.
     *
     * Creates a new User object.
     *
     * @param n Name of User.
     * @param a Age of User.
     * @param us Username.
     * @param pass User password.
     */
    User(std::string n, int16_t a, std::string us, std::string pass);
};

/**
 * @brief Get the Username from user input.
 *
 * Checks if the username is one word and 
 * is not q or Q as these characters are reserved for exiting.
 * 
 * @param uname The string to get input to
 * @param registeredUsers Vector of all users
 */
void getUsername(std::string &uname, std::vector<User> &registeredUsers);
/**
 * @brief Get the password from user input.
 *
 * @param uname The string to get input to
 */
void getPassword(std::string &input);

/**
 * @brief Login to the program.
 *
 * Checks whether the user exists and their credentials are correct.
 *
 * @param username Username
 * @param password Password
 * @param registeredUsers Vector of all users
 * @return int
 */
int login(const std::string &username, const std::string &password,
          std::vector<User> &registeredUsers);

/**
 * @brief Register new User.
 *
 * Creates a new user with data from user input and
 * adds it to the vector of all users.
 * @param registeredUsers Vector of all users to add new user to.
 * @return int Returns the ID of the newly registered user
 */
int registerNewUser(std::vector<User> &registeredUsers);

#endif // USER_H