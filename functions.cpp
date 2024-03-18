#include "functions.h"
#include <numeric>

void addworkouts(std::vector<Workout> &allworkouts,
                 std::vector<Exercise> &allexercises,
                 std::vector<Training> &trainings, int32_t &us_id)
{
    int32_t selected_wid = 0;
    std::vector<int32_t> ex_ids;

    int32_t new_wid = 0;

    if (!allworkouts.empty())
    {

        int32_t ans;
        std::cout << "You can create the same workout again "
                     "(It will have different ID)";
        while (true)
        {
            std::cout << "\nDo you wish to choose from already created "
                         "workouts or create new ones? "
                         "\n1.Choose the workout\n2.Create workout\n3.Exit\n";
            std::string impstream;
            std::getline(std::cin, impstream);

            std::stringstream ss(impstream);
            if (impstream == "3")
            {
                break;
            }
            ss >> ans;

            try
            {
                if (ss.fail() || !ss.eof() || ans <= 0 || ans > 3)
                {
                    throw std::invalid_argument(color_outpt("Invalid input. "
                    "Please enter a non-negative integer value not "
                    "greater than 2,147,483,647.\n"));
                }
                else if (ans == 1)
                {
                    printWorkouts(allworkouts, allexercises, trainings);
                    selected_wid = getID(allworkouts, "Enter the ID of the "
                    "workout you want to add again (enter [q] to exit): ");
                    if (selected_wid == 0) {
                        break;
                    }
                    for (const auto &w : allworkouts)
                    {
                        if (w.id == selected_wid)
                        {
                            Workout new_w(us_id);
                            new_w.name = w.name;
                            new_w.calories_burnt = w.calories_burnt;
                            new_w.completed = w.completed;
                            if (new_w.completed)
                                new_w.date = getstringdate();
                            new_w.difficulty = w.difficulty;
                            new_w.duration = w.duration;
                            allworkouts.push_back(new_w);
                            new_wid = new_w.id;
                            break;
                        }
                    }
                    for (const auto &t : trainings)
                    {
                        if (t.w_id == selected_wid)
                        {
                            ex_ids.push_back(t.e_id);
                        }
                    }
                    for (auto &e : ex_ids)
                    {
                        trainings.push_back(Training(new_wid, e));
                    }
                    ex_ids.clear();
                    selected_wid = 0;
                    new_wid = 0;
                    std::cout << "Created!\n";
                }
                else if (ans == 2)
                {
                    getWorkouts(allworkouts, us_id);
                    break;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what();
            }
        }
    }
    else
    {
        getWorkouts(allworkouts, us_id);
    }
}

void add_exercises_to_w(std::vector<Exercise> &allexercises,
                        const std::vector<Workout> &allworkouts,
                        std::vector<Training> &trainings)
{
    int exercise_chooseid;
    std::vector<Exercise> current_exercises;
    bool exitc = false, ex_option = false;
    int32_t wid;
    while (true)
    {
        std::cout << "Enter the ID of the workout (type [q] to exit): ";
        std::string impstream;
        std::getline(std::cin, impstream);

        std::stringstream ss(impstream);
        if (impstream == "q" || impstream == "Q")
        {
            break;
        }
        ss >> wid;

        try
        {
            if (ss.fail() || !ss.eof() || wid <= 0)
            {
                throw std::invalid_argument(color_outpt("Invalid input. "
                "Please enter a non-negative integer value not "
                "greater than 2,147,483,647.\n"));
                continue;
            }
            else
            {
                bool found = false;
                // bool foundex = false;
                int32_t select_wk_id = 0;
                // const Exercise* selected_exercise_ptr = nullptr;

                for (const auto &workout : allworkouts)
                {
                    if (workout.id == wid)
                    {
                        select_wk_id = workout.id;
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    if (!allexercises.empty())
                    {
                        getstringYesNo(ex_option, "Do you wish to choose "
                        "from already created exercises or create new ones?"
                        "\n1.Choose the exercises\n2.Add exercises\n");
                    }
                    if (ex_option)
                    {
                        std::cout << "Available exercises (You can choose "
                                     "one exercise more than once):"
                                  << std::endl;
                        std::cout << "Enter [q] to exit" << std::endl;

                        std::cout << allexercises << std::endl;
                        std::cout << "Enter exercise ID or "
                                     "enter [q] to exit:\n";
                        while (true)
                        {
                            exercise_chooseid = getID(allexercises, "");
                            if (exercise_chooseid == 0)
                            {
                                exitc = false;
                                select_wk_id = 0;
                                break;
                            }
                            auto ite = std::find(allexercises.begin(),
                                                 allexercises.end(),
                                                exercise_chooseid);
                            if (ite != allexercises.end())
                            {
                                trainings.push_back(Training{select_wk_id,
                                exercise_chooseid});
                            }
                            else
                            {
                                std::cout << "No exercise with "
                                             "such ID exists\n";
                            }
                            std::cout << "Added! Add another exercise or"
                                         " enter [q] to exit:\n";
                        }
                        select_wk_id = 0;
                        if (!exitc)
                            break;
                    }
                    else if (!ex_option)
                    {
                        getexercises(current_exercises);
                        for (auto &e : current_exercises)
                        {
                            trainings.push_back(Training{select_wk_id, e.id});
                            allexercises.push_back(e);
                        }
                        current_exercises.clear();
                        break;
                    }
                }
                else
                {
                    getstringYesNo(exitc, "Workout with ID " +
                    std::to_string(wid) + " does not exist, do you wish"
                    " to enter another one?\n1-Yes\n2-Exit\n");
                    if (!exitc)
                    {
                        break;
                    }
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what();
        }
    }
    current_exercises.clear();
}

void pmenuinput(int &logsign)
{
    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        ss >> logsign;
        try
        {
            if (ss.fail() || !ss.eof() || logsign < 1 || logsign > 4)
            {
                throw std::invalid_argument(color_outpt("Invalid input. "
                "Please enter 1, 2, 3 or 4\n"));
            }
            else
            {
                break;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what();
        }
    }
}

void removingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
                  std::vector<Training> &trainings, Sortcon &sc,
                  std::vector<User> &users, int32_t &us_id)
{
    bool exitcondition = false;
    std::string choice;
    while (choice[0] != 'Q' || choice[0] != 'q')
    {
        fort::char_table table;
        table
            << "W"
            << "Remove workout by ID" << fort::endr
            << fort::separator
            << "E"
            << "Remove exercise by ID" << fort::endr
            << " "
            << "(Removes exercise from workouts too)" << fort::endr
            << fort::separator
            << "R"
            << "Remove exercise only from workout" << fort::endr
            << fort::separator
            << "D"
            << "Remove workouts before the date (including)" << fort::endr
            << fort::separator
            << "O"
            << "Delete my account" << fort::endr
            << fort::separator
            << "Q"
            << "Back" << fort::endr;

        table.set_cell_content_fg_color(fort::color::light_green);
        std::cout << table.to_string() << std::endl;

        // Prompt the user to enter a choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!(choice.size() > 1))
        {
            size_t choicea = toupper(choice[0]);
            switch (choicea)
            {
            case 'W':
                std::cin.ignore(1, '\n');
                removeWorkout(work, exer, trainings, sc);
                break;
            case 'E':
                std::cin.ignore(1, '\n');
                removeExercise(exer, trainings);
                break;
            case 'R':
                std::cin.ignore(1, '\n');
                removeExercisefromWorkout(work, exer, trainings, sc);
                break;
            case 'D':
                std::cin.ignore(1, '\n');
                removeWorkout_fromdate(work, exer, trainings);
                break;
            case 'O':
                std::cin.ignore(1, '\n');
                remove_curruser(users, us_id);
                break;
            case 'Q':
                std::cin.ignore(1, '\n');
                exitcondition = true;
                break;
            default:
                std::cerr << color_outpt("Invalid choice!\n");
                break;
            }
        }
        else
        {
            std::cerr << color_outpt("Invalid input!\n");
        }
        if (exitcondition)
            break;
    }
}

//////////////////////////////////////////////////////////////////////
// Sorting
//////////////////////////////////////////////////////////////////////

void sortingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
                 std::vector<Training> &trainings, Sortcon &sc)
{
    bool exitcondition = false;
    std::string choice;
    while (choice[0] != 'Q' || choice[0] != 'q')
    {
        fort::char_table table;
        table
            << "D"
            << "Sort workouts by date" << fort::endr
            << fort::separator
            << "C"
            << "Sort workouts by calories" << fort::endr
            << fort::separator
            << "I"
            << "Sort workouts by ID" << fort::endr
            << fort::separator
            << "H"
            << "Sort workouts by difficulty" << fort::endr
            << fort::separator
            << "E"
            << "Sort exercises by difficulty" << fort::endr
            << fort::separator
            << "T"
            << "Sort workouts by duration" << fort::endr
            << fort::separator
            << "A"
            << "Sort exercises alphabetically" << fort::endr
            << fort::separator
            << "U"
            << "Sort workouts alphabetically" << fort::endr
            << fort::separator
            << "Q"
            << "Back" << fort::endr;

        table.set_cell_content_fg_color(fort::color::light_green);
        std::cout << table.to_string() << std::endl;

        // Prompt the user to enter a choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!(choice.size() > 1))
        {
            size_t choicea = toupper(choice[0]);
            switch (choicea)
            {
            case 'D':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::DATE;
                printWorkouts(work, exer, trainings, sc);
                break;
            case 'C':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::CALOR;
                printWorkouts(work, exer, trainings, sc);
                break;
            case 'I':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::ID;
                printWorkouts(work, exer, trainings, sc);

                break;
            case 'H':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::DIFF;
                printWorkouts(work, exer, trainings, sc);
                break;
            case 'E':
                std::cin.ignore(1, '\n');
                if (exer.empty())
                {
                    std::cout << "You do not have any exercises yet\n";
                    break;
                }
                std::sort(exer.begin(), exer.end(), [](Exercise fd, Exercise sd)
                          { return (fd.difficulty > sd.difficulty); });
                std::cout << exer << std::endl;

                // Sort the trainings vector so more difficult exercises show 
                // first in workout
                // Upon outputting, the trainings vector will be sorted again,
                // but the order of exercises will not change
                std::sort(trainings.begin(), trainings.end(), [&exer]
                (Training fd, Training sd)
                {
                    auto iter1 = std::find(exer.begin(), exer.end(), fd.e_id);
                    auto iter2 = std::find(exer.begin(), exer.end(), sd.e_id);

                    return (*iter1).compareByDiff(*iter2); });
                std::sort(trainings.begin(), trainings.end());
                break;
            case 'T':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::DURAT;
                printWorkouts(work, exer, trainings, sc);
                break;
            case 'A':
                std::cin.ignore(1, '\n');
                if (exer.empty())
                {
                    std::cout << "You do not have any exercises yet\n";
                    break;
                }
                std::sort(exer.begin(), exer.end(), [](Exercise fd, Exercise sd)
                          { return (fd.name < sd.name); });

                std::cout << exer << std::endl;
                std::sort(trainings.begin(), trainings.end(), [&exer]
                (Training fd, Training sd)
                  {
                    auto iter1 = std::find(exer.begin(), exer.end(), fd.e_id);
                    auto iter2 = std::find(exer.begin(), exer.end(), sd.e_id);

                    return (*iter1).compareByName(*iter2); });
                std::sort(trainings.begin(), trainings.end());
                break;
            case 'U':
                std::cin.ignore(1, '\n');
                if (work.empty() && trainings.empty())
                {
                    std::cout << "You do not have any workouts yet\n";
                    break;
                }
                sc = Sortcon::ALPHA;
                printWorkouts(work, exer, trainings, sc);
                break;
            case 'Q':
                std::cin.ignore(1, '\n');
                exitcondition = true;
                break;
            default:
                std::cerr << color_outpt("Invalid choice!\n");
                break;
            }
        }
        else
        {
            std::cerr << color_outpt("Invalid input!\n");
        }
        if (exitcondition)
            break;
    }
}

//////////////////////////////////////////////////////////////////////
// Filtering
//////////////////////////////////////////////////////////////////////
void filteringmenu(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                    std::vector<Training> &trainings)
{
    bool exitcondition = false;
    std::string choice;
    while (choice[0] != 'Q' || choice[0] != 'q')
    {
        fort::char_table table;
        table
            << "C"
            << "Filter completed/not completed" << fort::endr
            << " "
            << "workouts " << fort::endr
            << fort::separator
            << "W"
            << "Filter workouts by ID" << fort::endr
            << fort::separator
            << "E"
            << "Filter exercises by ID" << fort::endr
            << fort::separator
            << "N"
            << "Filter workouts by name" << fort::endr
            << fort::separator
            << "M"
            << "Filter exercises by name" << fort::endr
            << fort::separator
            << "J"
            << "Filter exercises by difficulty" << fort::endr
            << fort::separator
            << "R"
            << "Filter workouts with " << fort::endr
            << " "
            << "exercises having >= N reps" << fort::endr
            << fort::separator
            << "S"
            << "Filter workouts with " << fort::endr
            << " "
            << "exercises having >= N sets" << fort::endr
            << fort::separator
            << "H"
            << "Filter workouts with " << fort::endr
            << " "
            << "easy / medium / hard exercises" << fort::endr
            << fort::separator
            << "D"
            << "Filter workouts starting from date " << fort::endr
            << fort::separator
            << "Q"
            << "Back" << fort::endr;

        table.set_cell_content_fg_color(fort::color::light_green);
        std::cout << table.to_string() << std::endl;
        // Prompt the user to enter a choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!(choice.size() > 1))
        {
            size_t choicea = toupper(choice[0]);
            switch (choicea)
            {
            case 'C':
                std::cin.ignore(1, '\n');
                if (!work.empty())
                {
                    filtr_compltd(work, exer, trainings);
                }
                else
                {
                    std::cout << "You currently have no workouts\n";
                }
                break;
            case 'W':
                std::cin.ignore(1, '\n');
                if (!work.empty())
                {
                    filtr_wid(work, exer, trainings);
                }
                else
                {
                    std::cout << "You do not have any workouts yet\n";
                }
                break;
            case 'E':
                std::cin.ignore(1, '\n');
                if (!exer.empty())
                {
                    filtr_eid(exer);
                }
                else
                {
                    std::cout << "You do not have any exercises yet\n";
                }
                break;
            case 'N':
                std::cin.ignore(1, '\n');
                if (!work.empty())
                {
                    filtr_wname(work, exer, trainings);
                }
                else
                {
                    std::cout << "You do not have any workouts yet\n";
                }
                break;
            case 'M':
                std::cin.ignore(1, '\n');
                if (!exer.empty())
                {
                    filtr_ename(exer);
                }
                else
                {
                    std::cout << "You do not have any exercises yet\n";
                }
                break;
            case 'J':
                std::cin.ignore(1, '\n');
                if (!exer.empty())
                {
                    filtr_ediff(exer);
                }
                else
                {
                    std::cout << "You do not have any exercises yet\n";
                }
                break;
            case 'R':
                std::cin.ignore(1, '\n');

                if (!trainings.empty())
                {
                    filtr_wreps(work, exer, trainings);
                }
                else
                {
                    std::cout << "None of your workouts has exercises.\n";
                }
                break;
            case 'S':
                std::cin.ignore(1, '\n');

                if (!trainings.empty())
                {
                    filtr_wsets(work, exer, trainings);
                }
                else
                {
                    std::cout << "None of your workouts has exercises.\n";
                }
                break;
            case 'H':
                std::cin.ignore(1, '\n');

                if (!trainings.empty())
                {
                    filtr_wexerc(work, exer, trainings);
                }
                else
                {
                    std::cout << "None of your workouts has exercises.\n";
                }
                break;
            case 'D':
                std::cin.ignore(1, '\n');
                if (!(work.empty() && trainings.empty()))
                {
                    filtr_wsdate(work, exer, trainings);
                }
                else
                {
                    std::cout << "You do not have any workouts yet\n";
                }
                break;
            case 'Q':
                std::cin.ignore(1, '\n');
                exitcondition = true;
                break;
            default:
                std::cerr << color_outpt("Invalid choice!\n");
                break;
            }
        }
        else
        {
            std::cerr << color_outpt("Invalid input!\n");
        }
        if (exitcondition)
            break;
    }
}

void summarymenu(const std::vector<Workout> &work,
                 const std::vector<Exercise> &exer,
                 const std::vector<Training> &trainings)
{
    bool exitcondition = false;
    std::string choice;

    int numof_compl_work = 0;
    int numof_notompl_work = 0;

    int nof_has_exr = 0;
    int morethan = 0;

    int nof_work = 0;


    std::set<int32_t> works_withexer;
    Difficulty udiff{Difficulty::UNKNOWN};

    int total_calories = 0;
    Date start_date;
    Date default_date;

    int32_t last_wid = -1;
    while (choice[0] != 'Q' || choice[0] != 'q')
    {
        fort::char_table table;
        table
            << "C"
            << "Count the calories burnt (All workouts)" << fort::endr
            << fort::separator
            << "S"
            << "Count the calories (from certain date)" << fort::endr
            << fort::separator
            << "W"
            << "Number of workouts" << fort::endr
            << fort::separator
            << "E"
            << "Number of exercises" << fort::endr
            << fort::separator
            << "P"
            << "Number of completed/not completed workouts" << fort::endr
            << fort::separator
            << "R"
            << "Number of workouts with/without exercises" << fort::endr
            << fort::separator
            << "D"
            << "Number of workouts with " << fort::endr
            << " "
            << "easy / medium / hard exercises" << fort::endr
            << fort::separator
            << "M"
            << "Number of workouts that burn more than N calories" << fort::endr
            << fort::separator
            << "L"
            << "Number of workouts with duration longer than N" << fort::endr
            << fort::separator
            << "Q"
            << "Back" << fort::endr;

        table.set_cell_content_fg_color(fort::color::light_green);
        std::cout << table.to_string() << std::endl;

        // Prompt the user to enter a choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!(choice.size() > 1))
        {
            size_t choicea = toupper(choice[0]);
            switch (choicea)
            {
            case 'C':
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                std::cout << "Total number of calories burnt "
                            "through all workouts: ";
                for (const auto &w : work)
                {
                    total_calories += w.calories_burnt;
                }
                std::cout << total_calories << std::endl;
                total_calories = 0;

                std::cout << "Total number of calories burnt "
                            "through completed workouts: ";
                for (const auto &w : work)
                {
                    if (w.completed)
                        total_calories += w.calories_burnt;
                }
                std::cout << total_calories << std::endl;
                total_calories = 0;
                break;
            case 'S':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                std::cout << "Enter the date from which you want"
                            " to count calories: ";
                start_date = getstringdate();
                for (const auto &w : work)
                {
                    if ((w.date > default_date) && (w.date >= start_date))
                    {
                        total_calories += w.calories_burnt;
                    }
                }
                std::cout << "Total number of calories burnt "
                "through all workouts: " << total_calories << std::endl;
                total_calories = 0;
                break;
            case 'W':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                std::cout << "You currently have: " << work.size() 
                << " workouts" << std::endl;
                break;
            case 'E':
                std::cin.ignore(1, '\n');
                if (exer.empty())
                {
                    std::cout << "You do not have any exercises yet.\n";
                    break;
                }
                std::cout << "You currently have: " << exer.size() 
                << " exercises" << std::endl;
                break;
            case 'P':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                for (const auto &w : work)
                {
                    if (w.completed)
                    {
                        numof_compl_work++;
                    }
                    else if (!w.completed)
                    {
                        numof_notompl_work++;
                    }
                }
                std::cout << "Number of completed workouts: " 
                          << numof_compl_work << std::endl
                          << "Number of not completed workouts: "
                          << numof_notompl_work << std::endl;
                numof_compl_work = 0;
                numof_notompl_work = 0;
                break;
            case 'R':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                for (const auto &w : work)
                {
                    auto it = std::find(trainings.begin(), trainings.end(), w);
                    if (it != trainings.end() && (it->w_id != last_wid))
                    {
                        nof_has_exr++;
                        last_wid = it->w_id;
                    }
                }
                std::cout << "Number of workouts with exercises: " 
                << nof_has_exr << std::endl
                          << "Number of workouts with no exercises: " 
                          << (work.size() - nof_has_exr) << std::endl;
                nof_has_exr = 0;
                break;
            case 'D':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                std::cout << "Workouts with which exercises would you like"
                " to count?\n";
                std::cin >> udiff;

                for (const auto &t : trainings)
                {
                    for (const auto &e : exer)
                    {
                        if (e.id == t.e_id && e.difficulty == udiff)
                        {
                            works_withexer.insert(t.w_id);
                            break;
                        }
                    }
                }
                std::cout << "Number of workouts with " << udiff 
                << " exercises: " << works_withexer.size() << std::endl;
                udiff = Difficulty::UNKNOWN;
                works_withexer.clear();
                break;
            case 'M':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                getInput(morethan, "Enter the number of calories: ");
                for (const auto &w : work)
                {
                    if (w.calories_burnt > morethan) {
                        ++nof_work;
                    }
                }
                std::cout << "Number of workouts that burn more than " 
                << morethan << " calories: " << nof_work << std::endl;
                nof_work = 0;
                morethan = 0;
                break;
            case 'L':
                std::cin.ignore(1, '\n');
                if (work.empty())
                {
                    std::cout << "You do not have any workouts yet.\n";
                    break;
                }
                getInput(morethan, "Enter the duration (minutes): ");
                for (const auto &w : work)
                {
                    if (w.duration > morethan) {
                        ++nof_work;
                    }
                }
                std::cout << "Number of workouts with duration longer than " 
                << morethan << " minutes: " << nof_work << std::endl;
                morethan = 0;
                nof_work = 0;
                break;
            case 'Q':
                std::cin.ignore(1, '\n');
                exitcondition = true;
                break;
            default:
                std::cerr << color_outpt("Invalid choice!\n");
                break;
            }
        }
        else
        {
            std::cerr << color_outpt("Invalid input!\n");
        }
        if (exitcondition)
            break;
    }
}

//////////////////////////////////////////////////////////////////
// Changing
//////////////////////////////////////////////////////////////////

void changingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                  std::vector<Training> &trainings)
{
    bool exitcondition = false;
    std::string choice;

    while (choice[0] != 'Q' || choice[0] != 'q')
    {
        fort::char_table table;
        table
            << "W"
            << "Change workout data" << fort::endr
            << fort::separator
            << "E"
            << "Change exercise data" << fort::endr
            << fort::separator
            << "Q"
            << "Back" << fort::endr;

        table.set_cell_content_fg_color(fort::color::light_green);
        std::cout << table.to_string() << std::endl;
        // Prompt the user to enter a choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!(choice.size() > 1))
        {
            size_t choicea = toupper(choice[0]);
            switch (choicea)
            {
            case 'W':
                std::cin.ignore(1, '\n');
                if (!work.empty()) {
                    changeObject(work, exer, trainings);
                }
                else {
                    std::cout << "You have no workouts yet.\n";
                }
                break;
            case 'E':
                std::cin.ignore(1, '\n');
                if (!exer.empty()) {
                    changeObject(exer);
                }
                else {
                    std::cout << "You have no exercises yet.\n";
                }
                break;
            case 'Q':
                std::cin.ignore(1, '\n');
                exitcondition = true;
                break;
            default:
                std::cerr << color_outpt("Invalid choice!\n");
                break;
            }
        }
        else
        {
            std::cerr << color_outpt("Invalid input!\n");
        }
        if (exitcondition)
            break;
    }
}

//////////////////////////////////////////////////////////////////////
// Removing functions
//////////////////////////////////////////////////////////////////////

void removeWorkout(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                    std::vector<Training> &trainings, Sortcon &sc)
{

    int32_t wid;
    if (!work.empty())
    {
        printWorkouts(work, exer, trainings, sc);
        wid = getID(work, "\nPlease enter the ID of the workout you"
        " want to remove (enter [q] to exit):");
        if (wid != 0)
        {
            work.erase(std::remove_if(work.begin(), work.end(), 
            [&wid](Workout &we)
            { return we.id == wid; }),
                       work.end());

            trainings.erase(std::remove_if(trainings.begin(), trainings.end(), 
            [&wid](Training t)
             { return t.w_id == wid; }),
            trainings.end());

            std::cout << "The workout has been successfully removed.\n";
            wid = 0;
        }
    }
    else
    {
        std::cout << "You do not have any workouts yet.\n";
    }
}

void removeExercise(std::vector<Exercise> &vector, 
                    std::vector<Training> &trainings)
{
    if (!vector.empty())
    {
        int32_t exid;
        std::cout << vector << std::endl;

        exid = getID(vector, "\nPlease enter the ID of the exercise"
        " you want to remove(enter [q] to exit): ");
        if (exid != 0)
        {
            vector.erase(std::remove_if(vector.begin(), vector.end(), 
            [&exid](Exercise &ex)
                { return ex.id == exid; }),
                         vector.end());
            trainings.erase(std::remove_if(trainings.begin(), trainings.end(),
             [&exid](Training &tr)
                { return (tr.e_id == exid); }),
                            trainings.end());
            std::cout << "The exercise has been successfully removed.\n";
            exid = 0;
        }
    }
    else
    {
        std::cout << "You do not have any exercises yet.\n";
    }
}

void removeExercisefromWorkout(std::vector<Workout> &work, 
                               std::vector<Exercise> &exer, 
                               std::vector<Training> &trainings, Sortcon &sc)
{
    int32_t woid;
    int32_t exid;
    std::vector<Exercise> temp_ex;

    std::vector<int> ex_ids;
    std::vector<Exercise> chosen_work_exercises;

    bool exitchosingexer = false;
    bool exists = false;
    if (!trainings.empty())
    {
        while (true)
        {
            printWorkouts(work, exer, trainings, sc);
            woid = getID(work, "\nPlease enter the ID of the workout from"
            " which you want to remove exercise (enter [q] to exit): ");
            if (woid != 0)
            {
                std::cout << "\nThis workout has following exercises: \n"
                          << std::endl;

                for (const auto &t : trainings)
                {
                    if (t.w_id == woid)
                    {
                        exists = true;
                        ex_ids.push_back(t.e_id);
                    }
                }
                for (const auto &e : exer)
                {
                    for (const auto &ids : ex_ids)
                    {
                        if (e.id == ids)
                        {
                            chosen_work_exercises.push_back(e);
                        }
                    }
                }
                std::cout << chosen_work_exercises;
                if (exists)
                {
                    while (!ex_ids.empty())
                    {
                        exid = getID(exer, "Please enter the ID of the"
                        " exercise you want to remove (enter [q] to exit): ");
                        auto iterex = std::find(ex_ids.begin(), 
                        ex_ids.end(), exid);
                        if (exid == 0)
                        {
                            break;
                        }
                        if (iterex != ex_ids.end())
                        {
                            trainings.erase(std::remove_if(trainings.begin(), 
                            trainings.end(), [&woid, &exid](Training &tr)
                            { return (tr.w_id == woid && tr.e_id == exid); }),
                            trainings.end());
                            std::cout << "The exercise has been successfully"
                            " removed from workout.\n";
                            chosen_work_exercises.erase(
                            std::remove_if(chosen_work_exercises.begin(), 
                            chosen_work_exercises.end(), [&exid](Exercise &e)
                            { return (e.id == exid); }),
                            chosen_work_exercises.end());
                            ex_ids.erase(
                            std::remove(ex_ids.begin(), 
                            ex_ids.end(), exid), ex_ids.end());
                            std::cout << chosen_work_exercises;
                        }
                        else
                        {
                            getstringYesNo(exitchosingexer, "This workout does"
                            " not have this exercise, do you want to enter"
                            " the other one?\n1.Yes\n2.No\n");
                            if (!exitchosingexer)
                            {
                                break;
                            }
                        }
                    }
                    woid = 0;
                    exid = 0;
                    ex_ids.clear();
                    chosen_work_exercises.clear();
                    temp_ex.clear();
                }
                else
                {
                    std::cout << "The chosen workout has no exercises.\n\n";
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        std::cout << "None of your workouts has exercises.\n";
    }
}

void removeWorkout_fromdate(std::vector<Workout> &work, 
                            std::vector<Exercise> &exer, 
                            std::vector<Training> &trainings)
{
    std::vector<int> temp_exids;

    Date todate;
    Date default_date;

    if (!work.empty())
    {
        printWorkouts(work, exer, trainings, Sortcon::DATE);
        todate = getstringdate();

        for (auto &w : work)
        {
            if (w.date > default_date && w.date <= todate)
            {
                temp_exids.push_back(w.id);
            }
        }
        if (!temp_exids.empty())
        {
            // Remove from wokouts vector
            work.erase(std::remove_if(work.begin(), work.end(), 
            [&todate, &default_date](Workout &we)
            { return (we.date > default_date && we.date <= todate); }),
            work.end());

            // Remove from trainings vector
            for (auto b : temp_exids)
            {
                trainings.erase(std::remove_if(trainings.begin(), 
                trainings.end(), [&todate, &b](Training t)
                { return t.w_id == b; }),
                trainings.end());
            }
            printWorkouts(work, exer, trainings, Sortcon::DATE);
            temp_exids.clear();
        }
        else
        {
            std::cout << "You have no workouts prior to this date\n";
        }
    }
    else
    {
        std::cout << "You do not have any workouts yet\n";
    }
}

void remove_curruser(std::vector<User> &users, const int32_t &us_id)
{
    std::string folder_name = "data_user" + std::to_string(us_id);
    bool del = false;
    getstringYesNo(del, "Are you sure you want to delete your account?"
    "\n1.Yes\n2.No\n");
    if (del == true)
    {
        users.erase(std::remove_if(users.begin(), users.end(), [&us_id]
        (User &u)
        { return u.get_id() == us_id; }),
        users.end());

        try
        {
            if (std::filesystem::remove_all(folder_name))
            {
                std::cout << "All your data has been deleted.\n";
            }
            else
            {
                std::cout << "Your data " << folder_name << " has already"
                " been deleted.\n";
            }
        }
        catch (const std::filesystem::filesystem_error &err)
        {
            std::cout << "filesystem error: " << err.what() << '\n';
        }
        write_users(users);
        users = read_users();
        exit(0);
    }
}

//////////////////////////////////////////////////////////////////////
// Sorting functions
//////////////////////////////////////////////////////////////////////

void sort_date(std::vector<Workout> &work, std::vector<Training> &trainings)
{

    std::sort(trainings.begin(), trainings.end(), [&work]
    (Training fd, Training sd)
        {
        auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
        auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

        return (*iter1 > *iter2); });
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
              { return (fd.date > sd.date); });
}

void sort_cal(std::vector<Workout> &work, std::vector<Training> &trainings)
{

    std::sort(trainings.begin(), trainings.end(), [&work]
    (Training fd, Training sd)
        {
        auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
        auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

        return (*iter1).compareByCal(*iter2); });
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
              { return (fd.calories_burnt > sd.calories_burnt); });
}

void sort_diff(std::vector<Workout> &work, std::vector<Training> &trainings)
{

    std::sort(trainings.begin(), trainings.end(), [&work]
    (Training fd, Training sd)
        {
        auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
        auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

        return (*iter1).compareByDiff(*iter2); });
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
              { return (fd.difficulty > sd.difficulty); });
}

void sort_dur(std::vector<Workout> &work, std::vector<Training> &trainings)
{

    std::sort(trainings.begin(), trainings.end(), [&work]
    (Training fd, Training sd)
        {
        auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
        auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

        return (*iter1).compareByDurat(*iter2); });
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
              { return (fd.duration > sd.duration); });
}

