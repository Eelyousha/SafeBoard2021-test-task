#ifndef BASIC_FILE_HPP
#define BASIC_FILE_HPP
#include <string>
#include <fstream>

using namespace std;

class BasicFile
{
protected:
    unsigned amount, errorsAmount;

public:
    BasicFile(unsigned amount, unsigned errorsAmount);

    unsigned get_amount() const;

    unsigned get_errors_amount() const;

    void operate_file(const string &path);
};

#endif //BASIC_FILE_HPP
