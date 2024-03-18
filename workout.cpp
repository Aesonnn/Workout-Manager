#include "workout.h"
#include <vector>

bool Workout::operator==(const int& t) const
{
	return id == t;
}

bool Workout::operator > (const Workout& w) const
{
	return date > w.date;
}

bool Workout::operator < (const Workout& w) const
{
	return date < w.date;
}

bool Workout::compareByCal(const Workout& other) const
{
	return calories_burnt > other.calories_burnt;
}

bool Workout::compareByDiff(const Workout& other) const
{
	return difficulty > other.difficulty;
}

bool Workout::compareByDurat(const Workout& other) const
{
	return duration > other.duration;
}

bool Workout::compareByName(const Workout& other) const
{
	return name < other.name;
}

std::ostream& operator<<(std::ostream& os, const Workout& w) {

	fort::char_table table;

	table.set_border_style(FT_BASIC2_STYLE);
	table << fort::header
		<< "Workout name" << "ID" << "Duration (min)" << "Calories burnt" 
		<< "Difficulty" << "Status" << fort::endr;

	table << w.name << w.id << w.duration << w.calories_burnt << w.difficulty;
	if (w.completed) {
		table << "Completed" << w.date;
	}
	else {
		table << "Not yet completed" << "";
		table[1][5].set_cell_span(2);

	}


	table.row(0).set_cell_content_fg_color(fort::color::light_blue);
	table[0][5].set_cell_span(2);


	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::center);
	table.column(2).set_cell_text_align(fort::text_align::center);
	table.column(3).set_cell_text_align(fort::text_align::center);
	table.column(4).set_cell_text_align(fort::text_align::center);
	table.column(5).set_cell_text_align(fort::text_align::center);

	os << table.to_string();
	return os;

}

std::ostream& operator<<(std::ostream & os, const std::vector<Workout>& work) {

	fort::char_table table;

	table.set_border_style(FT_BASIC2_STYLE);
	table << fort::header
		<< "Workout name" << "ID" << "Duration" << "Calories burnt" 
		<< "Difficulty" << "Status" << fort::endr;
	for (const auto& w : work) {
		table << w.name << w.id << w.duration << w.calories_burnt 
		<< w.difficulty;
		if (w.completed) {
			table << "Completed" << w.date;
		}
		else {
			table << "Not yet completed" << "";
			table[1][5].set_cell_span(2);

		}
	}

	table.row(0).set_cell_content_fg_color(fort::color::light_blue);
	table[0][5].set_cell_span(2);


	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::center);
	table.column(2).set_cell_text_align(fort::text_align::center);
	table.column(3).set_cell_text_align(fort::text_align::center);
	table.column(4).set_cell_text_align(fort::text_align::center);
	table.column(5).set_cell_text_align(fort::text_align::center);

	os << table.to_string();
	return os;
}

int Workout::workout_count = 0;

Workout::Workout()
{
	++workout_count;
	name = " ";
	duration = 0;
	completed = 0;
	calories_burnt = 0;
	difficulty = Difficulty::UNKNOWN;

}

Workout::Workout(int32_t us_id)
{
	user_id = us_id;
	duration = 0;
	completed = 0;
	calories_burnt = 0;
	difficulty = Difficulty::UNKNOWN;
	id = ++workout_count;
}


void getWorkouts(std::vector<Workout>& work, int32_t& us_id)
{

	while (true)
	{
		std::cout << "Enter data about the workout \n";
		//while (true) {}
		Workout workout(us_id);
		getInput(workout.name, "Name: ");
		workout.id = Workout::workout_count;
		getInput(workout.duration, "Duration (minutes): ");
		getstringYesNo(workout.completed, "Have you already completed this"
		" workout?\n1.Yes\n2.No\n");
		if (workout.completed == true) {
			workout.date = getstringdate();
		}
		getInput(workout.calories_burnt, "How many calories does this workout "
		"burn: ");
		std::cin >> workout.difficulty;
		work.push_back(workout);
		bool anotherw = true;
		getstringYesNo(anotherw, "The workout has been successfully added!"
		"\nDo you wish to add another one?\n1.Yes\n2.No\n");

		if (anotherw != true) {
			break;
		}
	}
}
