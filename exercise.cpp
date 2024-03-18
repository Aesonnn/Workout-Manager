#include "exercise.h"
#include <vector>
#include "fort.hpp"
#include "fort.c"


Exercise::Exercise(std::string n, int16_t s, int16_t r, Difficulty diff)
	: name{ n }, sets{ s }, reps{ r }, difficulty{ diff } {
		id = ++Exercise::exercise_count;
	}

bool Exercise::operator==(const int &t) const
{
	return id == t;
}

bool Exercise::compareByDiff(const Exercise& other) const
{
	return difficulty > other.difficulty;
}

bool Exercise::compareByName(const Exercise& other) const
{
	return name < other.name;
}

int Exercise::exercise_count = 0;


Exercise::Exercise()
{
	exercise_count++;
	id = exercise_count;
	sets = 0;
	reps = 0;
	difficulty = Difficulty::UNKNOWN;
}

std::ostream& operator<<(std::ostream& os, const Exercise& e)
{
	fort::char_table table;

	table.set_border_style(FT_DOT_STYLE);
	table << fort::header
		<< "Exercise name" << "ID" << "Sets" << "Reps" << "Difficulty" 
		<< fort::endr;
	table << e.name << e.id << e.sets << e.reps << e.difficulty << fort::endr;
	table.row(0).set_cell_content_fg_color(fort::color::light_yellow);


	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::center);
	table.column(2).set_cell_text_align(fort::text_align::center);
	table.column(3).set_cell_text_align(fort::text_align::center);
	table.column(4).set_cell_text_align(fort::text_align::center);
	os << table.to_string();
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Exercise>& exvec)
{
	if (!exvec.empty()) {

		fort::char_table table;

		table.set_border_style(FT_DOT_STYLE);
		table << fort::header
			<< "Exercise name" << "ID" << "Sets" << "Reps" << "Difficulty" 
			<< fort::endr;
		for (const auto& e : exvec) {
			table << e.name << e.id << e.sets << e.reps << e.difficulty 
			<< fort::endr;
		}

		table.row(0).set_cell_content_fg_color(fort::color::light_yellow);


		table.column(0).set_cell_text_align(fort::text_align::center);
		table.column(1).set_cell_text_align(fort::text_align::center);
		table.column(2).set_cell_text_align(fort::text_align::center);
		table.column(3).set_cell_text_align(fort::text_align::center);
		table.column(4).set_cell_text_align(fort::text_align::center);
		os << table.to_string();
	}
	return os;
}

void getexercises(std::vector<Exercise>& e)
{
	while (true)
	{
		std::cout << "Enter data about the exercise \n";
		//while (true) {}
		Exercise ex;
		getInput(ex.name, "Name: ");
		ex.id = Exercise::exercise_count;
		getInput(ex.sets, "Number of sets: ");
		getInput(ex.reps, "Number of reps per set: ");


		std::cin >> ex.difficulty;

		e.push_back(ex);
		bool anotherw = true;
		std::cout << "The exercise has been successfully added!(ID: " 
			      << ex.id << ")";
		getstringYesNo(anotherw, "\nDo you wish to add another one?"
		"\n1.Yes\n2.No\n");

		if (anotherw != true) {
			break;
		}
	}
}
