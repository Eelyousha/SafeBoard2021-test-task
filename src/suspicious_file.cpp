#include "suspicious_file.hpp"

SuspiciousFile::SuspiciousFile(BasicFile basicFile, vector<string> susStrings, vector<string> extentions) : BasicFile{basicFile}
{
    for (const string &str : susStrings)
        this->susStrings.push_back(str);
    for (const string &str : extentions)
        this->extentions.push_back(str);
}

vector<string> SuspiciousFile::get_sus_strings() const { return susStrings; }

vector<string> SuspiciousFile::get_extention() const { return extentions; }

void SuspiciousFile::operate_file(const string &path)
{
    ifstream inputFile(path);
    if (!inputFile.is_open())
    {
        errorsAmount++;
        return;
    }

    string fileContent = string((std::istreambuf_iterator<char>(inputFile)),
                                std::istreambuf_iterator<char>());

    for (const auto &susString : this->susStrings)
        if (fileContent.find(susString) != string::npos)
        {
            amount++;
            break;
        }

    inputFile.close();
}
