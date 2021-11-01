#ifndef SUSPICIOUS_FILE_HPP
#define SUSPICIOUS_FILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include "basic_file.hpp"

using namespace std;

class SuspiciousFile : public BasicFile
{
protected:
    vector<string> susStrings;
    vector<string> extentions;

public:
    SuspiciousFile(BasicFile basicFile, vector<string> susStrings, vector<string> extentions);

    vector<string> get_sus_strings() const;

    vector<string> get_extention() const;

    void operate_file(const string &path);
};

#endif // SUSPICIOUS_FILE_HPP
