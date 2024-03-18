#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "utilities.h"
#include "date.h"
#include "workout.h"
#include "exercise.h"
#include "utilities.h"
#include "Training.h"
#include "binaryrw.h"
#include <set>

/**
 * @brief Output starting menu and take the user input.
 *
 * Input is validated.
 * @param logsign Record the option user chooses
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct
 */
void pmenuinput(int &logsign);

//////////////////////////////////////////////////////////////////
// Adding objects
//////////////////////////////////////////////////////////////////
/**
 * @brief Add workouts data.
 *
 * Allows user to choose whether to add completely new workout
 * or duplicate existing one with all its propeties and exercises.
 * @param allworkouts Vector of workouts to add objects to
 * @param allexercises Vector of exercises
 * @param trainings Vector of trainings
 * @param us_id User ID
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct
 * @see void getWorkouts(std::vector<Workout>& work, int32_t& us_id);
 */
void addworkouts(std::vector<Workout> &allworkouts,
				 std::vector<Exercise> &allexercises,
				 std::vector<Training> &trainings, int32_t &us_id);

/**
 * @brief Add exercises to workouts.
 *
 * This is how exercises are added to workouts. The user can choose
 * from all exercises or create new ones right away.
 * @param allexercises Vector of all Exercises
 * @param allworkouts Vector of all Workouts
 * @param trainings
 * @throws std::invalid_argument gets thrown and caught if the user
 * input is not correct
 */
void add_exercises_to_w(std::vector<Exercise> &allexercises,
						const std::vector<Workout> &allworkouts,
						std::vector<Training> &trainings);

//////////////////////////////////////////////////////////////////
// Menus
//////////////////////////////////////////////////////////////////

/**
 * @brief Outputs removing menu with its functionality.
 *
 * Allows the user to delete Workouts/Exercises data or
 * the account.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 * @param sc Sorting condition
 * @param users Vector of Users
 * @param us_id User ID
 */
void removingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
				  std::vector<Training> &trainings, Sortcon &sc,
				  std::vector<User> &users, int32_t &us_id);
/**
 * @brief Outputs Sorting menu with its functionality.
 *
 * Allows the user to sort Workouts/Exercises.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 * @param sc Sorting condition
 */
void sortingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
				 std::vector<Training> &trainings, Sortcon &sc);
/**
 * @brief Outputs filtering menu with its functionality.
 *
 * Allows the user to filter Workouts/Exercises.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filteringmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
				   std::vector<Training> &trainings);
/**
 * @brief Outputs summary menu with its functionality.
 *
 * Allows the user to sum Workouts/Exercises according
 * to different parameters.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void summarymenu(const std::vector<Workout> &work,
				 const std::vector<Exercise> &exer,
				 const std::vector<Training> &trainings);
/**
 * @brief Outputs changing menu with its functionality.
 *
 * Allows the user to change Workouts/Exercises data.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void changingmenu(std::vector<Workout> &work, std::vector<Exercise> &exer,
				  std::vector<Training> &trainings);

//////////////////////////////////////////////////////////////////
// Filtering functons
//////////////////////////////////////////////////////////////////

/**
 * @brief Outputs completed/not-completed workouts.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_compltd(std::vector<Workout> &work, std::vector<Exercise> &exer,
				   std::vector<Training> &trainings);
/**
 * @brief Outputs Workout by ID.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wid(std::vector<Workout> &work, std::vector<Exercise> &exer,
			   std::vector<Training> &trainings);
/**
 * @brief Outputs Exercise by ID.
 *
 * @param exer Vector of Exercises
 */
void filtr_eid(std::vector<Exercise> &exer);
/**
 * @brief Outputs Workouts by name.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wname(std::vector<Workout> &work, std::vector<Exercise> &exer,
				 std::vector<Training> &trainings);
/**
 * @brief Outputs Exercises by name.
 *
 * @param exer Vector of Exercises
 */
void filtr_ename(const std::vector<Exercise> &exer);
/**
 * @brief Outputs Exercises by difficulty.
 *
 * @param exer Vector of Exercises
 */
void filtr_ediff(const std::vector<Exercise> &exer);
/**
 * @brief Outputs Workouts if they haveexercises with more than N
 * number of reps.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wreps(std::vector<Workout> &work, std::vector<Exercise> &exer,
				 std::vector<Training> &trainings);
/**
 * @brief Outputs Workouts if they haveexercises with more than N
 * number of sets.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wsets(std::vector<Workout> &work, std::vector<Exercise> &exer,
				 std::vector<Training> &trainings);
/**
 * @brief Outputs Workouts if they have hard/medium/easy Exercises.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wexerc(std::vector<Workout> &work, std::vector<Exercise> &exer,
				  std::vector<Training> &trainings);
/**
 * @brief Outputs Workouts if they have been completed after the certain date.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void filtr_wsdate(std::vector<Workout> &work, std::vector<Exercise> &exer,
				  std::vector<Training> &trainings);

//////////////////////////////////////////////////////////////////
// Removing functons
//////////////////////////////////////////////////////////////////

/**
 * @brief Outputs Workouts and lets user remove them by ID.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 * @param sc Sorting condition
 */
