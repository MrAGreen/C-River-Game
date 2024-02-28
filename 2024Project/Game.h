#pragma once
#include "Rivers.h"

#define ASSIGNMENT_2				//uncomment to switch to assignment 2
//#define RUN_PAUSE_TEST  			//uncomment to run pause test (for assignment 2 only)

class Game {
	Rivers r;

private:
	std::string stringInput = "a";
	std::string river1;
	std::string river2;
	std::vector<std::pair<double, std::string>> fastestTimes;
	double dur = 0;
	int score = 0;
	int total = 0;

public:

	Game(Rivers& rivers) : r(rivers) { }

	std::string getRivers(Rivers& r);

	void userTime(std::ostream& out, std::istream& in);

	void validInput() {
		if (stringInput.length() != 1) {
			stringInput = "a";
		}
	}
	std::string pointScoring(std::string input, bool b);

	void addTime();

	int getScore() {
		return score;
	}
	void incrementScore() {
		++score;
	}
	int getTotal() {
		return total;
	}
	void incrementTotal() {
		++total;
	}
	void reset() {
		score = 0;
		total = 0;
	}

	bool playRound(std::ostream& out, std::istream& in);

	std::vector<std::string> getFastest();
};