void sort_alpha(std::vector<Workout> &work, std::vector<Training> &trainings)
{
    sort_id(work, trainings);
    std::sort(trainings.begin(), trainings.end(), [&work]
    (Training& fd, Training& sd)
    {
        auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
        auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

        return (*iter1).compareByName(*iter2); });
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
              { return (fd.name < sd.name); });
}
void sort_id(std::vector<Workout>& work, std::vector<Training> &trainings)
{
    std::sort(work.begin(), work.end(), [](Workout fd, Workout sd)
        { return (fd.id < sd.id); });

    std::sort(trainings.begin(), trainings.end());
}

void filtr_compltd(std::vector<Workout> &work, 
                   std::vector<Exercise> &exer, 
                   std::vector<Training> &trainings)
{
    bool filternoncompleted = false;
    int32_t trid = 0;
    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_hexer;

    getstringYesNo(filternoncompleted, "Print\n1.Not completed\n2.Completed\n");
    if (filternoncompleted)
    {
        for (const auto &w : work)
        {
            auto it = std::find(trainings.begin(), trainings.end(), w);
            if (it == trainings.end())
            {
                if (w.completed == false)
                {
                    std::cout << "WARNING! THE FOLLOWING WORKOUT HAS"
                    " NO EXERCISES:" << std::endl
                              << w << std::endl;
                }
            }
        }
        // Filtering
        for (const auto &t : trainings)
        {
            for (const auto &w : work)
            {
                if (w.id == t.w_id && w.completed == false)
                {
                    workids_with_hexer.push_back(t.w_id);
                    break;
                }
            }
        }

        filtered_trainings = trainings;
        for (const auto &t : trainings)
        {
            trid = t.w_id;
            auto ite = std::find(workids_with_hexer.begin(), 
            workids_with_hexer.end(), trid);
            if (ite == workids_with_hexer.end())
            {
                filtered_trainings.erase(
                    std::remove_if(filtered_trainings.begin(), 
                    filtered_trainings.end(), [&trid](Training tr)
                    { return tr.w_id == trid; }),
                    filtered_trainings.end());
            }
        }

        // Outputting
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);

        filtered_trainings.clear();
        workids_with_hexer.clear();
        filternoncompleted = false;
    }
    else
    {
        for (const auto &w : work)
        {
            auto it = std::find(trainings.begin(), trainings.end(), w);
            if (it == trainings.end())
            {
                if (w.completed == true)
                {
                    std::cout << "WARNING! THE FOLLOWING WORKOUT HAS NO"
                    " EXERCISES:" << std::endl
                              << w << std::endl;
                }
            }
        }
        // Filtering
        for (const auto &t : trainings)
        {
            for (const auto &w : work)
            {
                if (w.id == t.w_id && w.completed == true)
                {
                    workids_with_hexer.push_back(t.w_id);
                    break;
                }
            }
        }

        filtered_trainings = trainings;
        for (const auto &t : trainings)
        {
            trid = t.w_id;
            auto ite = std::find(workids_with_hexer.begin(), 
            workids_with_hexer.end(), trid);
            if (ite == workids_with_hexer.end())
            {
                filtered_trainings.erase(
                std::remove_if(filtered_trainings.begin(), 
                filtered_trainings.end(), [&trid](Training tr)
                { return tr.w_id == trid; }),
                filtered_trainings.end());
            }
        }

        // Outputting
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);

        filtered_trainings.clear();
        workids_with_hexer.clear();
        filternoncompleted = false;
    }
}

