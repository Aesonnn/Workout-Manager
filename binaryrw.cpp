#include "binaryrw.h"


void write_users(std::vector<User>& users)
{   

    std::string folder_name = "usercredentials";
    std::filesystem::create_directory(folder_name);

    std::string fname = folder_name + "/allusers.us";
    std:: ofstream ofs{ fname, std::ios::binary };
    try
    {
        if (!ofs)
            throw FileNotFoundCorrupted();
        ofs.write("US", 2);
        ofs.write("1.0", 3);
        size_t nus = (users.size()<(1 << 16)) ? users.size() : (1 << (16 - 1));
        time_t now = time(nullptr);
        ofs.write(reinterpret_cast<char*>(&now), 8);

        for (unsigned i = 0; i < nus; ++i) {
            const size_t name_size = users[i].name.size();
            const size_t username_size = users[i].get_username().size();
            const size_t passsword_size = users[i].get_password().size();
            const size_t us_size = 10 + name_size + username_size 
            + passsword_size;

            ofs.write(reinterpret_cast<const char*>(&us_size), 1);

            int32_t user_id = users[i].get_id();
            ofs.write(reinterpret_cast<const char*>(&user_id), 4);


            ofs.write(reinterpret_cast<const char*>(&users[i].age), 2);
            ofs.write(reinterpret_cast<const char*>(&name_size), 1);
            ofs.write(users[i].name.c_str(), name_size);

            ofs.write(reinterpret_cast<const char*>(&username_size), 1);
            ofs.write(users[i].get_username().c_str(), username_size);
            ofs.write(reinterpret_cast<const char*>(&passsword_size), 1);
            ofs.write(users[i].get_password().c_str(), passsword_size);

        }
        ofs.close();

    }
    catch (FileNotFoundCorrupted)
    {
        std::cerr << "\033[1;31mFailure to write to the file, check if it "
        "is possible to write to current directory\n\033[0m";
    }
}

std::vector<User> read_users()
{
    std::string folder_name = "usercredentials";
    std::string fname = folder_name + "/allusers.us";

    std::ifstream ifs{ fname, std::ios::binary };
    std::vector<int32_t> user_ids;
    std::vector<User> uss;
    if (ifs) {
        char header[5];
        ifs.read(header, 5);
        try
        {
            if (strncmp(header, "US", 2) != 0 
                || strncmp(header + 2, "1.0", 3) != 0)
                throw FileNotFoundCorrupted();

            time_t file_timestamp;
            ifs.read(reinterpret_cast<char*>(&file_timestamp), 8);

            while (ifs) {
                uint8_t tx_size;
                ifs.read(reinterpret_cast<char*>(&tx_size), 1);
                if (!ifs || tx_size < 10)
                    break;

                User user;
                int32_t us_id;
                ifs.read(reinterpret_cast<char*>(&us_id), 4);
                user.set_id(us_id);
                // Store ids to later find the greatest
                user_ids.push_back(us_id);


                ifs.read(reinterpret_cast<char*>(&user.age), 2);


                uint8_t name_size, username_size, passsword_size;
                ifs.read(reinterpret_cast<char*>(&name_size), 1);
                user.name.resize(name_size);
                ifs.read(&user.name[0], name_size);

                ifs.read(reinterpret_cast<char*>(&username_size), 1);
                std::string temp_usname;
                temp_usname.resize(username_size);
                ifs.read(&temp_usname[0], username_size);
                user.set_username(temp_usname);

                ifs.read(reinterpret_cast<char*>(&passsword_size), 1);
                std::string temp_pass;
                temp_pass.resize(passsword_size);
                ifs.read(&temp_pass[0], passsword_size);
                user.set_password(temp_pass);

                uss.push_back(user);
            }
            if (!user_ids.empty()) {
                User::user_count = *std::max_element(user_ids.begin(), 
                user_ids.end());
            }
            user_ids.clear();

        }
        catch (FileNotFoundCorrupted)
        {
            std::cerr << "\033[1;31mCould not open the file. Your data "
            "has been either corrupted or deleted.\n\033[0m";
        }
    }
    else {
        std::cout << "ATTENTON:\n"
            "If this is the first time you run this program then everything "
            "is in order.\n"
            "If not, it means your data has either been deleted or corrupted"
            " and you will have to add it again.\n"
            "To ensure correct functioning and avoid potential loss of data,\n"
            "please do not tamper with the files in any way.\n\n";
    }

    return uss;
}



void save_data(const std::vector<Exercise>& exs, 
               std::vector<Workout>& works, 
               const std::vector<Training>& trs, int32_t& us_id)
{
	std::string folder_name = "data_user" + std::to_string(us_id);
	std::filesystem::create_directory(folder_name);

	std::string general_path = folder_name + "/";

    try
    {
	    write_exs(general_path, exs, us_id);
        write_workouts(general_path, works, us_id);
        write_trainings(general_path, trs, us_id);
        std::cout << "Saved!\n";
    }
    catch (FileNotFoundCorrupted)
    {
        std::cerr << "\033[1;31mFailure to write to the file, check if it "
            "is possible to write to current directory\n\033[0m";
    }
}

