#ifndef DIRECTORY_SCANNER_HPP
#define DIRECTORY_SCANNER_HPP

#include "basic_file.hpp"
#include "js_suspicious_file.hpp"
#include "cmd_suspicious_file.hpp"
#include "exe_suspicious_file.hpp"

#include <filesystem>
#include <iostream>


class DirectoryScanner
{
private:
    BasicFile files;
    JsSuspiciousFiles jsSuspiciousFiles;
    CmdSuspiciousFiles cmdSuspiciousFiles;
    ExeSuspiciousfiles exeSuspiciousFiles;

    time_t runtime;
    unsigned get_errors_amount();

    void extension_checker(const string &path);

public:
    DirectoryScanner();

    void scan_directory(const string &path);

    void output_scan_result();
};

#endif // DIRECTORY_SCANNER_HPP