void filtr_wid(std::vector<Workout> &work, std::vector<Exercise> &exer, 
               std::vector<Training> &trainings)
{
    int32_t chosen_workout_id = 0;
    bool found = false;
    int32_t last_workout_id = -1;
    std::vector<Exercise> temp_ex;
    getInput(chosen_workout_id, "Enter the workout ID: ");
    for (const auto &w : work)
    {
        if (chosen_workout_id == w.id)
        {
            found = true;
            auto it = std::find(trainings.begin(), trainings.end(), w);
            if (it == trainings.end())
            {
                std::cout << "WARNING! THE FOLLOWING WORKOUT HAS NO EXERCISES:" 
                << std::endl << w << std::endl;
            }
        }
    }
    if (!found)
    {
        std::cout << "You do not have a workout with this ID\n" << std::endl;
    }
    else
    {
        // Outputting
        for (const auto &t : trainings)
        {
            if (chosen_workout_id == t.w_id)
            {
                if (t.w_id != last_workout_id)
                {
                    std::cout << temp_ex << std::endl
                              << std::endl;
                    temp_ex.clear();
                    output_byid(t.w_id, work);
                    last_workout_id = t.w_id;
                }
                auto iter = std::find(exer.begin(), exer.end(), t.e_id);
                if (iter != exer.end())
                {
                    temp_ex.push_back(*iter);
                }
            }
        }
        if (!temp_ex.empty())
        {
            std::cout << temp_ex << std::endl
                      << std::endl;
        }
    }
    found = false;
    temp_ex.clear();
    last_workout_id = -1;
    chosen_workout_id = 0;
}

