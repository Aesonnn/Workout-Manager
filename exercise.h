#ifndef EXERCISE_H
#define EXERCISE_H
#include "utilities.h"

/**
 * @struct Exercise
 * @brief Represents an exercise with its properties
 * @param exercise_count
 * @param name
 * @param id
 * @param sets
 * @param reps
 * @param difficulty 
 * @see Difficulty enum
 */
struct Exercise {

	/// @brief Number of Exercise objects.
	static int exercise_count;
	/// @brief Name.
	std::string name;
	/// @brief ID.
	int32_t id;
	/// @brief Number of sets.
	int16_t sets;
	/// @brief Number of reps.
	int16_t reps;
	/// @brief enum Difficulty.
	Difficulty difficulty;
	/**
	 * @brief Default constructor.
	 * 
	 * Creates a new Exercise object with id equal to number of objects 
	 * incremented by 1 .
	 * Sets, reps are initialized to 0, difficulty set to UNKNOWN
	 */
	Exercise();
	/**
	 * @brief Constructor.
	 * 
	 * Creates a new Exercise object.
	 * 
	 * @param n Name of exercise.
	 * @param s Number of sets in exercise.
	 * @param r Number of reps in exercise.
	 * @param diff The Exercise difficulty.
	 */
	Exercise(std::string n, int16_t s, int16_t r, Difficulty diff);

	/**
	 * @brief Equivalence overloading.
	 * @param t integer.
	 * @return Whether the Exercise id is qual to the t.
	 */
	bool operator==(const int& t) const;
	/**
	 * @brief Compare Exercise objects by difficulty (which is harder)
	 * @param other Another Exercise object.
	 * @return Whether the Exercise is greater than other Exercise.
	 */
	bool compareByDiff(const Exercise& other) const;
	/**
	 * @brief Compare Exercise objects by name (alphabetically).
	 * @param other Another Exercise object.
	 * @return Whether the Exercise is less than other Exercise.
	 */
	bool compareByName(const Exercise& other) const;


};
/**
 * @brief Overloaded insertion operator to output Exercise object.
 * @param os The output stream to write the Exercise object to.
 * @param e The Exercise object to be output.
 * @return Reference to the output stream after writing the Exercise object.
*/
std::ostream& operator<<(std::ostream& os, const Exercise& e);
/**
 * @brief Overloaded insertion operator to output Exercise vector.
 * @param os The output stream to write the Exercise vector to.
 * @param exvec The Exercise vector to be output.
 * @return Reference to the output stream after writing the Exercise vector.
*/
std::ostream& operator<<(std::ostream& os, const std::vector<Exercise>& exvec);
/**
 * @brief Create and get input for Exercise objects
 * from the user and push them into a vector.
 * @param e Reference to the vector where the Exercise objects will be stored.
*/
void getexercises(std::vector<Exercise>&e);
#endif // !EXERCISE_H

