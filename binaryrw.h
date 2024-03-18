#ifndef BINARYRW_H
#define BINARYRW_H

#include "Training.h"
#include "user.h"
#include <fstream>
#include <filesystem>
#include <cstring>
#include <algorithm>

/**
 * @brief Error class to throw if the file could not be opened.
 */
class FileNotFoundCorrupted
{
};

/**
 * Write a list of exercises into a file according to the format.
 *
 * The format of the file is as follows.
 *
 * File header
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 2 B   | The header field to identify the file is `US` in ASCII |
 * | 0x02   | 3 B   | File format version number is `1.0` in ASCII           |
 * | 0x05   | 8 B   | UNIX timestamp of last modification                    |
 * ---------------------------------------------------------------------------
 *
 * US records for individual users
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 1 B   | Size of the user in bytes                              |
 * | 0x01   | 4 B   | ID                                                     |
 * | 0x05   | 2 B   | Age                                                    |
 * | 0x07   | 1 B   | Size of the name in bytes SN                           |
 * | ....   | SN B  | Name                                                   |
 * | ....   | 1 B   | Size of the usernamename in bytes SN                   |
 * | ....   | SUN B | Username                                               |
 * | ....   | 1 B   | Size of the password in bytes SN                       |
 * | ....   | SUN B | Password                                               |
 * ---------------------------------------------------------------------------
 *
 * @param users   The Vector of all users.
 *
 * @exception FileNotFoundCorrupted Failure to write to the file.
 * check if it is possible to write to current directory.
 */
void write_users(std::vector<User> &users);
/**
 * @brief Read users from file and store them in a vector.
 * @return std::vector<User>  The vector of all users.
 * @exception FileNotFoundCorrupted. Could not open the file. 
 * Your data has been either corrupted or deleted,
 */
std::vector<User> read_users();

/**
 * @brief Save all user data.
 * 
 * Calls 3 functions for saving Workouts, Exercises, Trainings.
 * 
 * Catches the exceptions thrown by these functions.
 * 
 * @param exs Vector of exercises to write
 * @param works Vector of workouts to write
 * @param trs Vector of trainings to write
 * @param us_id User ID
 * @see write_exs(std::string &fname, 
 * const std::vector<Exercise> &exs, int32_t &us_id)
 * @see write_workouts(std::string &fname, 
 * std::vector<Workout> &works, int32_t &us_id)
 * @see write_trainings(std::string &fname, 
 * std::vector<Training> &trs, int32_t &us_id)
 */
void save_data(const std::vector<Exercise> &exs, 
               std::vector<Workout> &works,
               const std::vector<Training> &trs, int32_t &us_id);
/**
 * @brief Read all user data
 * 
 * Calls 3 functions for reading Workouts, Exercises, Trainings.
 * 
 * Catches the exceptions thrown by these functions.
 * 
 * @param allexercises Vector of exercises to read
 * @param works Vector of workouts to read
 * @param trs Vector of trainings to read
 * @param us_id User ID
 * @see read_exs(const std::string &fname, int32_t &us_id)
 * @see read_workouts(const std::string &fname, int32_t &us_id)
 * @see read_trainings(const std::string &fname, int32_t &us_id);
 */
void read_data(std::vector<Exercise> &allexercises,
               std::vector<Workout> &works, std::vector<Training> &trs,
               int32_t &us_id);
/**
 * Write a list of exercises into a file according to the format.
 *
 * The format of the file is as follows.
 *
 * File header
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 2 B   | The header field to identify the file is `EX` in ASCII |
 * | 0x02   | 3 B   | File format version number is `1.0` in ASCII           |
 * | 0x05   | 8 B   | UNIX timestamp of last modification                    |
 * ---------------------------------------------------------------------------
 *
 * EX records for individual exercises
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 1 B   | Size of the exercise in bytes                          |
 * | 0x01   | 4 B   | Exercise id                                            |
 * | 0x05   | 2 B   | Number of sets                                         |
 * | 0x07   | 2 B   | Number of reps                                         |
 * | 0x09   | 1 B   | Size of the name in bytes SN                           |
 * | ....   | SN B  | Name                                                   |
 * | ....   | 4 B   | Difficulty                                             |
 * ---------------------------------------------------------------------------
 *
 * @param fname   Directory where to write the file.
 * @param exs     The list of exercises.
 * @param us_id   User id.
 *
 * @exception FileNotFoundCorrupted Failure to write to the file.
 * check if it is possible to write to current directory.
 */
