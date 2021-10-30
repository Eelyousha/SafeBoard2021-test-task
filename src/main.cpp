#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>

using namespace std;

class BasicFile
{
protected:
    unsigned amount, errorsAmount;

public:
    BasicFile(unsigned amount = 0, unsigned errorsAmount = 0) : amount(amount), errorsAmount(errorsAmount) {}
    unsigned get_amount() const { return amount; }
    unsigned get_errors_amount() const { return errorsAmount; }
};

class SuspiciousFile : public BasicFile
{
protected:
    vector<string> susStrings;
    vector<string> extentions;

public:
    SuspiciousFile(BasicFile basicFile, vector<string> susStrings, vector<string> extentions) : BasicFile{basicFile}
    {
        for (const string &str : susStrings)
            this->susStrings.push_back(str);
        for (const string &str : extentions)
            this->extentions.push_back(str);
    }
    vector<string> get_sus_strings() const { return susStrings; }
    vector<string> get_extention() const { return extentions; }
};

class JsSuspiciousFiles : public SuspiciousFile
{
public:
    JsSuspiciousFiles() : SuspiciousFile{{0, 0}, {"<script>evil_script()</script>"}, {".js"}} {}
};

class CmdSuspiciousFiles : public SuspiciousFile
{
public:
    CmdSuspiciousFiles() : SuspiciousFile{{0, 0}, {"<rd /s /q \"c:\\windows\""}, {".cmd", ".bat"}} {}
};

class ExeSuspiciousfiles : public SuspiciousFile
{
public:
    ExeSuspiciousfiles() : SuspiciousFile{{0, 0}, {"CreateRemoteThread", "CreateProcess"}, {".exe", ".dll"}} {}
};

class DirectoryScanner
{
private:
    BasicFile files;
    JsSuspiciousFiles jsSuspiciousFiles;
    CmdSuspiciousFiles cmdSuspiciousFiles;
    ExeSuspiciousfiles exeSuspiciousFiles;
    chrono::duration<double> execTime;
    unsigned get_errors_amount();

public:
    DirectoryScanner() {}
    friend void output_scan_result(DirectoryScanner scan);
};

unsigned DirectoryScanner::get_errors_amount()
{
    return files.get_errors_amount() + jsSuspiciousFiles.get_errors_amount() +
           cmdSuspiciousFiles.get_errors_amount() + exeSuspiciousFiles.get_errors_amount();
}

void output_scan_result(DirectoryScanner scan)
{
    cout << "\n\n====== Scan result ======"
         << "\n\nProcessed files: " << scan.files.get_amount()
         << "\n\nJS detects: " << scan.jsSuspiciousFiles.get_amount()
         << "\n\nCMD detects: " << scan.cmdSuspiciousFiles.get_amount()
         << "\n\nEXE detects: " << scan.exeSuspiciousFiles.get_amount()
         << "\n\nErrors: " << scan.get_errors_amount()
         << "\n\nExecution time: " << scan.execTime.count()
         << "\n\n=========================\n\n";
}

int main(int argc, char **argv)
{
    DirectoryScanner scanner;
    output_scan_result(scanner);
    return EXIT_SUCCESS;
}