void filtr_eid(std::vector<Exercise> &exer)
{
    int32_t chosen_exercise_id = 0;
    bool found = false;
    getInput(chosen_exercise_id, "Enter the exercise ID: ");
    for (const auto &e : exer)
    {
        if (e.id == chosen_exercise_id)
        {
            found = true;
            std::cout << e;
        }
    }
    if (!found)
    {
        std::cout << "You do not have an exercise with this ID" << std::endl;
    }
    found = false;
    chosen_exercise_id = 0;
}

void filtr_wname(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                 std::vector<Training> &trainings)
{
    int32_t trid = 0;
    bool found = false;
    std::string chosen_workout_name;

    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_name;
    getInput(chosen_workout_name, "Enter the workout name "
        "(Case sensitive): ");

    for (const auto& t : trainings)
    {
        for (const auto& w : work)
        {
            if (w.id == t.w_id && w.name == chosen_workout_name)
            {
                found = true;
                workids_with_name.push_back(t.w_id);
                break;
            }
        }
    }
    if (!found)
    {
        std::cout << "You have no workouts with this name\n";
    }
    else
    {
        filtered_trainings = trainings;
        for (const auto& t : trainings)
        {
            trid = t.w_id;
            auto ite = std::find(workids_with_name.begin(),
                workids_with_name.end(), trid);
            if (ite == workids_with_name.end())
            {
                filtered_trainings.erase(
                std::remove_if(filtered_trainings.begin(),
                    filtered_trainings.end(), [&trid](Training tr)
                    { return tr.w_id == trid; }),
                filtered_trainings.end());
            }
        }

        // Outputting
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);

    }
    found = false;
    trid = 0;
    filtered_trainings.clear();
    workids_with_name.clear();
}

