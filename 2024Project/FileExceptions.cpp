#include "Rivers.h"


class FileException : public std::exception {

    const std::vector<std::string>& filenames;

public:

    FileException(const std::vector<std::string>& filenames) : filenames(filenames)
    {
        for (const auto& filename : filenames) {
            if (!std::filesystem::exists(filename)) {
                std::cerr << "the file " << filename << " has not been found" << std::endl;
                exit(EXIT_FAILURE);
            }   
            if (std::filesystem::is_empty(filename)) {
                std::cerr << "the file " << filename << " is empty" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
};