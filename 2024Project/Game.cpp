//Game.cpp

#include "Game.h"

//get 2 rivers and returns them to the user
std::string Game::getRivers(Rivers& r) {
	river1 = r.getRandomRiver();
	river2 = r.getRandomRiver();
	return river1 + "\n" + river2 + "\n";
}

//takes in user input with the chrono before and after so we can store the duration
void Game::userTime(std::ostream& out, std::istream& in) {
	auto start = std::chrono::high_resolution_clock::now();
	in >> stringInput;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	dur = duration.count();
}

//this functions takes in the input and a bool (true = same continent etc)
std::string Game::pointScoring(std::string input, bool b) {
	if (dur >= 10000) {
		return "Incorrect: time limit exceeded";
	}
	if (input == "d" && b == false) {
		//if the answers are correct we add the time to my fastestAnswers
		addTime();
		return "correct: " + river1 + " is in " + r.getContinent(river1) + " and " + river2 + " is in " + r.getContinent(river2);
	}
	if (input == "d" && b == true) {
		return  "incorrect: " + river1 + " and " + river2 + " are both in " + r.getContinent(river1);
	}
	if (input == "s" && b == true) {
		//if the answers are correct we add the time to my fastestAnswers
		addTime();
		return "correct: " + river1 + " and " + river2 + " are both in " + r.getContinent(river1);
	}
	if (input == "s" && b == false) {
		return "incorrect: " + river1 + " is in " + r.getContinent(river1) + " and " + river2 + " is in " + r.getContinent(river2);
	}
	return "";
}
//we put the rivers and duration in the time together so that we can return fastestTimes.first in the getFastest()
void Game::addTime() {
	fastestTimes.push_back(std::make_pair(dur, river1 + "," + river2 + "," + std::to_string(dur)));
	incrementScore();
}

//playround has been cleaned up and uses all the other functions 
bool Game::playRound(std::ostream& out, std::istream& in) {
	//out the random rivers
	out << getRivers(r);
	//get user input and duration it took 
	userTime(out, in);
	//check if the input was valid
	validInput();
	if (stringInput == "d" || stringInput == "s") {
		// check if the user scores a point and return correct/false
		out << pointScoring(stringInput, r.sameContinent(river1, river2));
	}
	else {
		out << "Incorrect input, the program will now end";
		return false;
	}

	// if they enter q the playround ends and then the getfastest method returns from mikes code
	if (stringInput == "q") {
		return false;
	}

	//increment the total at the end so that if they enter an answer that is either valid or invalid it
	//will still increase the total
	incrementTotal();
	//return true so that the program loops infinetly if they want to keep answering questions
	return true;
}

//created a sorting algorithm that just checks through x vs y and sorts them in non ascending order
bool SortDuration(std::pair<double, std::string> x, std::pair<double, std::string> y)
{
	return x.first < y.first;
}

//get fastest method has a vector of strings, sorts them with the above method and then adds them to the vector
//then we resize the vector to 5 long and present the user with those.
std::vector<std::string> Game::getFastest() {
	std::vector<std::string> topFive;
	std::sort(fastestTimes.begin(), fastestTimes.end(), SortDuration);
	for (const auto& time : fastestTimes) {
		std::string sentenceBuilder = time.second;
		topFive.push_back(sentenceBuilder);
	}
	if (topFive.size() > 5) {
		topFive.resize(5);
	}
	return topFive;
};