void filtr_ename(const std::vector<Exercise> &exer)
{
    std::vector<Exercise> tempex;
    std::string chosen_exercise_name;
    bool found = false;
    getInput(chosen_exercise_name, "Enter the exercise name "
        "(Case sensitive): ");
    for (const auto &e : exer)
    {
        if (e.name == chosen_exercise_name)
        {
            found = true;
            tempex.push_back(e);
        }
    }
    if (!found)
    {
        std::cout << "You do not have an exercise with this name" << std::endl;
    }
    else
    {
        std::cout << tempex;
    }
    found = false;
    tempex.clear();
}

void filtr_ediff(const std::vector<Exercise> &exer)
{
    std::vector<Exercise> tempex;
    Difficulty udiff;
    bool found = false;
    std::cin >> udiff;
    for (const auto &e : exer)
    {
        if (e.difficulty == udiff)
        {
            found = true;
            tempex.push_back(e);
        }
    }
    if (!found)
    {
        std::cout << "You do not have exercises with this difficulty" 
                  << std::endl;
    }
    else
    {
        std::cout << tempex;
    }
    found = false;
    tempex.clear();
}

void filtr_wreps(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                std::vector<Training> &trainings)
{
    int32_t trid = 0;
    bool found = false;
    int nof_reps = 0;
    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_reps;
    getInput(nof_reps, "Enter the number of reps in exercise\n");

    for (const auto &t : trainings)
    {
        for (const auto &e : exer)
        {
            if (e.id == t.e_id && e.reps >= nof_reps)
            {
                found = true;
                workids_with_reps.push_back(t.w_id);
                break;
            }
        }
    }
    if (!found)
    {
        std::cout << "You have no exercises with such number of reps\n";
    }
    else
    {
        filtered_trainings = trainings;
        for (const auto &t : trainings)
        {
            trid = t.w_id;
            auto ite = std::find(workids_with_reps.begin(), 
            workids_with_reps.end(), trid);
            if (ite == workids_with_reps.end())
            {
                filtered_trainings.erase(
                std::remove_if(filtered_trainings.begin(), 
                filtered_trainings.end(), [&trid](Training tr)
                { return tr.w_id == trid; }),
                filtered_trainings.end());
            }
        }

        // Outputting
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);

    }
    found = false;
    nof_reps = 0;
    trid = 0;
    filtered_trainings.clear();
    workids_with_reps.clear();
}

