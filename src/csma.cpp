#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    // Check if filename is provided as command-line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfilename>" << std::endl;
        return EXIT_FAILURE;
    }

    // Open the file for reading
    std::ifstream inputFile(argv[1]); // argv[1] contains the filename

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Read and output each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }

    inputFile.close();

    return EXIT_SUCCESS;
}
