#include "user.h"

int32_t User::user_count = 0;
void getUsername(std::string &uname, std::vector<User> &registeredUsers)
{
    while (true)
    {
        getInput(uname, "Please create a username: ");

        bool has_space = false;
        bool alr_exist = false;
        for (char c : uname)
        {
            if (std::isspace(c))
            {
                has_space = true;
                break;
            }
        }

        if (uname == "q" || uname == "Q")
        {
            std::cerr << color_outpt("This username cannot be used,"
                                    " please enter another one\n");
        } else if (has_space)
        {
            std::cerr << color_outpt("Please enter one word\n");
        }
        else
        {
            for (auto &u : registeredUsers)
            {
                if (u.get_username() == uname)
                {
                    alr_exist = true;
                    std::cout << "This username already exists, "
                                 "please enter another one.\n";
                    break;
                }
            }
            if (!alr_exist)
            {
                break;
            }
        }
    }
}

void getPassword(std::string &password)
{
    while (true)
    {
        getInput(password, "Please create a password: ");

        bool has_space = false;
        for (char c : password)
        {
            if (std::isspace(c))
            {
                has_space = true;
                break;
            }
        }

        if (has_space)
        {
            std::cerr << color_outpt("Please enter one word\n");
        }
        else
        {
            break;
        }
    }
}

int registerNewUser(std::vector<User> &registeredUsers)
{
    std::string name, username, password;
    int16_t age;
    getInput(name, "Please enter your name: ");
    getInput(age, "Please enter your age: ");
    getUsername(username, registeredUsers);
    getPassword(password);
    User newUser(name, age, username, password);
    registeredUsers.push_back(newUser);
    std::cout << "User " << name << " registered successfully! ID:"
              << User::user_count << "\n";
    return newUser.get_id();
}

int login(const std::string &username, const std::string &password,
          std::vector<User> &registeredUsers)
{
    if (username == "q" || username == "Q")
    {
        return -1;
    }
    for (auto &user : registeredUsers)
    {
        if (user.get_username() == username)
        {
            if (user.get_password() == password)
            {
                return user.get_id();
            }
        }
    }
    return 0;
}

int32_t User::get_id()
{
    return id;
}

void User::set_id(int32_t &us_id)
{
    id = us_id;
}

void User::set_username(std::string &n)
{
    username = n;
}

void User::set_password(std::string &p)
{
    password = p;
}

std::string User::get_username()
{
    return username;
}

std::string User::get_password()
{
    return password;
}

User::User()
{
    id = 0;
    age = 0;
    user_count++;
}

User::User(std::string n, int16_t a, std::string us, std::string pass)
{
    user_count++;
    name = n;
    age = a;
    username = us;
    password = pass;
    id = User::user_count;
}