void filtr_wsets(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                 std::vector<Training> &trainings)
{
    int32_t trid = 0;
    bool found = false;
    int nof_sets = 0;
    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_sets;
    getInput(nof_sets, "Enter the number of sets in exercise\n");

    for (const auto &t : trainings)
    {
        for (const auto &e : exer)
        {
            if (e.id == t.e_id && e.sets >= nof_sets)
            {
                found = true;
                workids_with_sets.push_back(t.w_id);
                break;
            }
        }
    }
    if (!found)
    {
        std::cout << "You have no exercises with such number of sets\n";
    }
    else
    {
        filtered_trainings = trainings;
        for (const auto &t : trainings)
        {
            trid = t.w_id;
            auto ite = std::find(workids_with_sets.begin(), 
            workids_with_sets.end(), trid);
            if (ite == workids_with_sets.end())
            {
                filtered_trainings.erase(
                std::remove_if(filtered_trainings.begin(), 
                filtered_trainings.end(), [&trid](Training tr)
                { return tr.w_id == trid; }),
                filtered_trainings.end());
            }
        }
        // Outputting
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);

    }
    trid = 0;
    found = false;
    nof_sets = 0;
    filtered_trainings.clear();
    workids_with_sets.clear();
}

void filtr_wexerc(std::vector<Workout> &work, std::vector<Exercise> &exer,
                  std::vector<Training> &trainings)
{
    int32_t trid = 0;
    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_hexer;
    Difficulty udiff{Difficulty::UNKNOWN};

    std::cout << "Workouts with which exercises would you like to filter?\n";
    std::cin >> udiff;

    for (const auto &t : trainings)
    {
        for (const auto &e : exer)
        {
            if (e.id == t.e_id && e.difficulty == udiff)
            {
                workids_with_hexer.push_back(t.w_id);
                break;
            }
        }
    }
    filtered_trainings = trainings;
    for (const auto &t : trainings)
    {
        trid = t.w_id;
        auto ite = std::find(workids_with_hexer.begin(), 
        workids_with_hexer.end(), trid);
        if (ite == workids_with_hexer.end())
        {
            filtered_trainings.erase(
            std::remove_if(filtered_trainings.begin(), 
            filtered_trainings.end(), [&trid](Training tr)
            { return tr.w_id == trid; }),
            filtered_trainings.end());
        }
    }
    // Outputting
    if (!filtered_trainings.empty())
    {   
        sort_id(work, filtered_trainings);
        print_filtr_w(work, exer, filtered_trainings);
        
    }
    else
    {
        std::cout << "You have no such workouts\n";
    }
    trid = 0;
    filtered_trainings.clear();
    workids_with_hexer.clear();
}

