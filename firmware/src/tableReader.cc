#include "tableReader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace micromouse {

TableReader::TableReader(std::string fpath) : fpath(fpath) {}

std::vector<float>* TableReader::parseTableCSV() {
    std::ifstream csvFile(this->fpath);
    auto table = new std::vector<float>();

    // populate header information
    std::string header;
    std::getline(csvFile, header);
    std::stringstream headerStream(header);
    std::string minValue;
    std::getline(headerStream, minValue, ',');
    this->minValue = std::stoi(minValue);

    while (csvFile) {
        std::string line;
        std::getline(csvFile, line);

        std::stringstream lineStream(line);
        std::string entry;
        while(std::getline(lineStream, entry, ',')) {
            if (entry.empty()) {
                continue;
            }
            table->push_back(std::stof(entry));
        }
    }
    return table;
}

int TableReader::getMinValue() {
    return this->minValue;
}

} // namespace micromouse
