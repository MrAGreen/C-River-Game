#pragma once
#include "Rivers.h"

#define ASSIGNMENT_2				//uncomment to switch to assignment 2
#define RUN_PAUSE_TEST  			//uncomment to run pause test (for assignment 2 only)

/**
 * @brief Game class for managing river trivia gameplay.
 *
 * This class represents the game state and logic for a river trivia game.
 * It interacts with a `Rivers` object for river data access and manages user input,
 * round execution, scoring, and fastest time tracking.
 */
class Game {
private:
	/**
	 * Reference to a Rivers object for accessing river data.
	 */
	Rivers r;

	/**
	 * Temporary string to store user input.
	 */
	std::string stringInput = "a";

	/**
	 * String to store the name of the first river in a round.
	 */
	std::string river1;

	/**
	 * String to store the name of the second river in a round.
	 */
	std::string river2;

	/**
	 * Vector to store information about the fastest rounds (time and formatted string).
	 */
	std::vector<std::pair<double, std::string>> fastestTimes;

	/**
	 * Double to store the time taken by the user in a round (in milliseconds).
	 */
	double dur = 0;

	/**
	 * Integer to track the player's score.
	 */
	int score = 0;

	/**
	 * Integer to track the total number of questions played.
	 */
	int total = 0;

public:
	/**
	 * Constructor for the Game class, taking a reference to a Rivers object.
	 *
	 * @param rivers Reference to a Rivers object providing river data access.
	 * Time Complexity: O(1) - Constant time.
	 */
	Game(Rivers& rivers) : r(rivers) {}
	/**
	 * @brief Retrieves two random rivers and formats them for display.
	 *
	 * This function gets two random rivers from the provided Rivers object,
	 * stores their names in separate variables for potential future use,
	 * and combines them into a formatted string with newlines for display to the user.
	 *
	 * @param r Reference to a Rivers object
	 * @return A string containing the names of the two random rivers, separated by newlines
	 * Time Complexity: O(1) - Constant time.
	 */
	std::string getRivers(Rivers& r);
	/**
	 * @brief Measures user input time and stores it in milliseconds.
	 *
	 * This function precisely measures the time it takes for the user to provide input
	 * using the high-resolution clock and converts the duration to milliseconds for storage.
	 *
	 * @param out Reference to an output stream for potential prompts or messages
	 * @param in Reference to an input stream for receiving user input
	 * Time Complexity: O(1) - Constant time.
	 */
	void userTime(std::ostream& out, std::istream& in);
	/**
	 * @brief Validates user input to ensure it's a single character.
	 *
	 * This function validates the user's input stored in `stringInput`. If it's not
	 * a single character (length not equal to 1), it resets `stringInput` to a default
	 * value of "a" to ensure consistent processing in subsequent steps.
	 * Time Complexity: O(1) - Constant time 
	 */
	void validInput() {
		if (stringInput.length() != 1) {
			stringInput = "a";
		}
	}
	/**
	 * @brief Provides feedback and scoring based on user input, game mode, and time limit.
	 *
	 * This function evaluates the user's input (`input`), a boolean flag (`b`) indicating
	 * the game mode (true for same continent, false for different continents), and the
	 * measured time (`dur`). It provides feedback messages accordingly:
	 *
	 * - **Time Limit Exceeded:** If the time taken (`dur`) exceeds 10 seconds (10000 milliseconds),
	 *   it returns an "Incorrect: time limit exceeded" message.
	 * - **Correct Answers:**
	   - If the user input (`input`) is "d" (different) and the rivers are indeed from
		 different continents (`b` is false), it adds the time to `fastestTimes` using `addTime`
		 and returns a success message with the continent information for both rivers.
	   - If the user input (`input`) is "s" (same) and the rivers are from the same continent
		 (`b` is true), it adds the time to `fastestTimes` using `addTime` and returns a success
		 message with the shared continent information.
	 * - **Incorrect Answers:**
	   - If the user input (`input`) is "d" (different) but the rivers are from the same continent
		 (`b` is true), it returns an incorrect message with the shared continent information.
	   - If the user input (`input`) is "s" (same) but the rivers are from different continents
		 (`b` is false), it returns an incorrect message with the continent information for both rivers.
	 *
	 * @param input User's input string ("d" for different, "s" for same)
	 * @param b Boolean flag indicating game mode (true: same continent, false: different continents)
	 * @return A string containing feedback and scoring information
	 * Time Complexity: O(n) - Linear time
	 */
	std::string pointScoring(std::string input, bool b);
	/**
	 * @brief Records a successful round's time and increments the score.
	 *
	 * This function stores the current round's information (duration, rivers, and time
	 * as a string) in the `fastestTimes` vector, paired with the measured duration for
	 * quick sorting and retrieval. It also calls `incrementScore()` to increase the
	 * player's score.
	 * Time Complexity: O(1) - Constant time 
	 */
	void addTime();

	/**
	 * @brief Retrieves the current score.
	 *
	 * @return The current score value
	 * Time Complexity: O(1) - Constant time 
	 */
	int getScore() const { return score; }

	/**
	 * @brief Increments the current score by 1.
	 * Time Complexity: O(1) - Constant time 
	 */
	void incrementScore() { ++score; }

	/**
	 * @brief Retrieves the total number of questions played.
	 *
	 * @return The total number of questions played
	 * Time Complexity: O(1) - Constant time 
	 */
	int getTotal() const { return total; }

	/**
	 * @brief Increments the total number of questions played by 1.
	 * Time Complexity: O(1) - Constant time 
	 */
	void incrementTotal() { ++total; }

	/**
	 * @brief Resets the score and total questions to 0.
	 * Time Complexity: O(1) - Constant time 
	 */
	void reset() {
		score = 0;  // Reset score
		total = 0;  // Reset total questions

	}
	/**
	 * @brief Manages a single round of the game, handling user input, feedback, scoring, and termination.
	 *
	 * This function orchestrates a single round of the river trivia game, incorporating
	 * various other functions for input, validation, scoring, and timing. It also handles
	 * termination based on user input.
	 *
	 * @param out Reference to an output stream for displaying prompts and messages
	 * @param in Reference to an input stream for receiving user input
	 * @return True if the round was played successfully, false if the user entered "q" to quit
	 * Time Complexity: O(n) - Linear time
	 */
	bool playRound(std::ostream& out, std::istream& in);
	/**
	 * @brief Retrieves and formats the top 5 fastest round scores.
	 *
	 * This function retrieves the top 5 fastest rounds from the `fastestTimes` vector,
	 * which stores pairs of time and river information for successful rounds. It performs:
	 * 1. Sorts the `fastestTimes` vector in ascending order of time using `SortDuration`.
	 * 2. Iterates through the sorted vector and extracts the second element of each pair,
	 *    which contains formatted information about the rivers and time for that round.
	 * 3. Stores those formatted strings in a new vector `topFive`.
	 * 4. Resizes `topFive` to a maximum of 5 elements to ensure only the top 5 scores are returned.
	 * 5. Returns the `topFive` vector containing strings representing the top 5 fastest rounds.
	 *
	 * @return A vector of strings, each containing formatted information about a top round (rivers and time)
	 * Time Complexity: O(n log n) - Log-linear time.
	 */
	std::vector<std::string> getFastest();
};