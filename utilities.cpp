#include "utilities.h"


std::string color_outpt(const std::string&& s)
{
	std::string cs;
	cs = "\033[1;31m" + s + "\033[0m";
	return cs;
}

std::istream& operator>>(std::istream& is, Difficulty& d) {
	
	std::cout << "Choose the difficulty: \n1.Easy\n2.Medium\n3.Hard\n";
	while (true) {
		int16_t input;

		try
		{
			std::string impstream;
			std::getline(std::cin, impstream);

			std::stringstream ss(impstream);
			ss >> input;
			if (ss.fail() || !ss.eof() || input < 1 || input > 3) {
				throw std::invalid_argument(color_outpt("Invalid input. "
				"Please enter a non - negative integer value from 1 to 3\n"));
			}
			else {
				if (input == 1) {
					d = Difficulty::EASY;
				}
				else if (input == 2) {
					d = Difficulty::MEDIUM;
				}
				else if (input == 3) {
					d = Difficulty::HARD;
				}
				else
					d = Difficulty::UNKNOWN;
				return is;
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what();
		}
		
	}
}

std::ostream& operator<<(std::ostream& os, const Difficulty& c)
{
	switch (c) {
	case Difficulty::EASY:
		os << "Easy";
		break;
	case Difficulty::MEDIUM:
		os << "Medium";
		break;
	case Difficulty::HARD:
		os << "Hard";
		break;
	case Difficulty::UNKNOWN:
		os << "Unknown";
		break;
	default:
		os << "Unknown";
	}

	return os;
}


void getstringYesNo(bool& b, std::string s) {
	int16_t ans{ 0 };
	std::cout << s;
	while (true) {
		std::string input;
		std::getline(std::cin, input);

		std::stringstream ss(input);
		ss >> ans;

		try {
			if (ss.fail() || !ss.eof() || ans < 1 || ans > 2) {
				throw std::invalid_argument(color_outpt("Invalid input. "
				"Please enter 1 or 2\n"));
				continue;
			}
			else {
				if (ans == 1) {
					b = true;
				}
				else if (ans == 2) {
					b = false;
				}
				break;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what();
		}
	}
}