void write_exs(const std::string &fname, const std::vector<Exercise> &exs, 
int32_t &us_id);
/**
 * @brief Read Exercises from file and store them in a vector.
 * 
 * @param fname File address from which to read
 * @param us_id User ID
 * @exception FileNotFoundCorrupted. Could not open the file. 
 * @return std::vector<Exercise> The vector of all Exercises.
 */
std::vector<Exercise> read_exs(const std::string &fname, int32_t &us_id);

/**
 * Write a list of workouts into a file according to the format.
 *
 * The format of the file is as follows.
 *
 * File header
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 2 B   | The header field to identify the file is `WK` in ASCII |
 * | 0x02   | 3 B   | File format version number is `1.0` in ASCII           |
 * | 0x05   | 8 B   | UNIX timestamp of last modification                    |
 * ---------------------------------------------------------------------------
 *
 * WK records for individual workouts
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 1 B   | Size of the exercise in bytes                          |
 * | 0x01   | 4 B   | User ID                                                |
 * | 0x05   | 4 B   | ID                                                     |
 * | 0x09   | 6 B   | Date                                                   |
 * | 0x0F   | 2 B   | Duration                                               |
 * | 0x11   | 1 B   | Completed                                              |
 * | 0x12   | 2 B   | Calories burnt                                         |
 * | 0x14   | 4 B   | Difficulty                                             |
 * | 0x19   | 1 B   | Size of the name in bytes SN                           |
 * | 0x16   | SN B  | Name                                                   |
 * ---------------------------------------------------------------------------
 *
 * @param fname   Directory where to write the file.
 * @param works   The list of workouts.
 * @param us_id   User id.
 *
 * @exception FileNotFoundCorrupted Failure to write to the file.
 * check if it is possible to write to current directory.
 */
void write_workouts(const std::string& fname, std::vector<Workout> &works, 
int32_t &us_id);
/**
 * @brief Read Workouts from file and store them in a vector.
 * 
 * @param fname File address from which to read
 * @param us_id User ID
 * @exception FileNotFoundCorrupted. Could not open the file. 
 * @return std::vector<Workout> The vector of all Workouts.
 */
std::vector<Workout> read_workouts(const std::string &fname, int32_t &us_id);
/**
 * Write a list of trainings into a file according to the format.
 *
 * The format of the file is as follows.
 *
 * File header
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 2 B   | The header field to identify the file is `TR` in ASCII |
 * | 0x02   | 3 B   | File format version number is `1.0` in ASCII           |
 * | 0x05   | 8 B   | UNIX timestamp of last modification                    |
 * ---------------------------------------------------------------------------
 *
 * TR records for individual workouts
 * ---------------------------------------------------------------------------
 * | Offset | Size  | Purpose                                                |
 * ---------------------------------------------------------------------------
 * | 0x00   | 1 B   | Size of the training in bytes                          |
 * | 0x01   | 4 B   | Workout ID                                             |
 * | 0x05   | 4 B   | Exercise ID                                            |
 * ---------------------------------------------------------------------------
 *
 * @param fname   Directory where to write the file.
 * @param trs     The list of trainigs.
 * @param us_id   User id.
 *
 * @exception FileNotFoundCorrupted Failure to write to the file.
 * check if it is possible to write to current directory.
 */
void write_trainings(const std::string &fname, const std::vector<Training> &trs, 
int32_t &us_id);
/**
 * @brief Read Trainings from file and store them in a vector.
 * 
 * @param fname File address from which to read
 * @param us_id User ID
 * @exception FileNotFoundCorrupted. Could not open the file. 
 * @return std::vector<Training> The vector of all Trainings.
 */
std::vector<Training> read_trainings(const std::string &fname, int32_t &us_id);

#endif // !BINARYRW_H
