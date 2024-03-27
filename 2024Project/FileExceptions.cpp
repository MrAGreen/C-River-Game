#include "Rivers.h"

//https://en.cppreference.com/w/cpp/filesystem/exists

/**
 * @class FileException
 * @brief Custom exception for file-related errors.
 *
 * This exception is thrown when there are issues with files, such as missing files or empty files.
 */

class FileException : public std::exception {

    const std::vector<std::string>& filenames;///< Vector of filenames causing the exception.

public:
    /**
     * @brief Constructor for FileException.
     * @param filenames A vector of filenames that caused the exception.
     *
     * The constructor checks each filename in the vector:
     * - If the file does not exist, it prints an error message and exits.
     * - If the file is empty, it prints an error message and exits.
     *
     * @note The adapted code is based on https://en.cppreference.com/w/cpp/filesystem/exists.
     *
     * @param filenames A vector of filenames to check.
     */
    FileException(const std::vector<std::string>& filenames) : filenames(filenames)
    {
        for (const auto& filename : filenames) {
            //code adapted from https://en.cppreference.com/w/cpp/filesystem/exists, 2024
            if (!std::filesystem::exists(filename)) {
                std::cerr << "the file " << filename << " has not been found" << std::endl;
                exit(EXIT_FAILURE);
            }   
            if (std::filesystem::is_empty(filename)) {
                std::cerr << "the file " << filename << " is empty" << std::endl;
                exit(EXIT_FAILURE);
            }
            //end of adapted code
        }
    }
};