void read_data(std::vector<Exercise>& allexercises, std::vector<Workout>& works, 
               std::vector<Training>& trs, int32_t& us_id)
{
	std::string folder_name = "data_user" + std::to_string(us_id);
	std::string general_path = folder_name + "/";
    try
    {
	    allexercises = read_exs(general_path, us_id);
        works = read_workouts(general_path, us_id);
	    trs = read_trainings(general_path, us_id);
    }
    catch (FileNotFoundCorrupted)
    {
        std::cerr << "\033[1;31mCRITICAL ERROR: "
            "Could not open the file.\nYour data might"
            " have been either corrupted or deleted.\n"
            "Your data may not be displayed correctly!\n\033[0m";
    }
}

void write_exs(const std::string& fname, const std::vector<Exercise>& exs, 
               int32_t& us_id)
{   
    std::string full_path = fname + "exerdata_" + std::to_string(us_id) +".ex";
	std::ofstream ofs{ full_path, std::ios::binary };

    if (!ofs) {
        throw FileNotFoundCorrupted();
    }

	ofs.write("EX", 2);
	ofs.write("1.0", 3);
	size_t nts = (exs.size() < (1 << 16)) ? exs.size() : (1 << (16 - 1));
	time_t now = time(nullptr);
	ofs.write(reinterpret_cast<char*>(&now), 8);

	for (unsigned i = 0; i < nts; ++i) {
		const size_t name_size = exs[i].name.size();
		const size_t tx_size = 14 + name_size;

		ofs.write(reinterpret_cast<const char*>(&tx_size), 1);
		ofs.write(reinterpret_cast<const char*>(&exs[i].id), 4);
		ofs.write(reinterpret_cast<const char*>(&exs[i].sets), 2);
		ofs.write(reinterpret_cast<const char*>(&exs[i].reps), 2);
		ofs.write(reinterpret_cast<const char*>(&name_size), 1);
		ofs.write(exs[i].name.c_str(), name_size);
		// Write difficulty cast enum to int first
		int32_t diff_castedint = static_cast<int32_t>(exs[i].difficulty);
		ofs.write(reinterpret_cast<char*>(&diff_castedint), 4);

	}
    ofs.close();

}

std::vector<Exercise> read_exs(const std::string& fname, int32_t& us_id){
    std::string full_path = fname + "exerdata_" + std::to_string(us_id) +".ex";

    std::ifstream ifs{ full_path, std::ios::binary };
    std::vector<Exercise> txs;
    std::vector<int32_t> ex_ids;
    if (!ifs) {
        throw FileNotFoundCorrupted();
    }

    char header[5];
    ifs.read(header, 5);
    if (strncmp(header, "EX", 2) != 0 || strncmp(header + 2, "1.0", 3) != 0) {
        throw FileNotFoundCorrupted();
    }


    time_t file_timestamp;
    ifs.read(reinterpret_cast<char*>(&file_timestamp), 8);

    while (ifs) {
        uint8_t tx_size;
        ifs.read(reinterpret_cast<char*>(&tx_size), 1);
        if (!ifs || tx_size < 14)
            break;

        Exercise tx;
        ifs.read(reinterpret_cast<char*>(&tx.id), 4);
        ex_ids.push_back(tx.id);

        ifs.read(reinterpret_cast<char*>(&tx.sets), 2);
        ifs.read(reinterpret_cast<char*>(&tx.reps), 2);

        uint8_t name_size;
        ifs.read(reinterpret_cast<char*>(&name_size), 1);
        tx.name.resize(name_size);
        ifs.read(&tx.name[0], name_size);

        int32_t a;
        ifs.read(reinterpret_cast<char*>(&a), 4);
        tx.difficulty = static_cast<Difficulty>(a);

        txs.push_back(tx);
    }
    if (!ex_ids.empty()) {
        Exercise::exercise_count = *std::max_element(ex_ids.begin(),
            ex_ids.end());
    }
    ex_ids.clear();

    return txs;
}

void write_workouts(const std::string& fname, std::vector<Workout>& works, 
                    int32_t& us_id) 
{

	std::string full_path = fname + "workoutdata_" + 
                            std::to_string(us_id) + ".wk";
	std::ofstream ofs{ full_path, std::ios::binary };

    if (!ofs) {
        throw FileNotFoundCorrupted();
    }

	ofs.write("WK", 2);
	ofs.write("1.0", 3);
	size_t wks = (works.size()<(1 << 16)) ? works.size() : (1 << (16 - 1));
	time_t now = time(nullptr);
	ofs.write(reinterpret_cast<char*>(&now), 8);

	for (unsigned i = 0; i < wks; ++i) {
		const size_t name_size = works[i].name.size();
		const size_t wk_size = 25 + name_size;

		ofs.write(reinterpret_cast<const char*>(&wk_size), 1);
		ofs.write(reinterpret_cast<const char*>(&works[i].user_id), 4);
		ofs.write(reinterpret_cast<const char*>(&works[i].id), 4);

		// Writing date
		ofs.write(reinterpret_cast<char*>(&(works[i].date)), 6);

		ofs.write(reinterpret_cast<const char*>(&works[i].duration), 2);
        ofs.write(reinterpret_cast<const char*>(&works[i].completed), 1);
		ofs.write(reinterpret_cast<const char*>(&works[i].calories_burnt), 
        2);

		// Write difficulty cast enum to int first
		int32_t diff_castedint = static_cast<int32_t>(works[i].difficulty);
		ofs.write(reinterpret_cast<char*>(&diff_castedint), 4);

		ofs.write(reinterpret_cast<const char*>(&name_size), 1);
		ofs.write(works[i].name.c_str(), name_size);

	}
    ofs.close();

}

