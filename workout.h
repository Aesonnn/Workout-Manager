#ifndef WORKOUT_H
#define WORKOUT_H

#include "date.h"
#include "utilities.h"
#include <cstdint>
#include <string>
#include <vector>

/**
 * @struct Exercise
 * @brief Represents a workout with its properties.
 * @param workout_count
 * @param user_id
 * @param name
 * @param id
 * @param date
 * @param duration
 * @param completed
 * @param calories_burnt
 * @param difficulty
 * @see Difficulty enum
 * @see Date class
 */
struct Workout {

	/// @brief Number of Workout objects.
	static int workout_count;
	/// @brief ID of the user who has this workout.
	int32_t user_id;
	/// @brief Name.
	std::string name;
	/// @brief ID.
	int32_t id;
	/// @brief Date.
	Date date;
	/// @brief Duration.
	int16_t duration;
	/// @brief Status - completed or not.
	bool completed;
	/// @brief Number of calories the workout burns.
	int16_t calories_burnt;
	/// @brief enum Difficulty.
	Difficulty difficulty;
	/**
	 * @brief Default constructor.
	 * 
	 * Creates a new Workout object with id equal to number of objects 
	 * incremented by 1.
	 * 
	 * Duration, completed and calories_burnt are initialized to 0, 
	 * difficulty set to UNKNOWN.
	 */
	Workout();
	/**
	 * @brief Constructor.
	 * 
	 * Creates a new Workout object with id equal to number of objects 
	 * incremented by 1.
	 * Duration, completed and calories_burnt are initialized to 0, 
	 * difficulty set to UNKNOWN
	 * user_id is set to the id of the current user.
	 */
	Workout(int32_t us_id);
	/**
	 * @brief Equivalence overloading.
	 * @param t integer.
	 * @return Whether the Workout id is qual to the t.
	 */
	bool operator == (const int& t) const;
	/**
	 * @brief Greater-than overloading.
	 * @param other Another Workout object.
	 * @return Whether the Workout id is qual to the t.
	 */
	bool operator > (const Workout& w) const;
	/**
	 * @brief Less-than overloading.
	 * @param other Another Workout object.
	 * @return Whether the Workout is less than other Workout.
	 */
	bool operator < (const Workout& w) const;
	/**
	 * @brief Compare Workoutse objects by calories burnt (which burns more).
	 * @param other Another Workout object.
	 * @return Whether the Workout is greater than other Workout.
	 */
	bool compareByCal(const Workout& other) const;
	/**
	 * @brief Compare Workoutse objects by difficulty (which is harder).
	 * @param other Another Workout object.
	 * @return Whether the Workout is greater than other Workout.
	 */
	bool compareByDiff(const Workout& other) const;
	/**
	 * @brief Compare Workoutse objects by duration (which is longer)
	 * @param other Another Workout object.
	 * @return Whether the Workout is greater than other Workout.
	 */
	bool compareByDurat(const Workout& other) const;
	/**
	 * @brief Compare Workoutse objects by name (alphabetically).
	 * @param other Another Workout object.
	 * @return Whether the Workout is greater than other Workout.
	 */
	bool compareByName(const Workout& other) const;


};
/**
 * @brief Overloaded insertion operator to output Workout object.
 * @param os The output stream to write the Workout object to.
 * @param w The Workout object to be output.
 * @return Reference to the output stream after writing the Workout object.
*/
std::ostream& operator<<(std::ostream& os, const Workout& w);
/**
 * @brief Overloaded insertion operator to output Workout vector.
 * @param os The output stream to write the Workout vector to.
 * @param work The Workout vector to be output.
 * @return Reference to the output stream after writing the Workout vector.
*/
std::ostream& operator<<(std::ostream& os, const std::vector<Workout>& work);
/**
 * @brief Create and get input for Workout objects.
 * from the user and push them into a vector.
 * @param w Reference to the vector where the Workout objects will be stored.
 * @param us_id Current user's id
*/
void getWorkouts(std::vector<Workout>& w, int32_t& us_id);
#endif // !WORKOUT_H