void filtr_wsdate(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                  std::vector<Training> &trainings)
{
    int32_t trid = 0;
    std::vector<Training> filtered_trainings;
    std::vector<int32_t> workids_with_gdate;
    std::vector<Workout> work_from_date;
    Date start_date;

    bool found = false;

    std::cout << "Enter the date from which you want to filter workouts\n";
    start_date = getstringdate();

    // Filtering by date - work_from_date  Workouts without exercises
    work_from_date = work;
    // Sort by date
    std::sort(work_from_date.begin(), work_from_date.end(), 
    [](Workout fd, Workout sd)
    { return (fd.date > sd.date); });

    std::cout << std::endl;

    for (const auto &w : work_from_date)
    {
        auto it = std::find(trainings.begin(), trainings.end(), w);
        if (it == trainings.end())
        {
            if (w.date >= start_date && w.completed == true)
            {
                found = true;
                std::cout << "WARNING! THE FOLLOWING WORKOUT HAS NO EXERCISES:"
                 << std::endl << w << std::endl;
            }
        }
    }

    // Filtering be date - Trainings Workouts with exercises
    for (const auto &t : trainings)
    {
        for (const auto &w : work)
        {
            if (w.id == t.w_id && w.date >= start_date 
            && w.completed == true)
            {
                found = true;
                workids_with_gdate.push_back(t.w_id);
                break;
            }
        }
    }
    std::cout << "|======================================================="
    "====================================|" << std::endl;

    filtered_trainings = trainings;
    for (const auto &t : trainings)
    {
        trid = t.w_id;
        auto ite = std::find(workids_with_gdate.begin(), 
        workids_with_gdate.end(), trid);
        if (ite == workids_with_gdate.end())
        {
            filtered_trainings.erase(
            std::remove_if(filtered_trainings.begin(), 
            filtered_trainings.end(), [&trid](Training tr)
            { return tr.w_id == trid; }),
            filtered_trainings.end());
        }
    }
    std::sort(filtered_trainings.begin(), filtered_trainings.end(), 
    [&work](Training fd, Training sd)
                {
            auto iter1 = std::find(work.begin(), work.end(), fd.w_id);
            auto iter2 = std::find(work.begin(), work.end(), sd.w_id);

            return (*iter1 > *iter2); });
    std::cout << std::endl;
    if (found == true)
    {
        // Outputting Workouts with exercises
        print_filtr_w(work, exer, filtered_trainings);
    }
    else
    {
        std::cout << "You do not have workouts after this date\n";
    }
    filtered_trainings.clear();
    workids_with_gdate.clear();
    work_from_date.clear();
}

void changeObject(std::vector<Workout> &work, std::vector<Exercise> &exer, 
                  std::vector<Training> &trainings)
{
    int32_t checkid = 0;
    int32_t changeopt = 0;
    int32_t foundid = 0;

    bool exitcon = false;
    if (!work.empty())
    {
        while (true)
        {
            printWorkouts(work, exer, trainings);
            checkid = getID(work, "Enter the ID of the workout you want"
            " to change (enter [q] to exit): ");
            if (checkid != 0)
            {
                while (true)
                {
                    for (auto &w : work)
                    {
                        if (w.id == checkid)
                        {
                            foundid = w.id;
                            output_byid(w.id, work);

                            std::cout << "What would you like to change?"
                                      << "\n1.Name"
                                      << "\n2.Duration"
                                      << "\n3.Calories burnt"
                                      << "\n4.Difficulty"
                                      << "\n5.Completed status\n";
                            if (w.completed == true)
                            {
                                std::cout << "6.Date\n";
                            }
                            std::cout << "9 - Exit\n";
                            while (true)
                            {
                                getInput(changeopt, "Enter your choice: ");
                                if (changeopt == 9)
                                {
                                    exitcon = true;
                                    break;
                                }
                                if (changeopt == 1 || changeopt == 2 
                                || changeopt == 3 || changeopt == 4 
                                || changeopt == 5)
                                {
                                    break;
                                }
                                else if (changeopt == 6 && w.completed == true)
                                {
                                    break;
                                }
                                else
                                {
                                    if (w.completed == true)
                                    {
                                        std::cerr << color_outpt("Please enter"
                                        " 1, 2, 3, 4, 5 or 6\n");
                                    }
                                    else
                                    {
                                        std::cerr << color_outpt("Please enter"
                                        " 1, 2, 3, 4 or 5\n");
                                    }
                                }
                            }
                            if (changeopt == 1)
                            {
                                getInput(w.name, "Enter the new name: ");
                            }
                            else if (changeopt == 2)
                            {
                                getInput(w.duration, "Enter new duration: ");
                            }
                            else if (changeopt == 3)
                            {
                                getInput(w.calories_burnt, 
                                "Enter calories burnt: ");
                            }
                            else if (changeopt == 4)
                            {
                                std::cin >> w.difficulty;
                            }
                            else if (changeopt == 5)
                            {
                                getstringYesNo(w.completed, "Have you already"
                                " completed this workout?\n1.Yes\n2.No\n");
                                if (w.completed == true)
                                {
                                    w.date = getstringdate();
                                }
                                else if (w.completed == false) {
                                    Date deflt_d;
                                    w.date = deflt_d;
                                }
                            }
                            else if (w.completed == true && changeopt == 6)
                            {
                                w.date = getstringdate();
                            }

                            if (exitcon)
                            {
                                break;
                            }
                            break;
                        }
                    }
                    if (foundid == 0)
                    {
                        break;
                    }
                    if (exitcon)
                    {
                        break;
                    }
                }
            }
            else
            {
                break;
            }
            if (exitcon)
            {
                exitcon = false;
                break;
            }
        }
    }
    else
    {
        std::cout << "You do not have any workouts yet\n";
    }
}

