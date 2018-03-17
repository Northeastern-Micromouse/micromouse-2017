#ifndef _MM_TABLEREADER_
#define _MM_TABLEREADER_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace micromouse {

class TableReader {
 public:
    TableReader(std::string fpath);
    std::vector<float>* parseTableCSV();
    int getMinValue();
 private:
    std::string fpath;
    int minValue;
};

}
#endif