void removeWorkout(std::vector<Workout> &work, std::vector<Exercise> &exer,
				   std::vector<Training> &trainings, Sortcon &sc);
/**
 * @brief Outputs exercises and lets user remove them by ID.
 *
 * Exercises are also removed from all workouts that have them.
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void removeExercise(std::vector<Exercise> &vector,
					std::vector<Training> &trainings);
/**
 * @brief Outputs Workouts and lets user remove exercises from them by ID.
 *
 * Exercises are removed only form chosen workout.
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 * @param sc Sorting condition
 */
void removeExercisefromWorkout(std::vector<Workout> &work,
							   std::vector<Exercise> &exer,
							   std::vector<Training> &trainings, Sortcon &sc);
/**
 * @brief Outputs Workouts and lets user remove Workouts before certain date.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void removeWorkout_fromdate(std::vector<Workout> &work,
							std::vector<Exercise> &exer,
							std::vector<Training> &trainings);
/**
 * @brief Lets the user delete their account.
 *
 * @param users Vector of all Users
 * @param us_id User's ID
 */
void remove_curruser(std::vector<User> &users, const int32_t &us_id);

//////////////////////////////////////////////////////////////////
// Sorting functions
//////////////////////////////////////////////////////////////////

/**
 * @brief Sorts workouts by date (Newest first).
 *
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 */
void sort_date(std::vector<Workout> &work, std::vector<Training> &trainings);
/**
 * @brief Sorts workouts by calories burnt (Greater first).
 *
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 */
void sort_cal(std::vector<Workout> &work, std::vector<Training> &trainings);
/**
 * @brief Sorts workouts by difficulty (Harder first).
 *
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 */
void sort_diff(std::vector<Workout> &work, std::vector<Training> &trainings);
/**
 * @brief Sorts workouts by duration (Longer first).
 *
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 */
void sort_dur(std::vector<Workout> &work, std::vector<Training> &trainings);
/**
 * @brief Sorts workouts by name alphabetically.
 *
 * Sorts by ID first to avoid problems with workouts that have same names
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 * @see void sort_id(std::vector<Workout>& work, 
 * std::vector<Training> &trainings);
 */
void sort_alpha(std::vector<Workout> &work, std::vector<Training> &trainings);
/**
 * @brief Sorts workouts by ID (lesser first).
 *
 * @param work Vector of Workouts
 * @param trainings Vector of Trainings
 */
void sort_id(std::vector<Workout>& work, std::vector<Training> &trainings);

//////////////////////////////////////////////////////////////////
// Changing functions
//////////////////////////////////////////////////////////////////

/**
 * @brief Outputs Workouts and lets user change data about the Workout.
 *
 * @param work Vector of Workouts
 * @param exer Vector of Exercises
 * @param trainings Vector of Trainings
 */
void changeObject(std::vector<Workout> &work, std::vector<Exercise> &exer,
				  std::vector<Training> &trainings);
/**
 * @brief Outputs Exercises and lets user change data about the Exercise.
 *
 * @param exer Vector of Exercises
 */
void changeObject(std::vector<Exercise> &exer);

//////////////////////////////////////////////////////////////////
// Printing
//////////////////////////////////////////////////////////////////

/**
 * @brief Print out Workouts after filtering.
 *
 * @param work Vector of all workouts
 * @param exer Vector of all exercises
 * @param filtered_trainings Vector of filtered trainings
 * @see void output_byid(int32_t id, std::vector<Workout> &cont);
 * @see output_byid(int32_t id, std::vector<Exercise> &cont);
 */
void print_filtr_w(std::vector<Workout> &work,
				   std::vector<Exercise> &exer,
				   std::vector<Training> &filtered_trainings);
/**
 * @brief Print out Workouts with its exercises according to sorting condition.
 *
 * Sorts workouts alphabetically, if no sorting condition is provided.
 * @param allworkouts Vector of all workouts
 * @param allexercises Vector of all exercises
 * @param trainings Vector of trainings
 * @param sc
 * @see void output_byid(int32_t id, std::vector<Workout> &cont);
 * @see output_byid(int32_t id, std::vector<Exercise> &cont);
 */
void printWorkouts(std::vector<Workout> &allworkouts,
				   std::vector<Exercise> &allexercises,
				   std::vector<Training> &trainings,
				   const Sortcon sc = Sortcon::ALPHA);

/**
 * @brief Output Workout by its ID
 *
 * @param id Workout ID
 * @param cont Vector of Workouts
 */
void output_byid(const int32_t &id, const std::vector<Workout> &cont);
/**
 * @brief Output Exercise by its ID
 *
 * @param id Exercise ID
 * @param cont Vector of Exercises
 */
void output_byid(const int32_t &id, const std::vector<Exercise> &cont);

#endif // !FUNCTIONS_H