void changeObject(std::vector<Exercise> &exer)
{
    int32_t checkid = 0;
    int32_t changeopt = 0;

    // bool exitfrom_menu = false;

    bool exitcon = false;

    std::cout << exer;
    std::cout << "\nATTENTION: After changing name or difficulty,\nexercise"
        " sorting might change and you will have to sort them again.\n";
    while (true)
    {
        checkid = getID(exer, "Enter the ID of the exercise you want to"
        " change (enter [q] to exit): ");
        if (checkid != 0)
        {
            while (true)
            {
                for (auto &e : exer)
                {
                    if (e.id == checkid)
                    {
                        output_byid(e.id, exer);

                        std::cout << "What would you like to change?"
                                    << "\n1.Name"
                                    << "\n2.Number of sets"
                                    << "\n3.Number of reps"
                                    << "\n4.Difficulty\n";
                        std::cout << "9 - Exit\n";
                        while (true)
                        {
                            getInput(changeopt, "Enter your choice: ");
                            if (changeopt == 9)
                            {
                                exitcon = true;
                                break;
                            }
                            if (changeopt == 1 || changeopt == 2 
                            || changeopt == 3 || changeopt == 4)
                            {
                                break;
                            }
                            else
                            {
                                std::cout << color_outpt("Please enter"
                                " 1, 2, 3 or 4\n");
                            }
                        }
                        if (changeopt == 1)
                        {
                            getInput(e.name, "Enter the new name: ");
                        }
                        else if (changeopt == 2)
                        {
                            getInput(e.sets, "Enter new number of sets: ");
                        }
                        else if (changeopt == 3)
                        {
                            getInput(e.reps, "Enter new number of reps: ");
                        }
                        else if (changeopt == 4)
                        {
                            std::cin >> e.difficulty;
                        }

                        if (exitcon)
                        {
                            break;
                        }
                        break;
                    }
                }
                if (exitcon)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
        if (exitcon)
        {
            exitcon = false;
            break;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// Printing
//////////////////////////////////////////////////////////////////////

void print_filtr_w(std::vector<Workout> &work, 
                   std::vector<Exercise> &exer, 
                   std::vector<Training> &filtered_trainings)
{
    std::vector<Exercise> temp_ex;
    int32_t last_workout_id = -1;
    for (const auto &t : filtered_trainings)
    {
        if (t.w_id != last_workout_id)
        {
            std::cout << temp_ex << std::endl
                        << std::endl;
            temp_ex.clear();
            output_byid(t.w_id, work);
            last_workout_id = t.w_id;
        }
        auto iter = std::find(exer.begin(), exer.end(), t.e_id);
        if (iter != exer.end())
        {
            temp_ex.push_back(*iter);
        }
    }
    if (!temp_ex.empty())
    {
        std::cout << temp_ex << std::endl
                    << std::endl;
    }
    last_workout_id = 0;
    temp_ex.clear();
}

void printWorkouts(std::vector<Workout> &allworkouts,
                   std::vector<Exercise> &allexercises,
                   std::vector<Training> &trainings, const Sortcon sc)
{
    int32_t last_workout_id = -1;
    std::vector<Exercise> temp_ex;
    std::sort(trainings.begin(), trainings.end());
    switch (sc)
    {
    case Sortcon::ALPHA:
        sort_alpha(allworkouts, trainings);
        break;
    case Sortcon::CALOR:
        sort_cal(allworkouts, trainings);
        break;
    case Sortcon::DATE:
        sort_date(allworkouts, trainings);
        break;
    case Sortcon::DIFF:
        sort_diff(allworkouts, trainings);
        break;
    case Sortcon::DURAT:
        sort_dur(allworkouts, trainings);
        break;
    case Sortcon::ID:
        sort_id(allworkouts, trainings);
        break;
    default:
        sort_alpha(allworkouts, trainings);
    }

    for (const auto &w : allworkouts)
    {
        auto it = std::find(trainings.begin(), trainings.end(), w);
        if (it == trainings.end())
        {
            std::cout << "WARNING! THE FOLLOWING WORKOUT HAS NO EXERCISES:"
                      << std::endl
                      << w << std::endl;
        }
    }
    std::cout << "|======================================================="
                 "====================================|"
              << std::endl;
    for (const auto &t : trainings)
    {
        if (t.w_id != last_workout_id)
        {
            std::cout << temp_ex << std::endl
                      << std::endl;
            temp_ex.clear();
            output_byid(t.w_id, allworkouts);
            last_workout_id = t.w_id;
        }
        auto iter = std::find(allexercises.begin(), allexercises.end(), t.e_id);
        if (iter != allexercises.end())
        {
            temp_ex.push_back(*iter);
        }
    }
    if (!temp_ex.empty())
    { // Output the last workout exercises if there are any
        std::cout << temp_ex << std::endl
                  << std::endl;
    }
    temp_ex.clear();
    last_workout_id = -1;
}

void output_byid(const int32_t &id, const std::vector<Workout> &cont)
{
    for (const auto &e : cont)
    {
        if (e.id == id)
        {
            std::cout << e;
            break;
        }
    }
}

void output_byid(const int32_t &id, const std::vector<Exercise> &cont)
{
    std::vector<Exercise> temp_ex;
    for (const auto &e : cont)
    {
        if (e.id == id)
        {
            temp_ex.push_back(e);
        }
    }
    std::cout << temp_ex;
}