std::vector<Workout> read_workouts(const std::string& fname, int32_t& us_id)
{
    std::string full_path = fname + "workoutdata_" + 
                            std::to_string(us_id) + ".wk";

    std::ifstream ifs{ full_path, std::ios::binary };
    std::vector<Workout> works;
    std::vector<int32_t> wk_ids;
     if (!ifs) {
        throw FileNotFoundCorrupted();
     }

    char header[5];
    ifs.read(header, 5);
    if (strncmp(header, "WK", 2) != 0 || strncmp(header + 2,"1.0", 3) != 0)
    {
        throw FileNotFoundCorrupted();
    }

    time_t file_timestamp;
    ifs.read(reinterpret_cast<char*>(&file_timestamp), 8);

    while (ifs) {
        uint8_t wk_size;
        ifs.read(reinterpret_cast<char*>(&wk_size), 1);
        if (!ifs || wk_size < 25)
            break;

        Workout w;
        ifs.read(reinterpret_cast<char*>(&w.user_id), 4);
        if (w.user_id != us_id) {
            std::cerr << "\033[1;31mCRITICAL ERROR: The data belongs"
                " to other user.\nLooks like your files have been"
                " replaced with the files of the other user and your data"
                " has been lost.\n"
                "You will have to delete them.\n\033[0m";
            exit(0);
        }
        ifs.read(reinterpret_cast<char*>(&w.id), 4);
        wk_ids.push_back(w.id);
        ifs.read(reinterpret_cast<char*>(&w.date), 6);

        ifs.read(reinterpret_cast<char*>(&w.duration), 2);
        ifs.read(reinterpret_cast<char*>(&w.completed), 1);
        ifs.read(reinterpret_cast<char*>(&w.calories_burnt), 2);

        int32_t a;
        ifs.read(reinterpret_cast<char*>(&a), 4);
        w.difficulty = static_cast<Difficulty>(a);

        uint8_t name_size;
        ifs.read(reinterpret_cast<char*>(&name_size), 1);
        w.name.resize(name_size);
        ifs.read(&w.name[0], name_size);


        works.push_back(w);
    }
    if (!wk_ids.empty()) {
        Workout::workout_count = *std::max_element(wk_ids.begin(),
            wk_ids.end());
    }
    wk_ids.clear();

    return works;
}

void write_trainings(const std::string& fname, 
                     const std::vector<Training>& trs, 
                     int32_t& us_id)
{
	std::string full_path = fname + "trsdata_" + std::to_string(us_id) + ".tr";
	std::ofstream ofs{ full_path, std::ios::binary };

    if (!ofs) {
        throw FileNotFoundCorrupted();
    }

	ofs.write("TR", 2);
	ofs.write("1.0", 3);
	size_t ntr = (trs.size() < (1 << 16)) ? trs.size() : (1 << (16 - 1));
	time_t now = time(nullptr);
	ofs.write(reinterpret_cast<char*>(&now), 8);

	for (unsigned i = 0; i < ntr; ++i) {
		const size_t tr_size = 9;
		ofs.write(reinterpret_cast<const char*>(&tr_size), 1);
		ofs.write(reinterpret_cast<const char*>(&trs[i].w_id), 4);
		ofs.write(reinterpret_cast<const char*>(&trs[i].e_id), 4);
	}
    ofs.close();

}

std::vector<Training> read_trainings(const std::string& fname, int32_t& us_id)
{
    std::string full_path = fname + "trsdata_" + std::to_string(us_id) + ".tr";

    std::ifstream ifs{ full_path, std::ios::binary };
    std::vector<Training> ts;

    if (!ifs) {
        throw FileNotFoundCorrupted();
    }

    char header[5];
    ifs.read(header, 5);
    if (strncmp(header, "TR", 2) != 0 || strncmp(header + 2, "1.0", 3) != 0) {
        throw FileNotFoundCorrupted();
    }

    time_t file_timestamp;
    ifs.read(reinterpret_cast<char*>(&file_timestamp), 8);

    while (ifs) {
        uint8_t tr_size;
        ifs.read(reinterpret_cast<char*>(&tr_size), 1);
        if (!ifs || tr_size < 9)
            break;

        Training tr;
        ifs.read(reinterpret_cast<char*>(&tr.w_id), 4);
        ifs.read(reinterpret_cast<char*>(&tr.e_id), 4);
        ts.push_back(tr);
    }
    return ts;
}

