#include "functions.h"
#include "binaryrw.h"

int main()
{
    std::vector<Workout> allworkouts;
    std::vector<Exercise> allexercises;
    std::vector<User> registeredUsers = read_users();
    if (registeredUsers.empty()) {
        write_users(registeredUsers);
    }
    std::vector<Training> trainings;

    Sortcon sort_condition {Sortcon::ALPHA};

    int32_t current_user = 0;
    std::string choice;
    int logsign = 0;
    
    bool save = false;
    std::string username, password;

    while (true) {
        std::cout << "1.Login\n2.Sign up\n3.Quit\n4.List all usernames"
        "\n\nEnter your choice: ";
        pmenuinput(logsign);
        if (logsign == 3) {
            return 1;
        }
        if (logsign == 2) {
            current_user = registerNewUser(registeredUsers);
            // Create files for new user, though empty, 
            // they are required to be able to login
            save_data(allexercises, allworkouts, trainings, current_user);
            write_users(registeredUsers);
        }
        if (logsign == 4) {
            if (!registeredUsers.empty()) {
                std::cout << std::endl;
                for(auto& u : registeredUsers) {
                    std::cout << u.get_username() << " (ID:"<< u.get_id() 
                               << ")" << std::endl;
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "No users found, please sign up\n\n";
            }
            continue;
        }

        std::cout << "Logging in... (Enter [q] as username to exit)\n";
        std::cout << "Please enter your username: ";
        std::cin >> username;
        if (username != "q" && username != "Q") {
            std::cout << "Please enter your password: ";
            std::cin >> password;
        }
        
        current_user = login(username, password, registeredUsers);


        if (current_user > 0) {

            int32_t current_user_id = current_user;
            read_data(allexercises, allworkouts, trainings, current_user_id);
            std::cout << "Welcome " << username << "!\n";
            while (choice[0] != 'Q' || choice[0] != 'q')
            {
                
                fort::char_table table;
                table 
                    << "S" << "Save" << fort::endr
                    << fort::separator 
                    << "A" << "Add workouts" << fort::endr
                    << fort::separator 
                    << "B" << "Add exercises" << fort::endr
                    << fort::separator 
                    << "P" << "Print all workouts" << fort::endr
                    << fort::separator 
                    << "M" << "Summary" << fort::endr
                    << fort::separator 
                    << "E" << "Add exercises to workouts" << fort::endr
                    << fort::separator
                    << "X" << "Print all exercises" << fort::endr
                    << fort::separator
                    << "R" << "Removing" << fort::endr
                    << fort::separator
                    << "G" << "Sorting" << fort::endr
                    << fort::separator
                    << "F" << "Filtering" << fort::endr
                    << fort::separator
                    << "C" << "Change data / complete workout" << fort::endr
                    << fort::separator
                    << "Q" << "Quit" << fort::endr;

                table.set_cell_content_fg_color(fort::color::light_yellow);
                std::cout << table.to_string() << std::endl;


                // Prompt the user to enter a choice
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                if (!(choice.size() > 1))
                {
                    size_t choicea = toupper(choice[0]);
                    switch (choicea)
                    {
                    case 'S':
                        std::cin.ignore(1, '\n');
                        save_data(allexercises, allworkouts, trainings, 
                        current_user_id);
                        break;
                    case 'A':
                        std::cin.ignore(1, '\n');
                        addworkouts(allworkouts, allexercises,trainings, 
                        current_user_id);
                        break;
                    case 'B': 
                        std::cin.ignore(1, '\n');
                        getexercises(allexercises);
                        break;
                    case 'C': 
                        std::cin.ignore(1, '\n');
                        changingmenu(allworkouts, allexercises, trainings);
                        break;
                    case 'P':
                        std::cin.ignore(1, '\n');
                        if (!allworkouts.empty()) {
                            std::cout << "All workouts: \n";
                            printWorkouts(allworkouts, allexercises, trainings, 
                            sort_condition);
                        }
                        else {
                            std::cout << "You do not have any workouts yet.\n";
                        }

                        break;
                    case 'M':
                        std::cin.ignore(1, '\n');
                        summarymenu(allworkouts, allexercises, trainings);
                        break;
                    case 'E':
                        std::cin.ignore(1, '\n');
                        if (!allworkouts.empty()) {
                            printWorkouts(allworkouts, allexercises, trainings, 
                            sort_condition);
                            add_exercises_to_w(allexercises, allworkouts, 
                            trainings);
                        }
                        else {
                            std::cout << "You do not have any workouts yet.\n";
                        }
                        break;
                    case 'X':
                        std::cin.ignore(1, '\n');
                        if (!allexercises.empty()) {
                            std::cout << allexercises;
                        }
                        else {
                            std::cout << "You do not have any exercises yet.\n";
                        }
                        break;
                    case 'R':
                        removingmenu(allworkouts, allexercises, trainings,
                                    sort_condition, registeredUsers, 
                                    current_user_id);
                        break;
                    case 'G':
                        sortingmenu(allworkouts, allexercises, trainings,
                                     sort_condition);
                        break;
                    case 'F':
                        filteringmenu(allworkouts, allexercises, trainings);
                        break;
                    case 'Q':
                        // Quit
                        std::cin.ignore(1, '\n');
                        getstringYesNo(save, "Do you want to save your data?"
                        "\n1.Yes\n2.No\n");
                        if (save) {
                            save_data(allexercises, allworkouts, trainings, 
                            current_user_id);
                            return 0;
                        }
                        return 0;
                    default:
                        std::cerr << color_outpt("Invalid choice!\n");
                        break;
                    }
                }
                else
                {
                    std::cerr << color_outpt("Invalid input!\n");
                }
            }
        }
        else if (current_user == -1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
        std::cout << color_outpt("Incorrect username or password.\n");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    }
}
