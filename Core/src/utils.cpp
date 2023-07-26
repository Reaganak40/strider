#include "utils.h"
#include <fstream>
#include <iostream>

const std::string ReadFile(const std::string& filepath) {
    std::ifstream infile(filepath);

    std::string fileBuffer;
    if (infile.is_open()) { // always check whether the file is open

        while (infile) {
            std::string line;
            std::getline(infile, line);
            fileBuffer += line + '\n';
        }
    }
    else {
        std::cout << "Error: Could not open '" << filepath << "'\n";
    }

    infile.close();
    return fileBuffer;
}