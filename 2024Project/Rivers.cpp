#include "Rivers.h"


Rivers::Rivers(const std::vector<std::string>& filenames){
	firstGeneration = true;
	myMode = 2;
	std::mutex mutex;
	std::random_device rd;
	randomGen = std::mt19937_64(rd());
	std::vector<std::string> vec;
	std::vector<std::thread> files;
	for (const auto& f : filenames) {
		std::thread t1(&Rivers::fileRead, this, f, std::ref(mutex));
		files.push_back(std::move(t1));
	}
	for (std::thread& thread : files) {
		thread.join();
	}
}

void Rivers::fileRead(std::string filenames, std::mutex& mutex) {
	std::vector<std::string> vec;
		std::fstream file(filenames);
		if (file.is_open()) {
			std::string cont = filenames.substr(0, filenames.length() - 4);
			std::string r;
			std::vector<std::string> vec;
			while (getline(file, r)) {
				mutex.lock();
				cont[0] = toupper(cont[0]);
				rivers[r] = cont;
				vec.push_back(r);
				mutex.unlock();
		} 
		ContWeight[cont] = vec;		
	}
}

std::discrete_distribution<> Rivers::modeOne() {
	std::vector<double> weights;
	for (auto& i : ContWeight)
	{
		weights.push_back(1);
	}
	std::discrete_distribution<> dis(weights.begin(), weights.end());
	return dis;
}

std::discrete_distribution<> Rivers::modeTwo() {

	std::vector<double> weights;
	for (auto& i : ContWeight)
	{
		weights.push_back(i.second.size());
	}
	std::discrete_distribution<> dis(weights.begin(), weights.end());
	return dis;
}

std::discrete_distribution<> Rivers::modeThree() {
	std::vector<double> weights;
	for (auto& i : ContWeight)
	{
		if (i.first == usedContinent) {
			weights.push_back(50);
		}
		else {
			weights.push_back(50 / ContWeight.size() - 1);
		}
	}
	std::discrete_distribution<> dis(weights.begin(), weights.end());
	return dis;
}

std::string Rivers::newRandomRiver() {

	//declare my distibution
	std::discrete_distribution<> dis;

	switch (myMode) {
	case 1: {
		dis = modeOne();
		break;
	}
	case 2: {
		dis = modeTwo();
		break;
	}
	case 3: {
		//the first generation uses mode 2 so that the river is randomly generated, then we set
		//the mode to three so that it can work.
			if(firstGeneration == true){
				dis = modeTwo();
				break;
			}
			else {
				dis = modeThree();
				break;

			}
		}
	}

	//randomnumber is equal to my distribution with the mersenne twister in it
	rnd = dis(randomGen);
	auto it = ContWeight.begin();
	std::advance(it, rnd);
	// this point it now points to the vector of rivers
	std::uniform_int_distribution<> dist(0, it->second.size() - 1);
	int num = dist(randomGen);
	usedContinent = it->first;
	firstGeneration = false;
	return it->second[num];
}

std::string Rivers::getRandomRiver() {

	//get new river
	std::string randomRiver = newRandomRiver();

	//if the river is in our used river deque then we get another one 
	while (true) {
		auto it = std::find(usedRivers.begin(), usedRivers.end(), randomRiver);
		if (it != usedRivers.end()) {
			// Randomriver found in usedRivers deque
			// i.e. it is a duplicate
			randomRiver = newRandomRiver();
			continue;
		}
		break;
	}
	//code adapted from https://en.cppreference.com/w/cpp/container/deque, 2024
	//if deque is full, pop first item to make space
	if (usedRivers.size() == 6) {
		usedRivers.pop_front();
	}
	//add new river to the deque then return it 
	usedRivers.push_back(randomRiver);
	//end of adapted code
	return randomRiver;
}


bool Rivers::sameContinent(std::string r1, std::string r2) {
	if (getContinent(r1) == "" || (getContinent(r2)) == "" || getContinent(r1) != getContinent(r2)) {
		return false;
	}
	return true;
}

std::string Rivers::getContinent(std::string river) {
	try {
		return rivers[river];
	}
	catch(std::exception ex){
		return "";
	}

};