#ifndef TRAINING_H
#define TRAINING_H

#include "workout.h"
#include "exercise.h"

/**
 * @struct Training
 * @brief Holds relations between workouts and exercises.
 * @param w_id
 * @param e_id
 * @see Workout class
 * @see Exercise class
 */
struct Training {

	/// @brief Workout ID.
	int32_t w_id;
	/// @brief Exercise ID.
	int32_t e_id;
	/**
	 * @brief Default constructor.
	 * Creates a new Training object with w_id and e_id initialized to 0 
	 */
	Training();
	/**
	 * @brief Constructor.
	 * Creates a new Training object.
     * @param w Workout ID.
	 * @param e Exercise ID.
	 */
	Training(int32_t w, int32_t e);
	/**
	 * @brief Equivalence overloading.
	 * @param t Workout object.
	 * @return Whether the ID is qual to the Workout ID.
	 */
	bool operator==(const Workout& t) const;
	/**
	 * @brief Greater-than overloading.
	 * @param other Training object.
	 * @return Whether the Training is greater than other Training.
	 */
	bool operator > (const Training& other) const;
	/**
	 * @brief Less-than overloading.
	 * @param other Training object.
	 * @return Whether the Training is less than other Training.
	 */
	bool operator < (const Training& other) const;

};


#endif // TRAINING_H