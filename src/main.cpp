#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>
#include <ctime>

using namespace std;

using recursive_directory_iterator = filesystem::recursive_directory_iterator;

class BasicFile
{
protected:
    unsigned amount, errorsAmount;

public:
    BasicFile(unsigned amount = 0, unsigned errorsAmount = 0) : amount(amount), errorsAmount(errorsAmount) {}

    unsigned get_amount() const { return amount; }

    unsigned get_errors_amount() const { return errorsAmount; }

    void operate_file(const string &path)
    {
        ifstream input_file(path);
        if (!input_file.is_open())
        {
            errorsAmount++;
            return;
        }

        amount++;
    }
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

    void operate_file(const string &path)
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

    clock_t runtime;
    unsigned get_errors_amount()
    {
        return files.get_errors_amount() + jsSuspiciousFiles.get_errors_amount() +
               cmdSuspiciousFiles.get_errors_amount() + exeSuspiciousFiles.get_errors_amount();
    }

    void extension_checker(const string &path)
    {
        for (const string &ext : jsSuspiciousFiles.get_extention())
            if (path.rfind(ext) == path.rfind("."))
                jsSuspiciousFiles.operate_file(path);

        for (const string &ext : cmdSuspiciousFiles.get_extention())
            if (path.rfind(ext) == path.rfind("."))
                cmdSuspiciousFiles.operate_file(path);

        for (const string &ext : exeSuspiciousFiles.get_extention())
            if (path.rfind(ext) == path.rfind("."))
                exeSuspiciousFiles.operate_file(path);

        files.operate_file(path);
    }

public:
    DirectoryScanner()
    {
        runtime = clock();
    }

    void scan_directory(const string &path)
    {
        for (const auto &dirEntry : recursive_directory_iterator(path))
        {
            if (dirEntry.status().type() == filesystem::file_type::directory)
                continue;
            extension_checker(dirEntry.path());
        }
    }

    void output_scan_result()
    {
        runtime = (clock() - runtime) / CLOCKS_PER_SEC;
        clock_t hours = runtime / 3600;
        clock_t minutes = (runtime / 60) % 60;
        clock_t seconds = runtime % 60;
        cout << "\n\n====== Scan result ======"
             << "\n\nProcessed files: " << this->files.get_amount()
             << "\n\nJS detects: " << this->jsSuspiciousFiles.get_amount()
             << "\n\nCMD detects: " << this->cmdSuspiciousFiles.get_amount()
             << "\n\nEXE detects: " << this->exeSuspiciousFiles.get_amount()
             << "\n\nErrors: " << this->get_errors_amount()
             << "\n\nExecution time: " << hours << ":"
             << minutes << ":"
             << seconds
             << "\n\n=========================\n\n"
             << runtime;
    }
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        throw std::runtime_error("Incorrect args amount");
    }

    DirectoryScanner scanner;
    scanner.scan_directory(argv[1]);
    scanner.output_scan_result();
    return EXIT_SUCCESS;
}
