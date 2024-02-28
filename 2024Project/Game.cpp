#include "Game.h"

std::string Game::getRivers(Rivers& r) {
	river1 = r.getRandomRiver();
	river2 = r.getRandomRiver();
	return river1 + "\n" + river2 + "\n";
}
void Game::userTime(std::ostream& out, std::istream& in) {
	auto start = std::chrono::high_resolution_clock::now();
	in >> stringInput;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	dur = duration.count();
}

std::string Game::pointScoring(std::string input, bool b) {
	if (dur >= 10000) {
		return "Incorrect: time limit exceeded";
	}
	if (input == "d" && b == false) {
		addTime();
		return "correct: " + river1 + " is in " + r.getContinent(river1) + " and " + river2 + " is in " + r.getContinent(river2);
	}
	if (input == "d" && b == true) {
		return  "incorrect: " + river1 + " and " + river2 + " are both in " + r.getContinent(river1);
	}
	if (input == "s" && b == true) {
		addTime();
		return "correct: " + river1 + " and " + river2 + " are both in " + r.getContinent(river1);
	}
	if (input == "s" && b == false) {
		return "incorrect: " + river1 + " is in " + r.getContinent(river1) + " and " + river2 + " is in " + r.getContinent(river2);
	}
	return "";
}
// could do this without a map but the map lets it automatically sort the duration as the key is the duration
void Game::addTime() {
	fastestTimes.push_back(std::make_pair(dur, river1 + "," + river2 + "," + std::to_string(dur)));
	incrementScore();
}
bool Game::playRound(std::ostream& out, std::istream& in) {
	out << getRivers(r);
	userTime(out, in);
	validInput();
	if (stringInput == "d" || stringInput == "s") {
		out << pointScoring(stringInput, r.sameContinent(river1, river2));
	}
	if (stringInput == "q") {
		return false;
	}
	incrementTotal();
	return true;


}

// turn this sorting algorithmn into a template.

bool SortDuration(std::pair<double, std::string> x, std::pair<double, std::string> y)
{
	return x.first < y.first;
}

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
}
