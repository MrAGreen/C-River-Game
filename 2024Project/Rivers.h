#pragma once
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <fstream>
#include <iostream>
#include <ostream>
#include <iterator>
#include <tuple>
#include <thread>
#include <mutex>
#include <boost/thread.hpp>
#include <chrono>

class Rivers {

private:

	std::map<std::string, std::string> rivers;
	std::map<std::string, std::vector<std::string>> ContWeight;
	std::deque<std::string> usedRivers{};
	std::string usedContinent;
	std::mt19937_64 randomGen;
	int myMode;
	int contCount;
	int rnd;

public:

	Rivers(const std::vector<std::string>& filenames);

	void fileRead(std::string filenames, std::mutex& mutex);

	std::discrete_distribution<> modeOne();

	std::discrete_distribution<> modeTwo();

	std::discrete_distribution<> modeThree();

	std::string newRandomRiver();

	std::string getRandomRiver();

	bool sameContinent(std::string river1, std::string river2);

	//trie data structure
	std::string getContinent(std::string river);

	void setMode(int mode) {
		myMode = mode;
	}

};
