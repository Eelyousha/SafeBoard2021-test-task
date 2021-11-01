#include "directory_scanner.hpp"

using recursive_directory_iterator = filesystem::recursive_directory_iterator;

unsigned DirectoryScanner::get_errors_amount()
{
    return files.get_errors_amount() + jsSuspiciousFiles.get_errors_amount() +
           cmdSuspiciousFiles.get_errors_amount() + exeSuspiciousFiles.get_errors_amount();
}

void DirectoryScanner::extension_checker(const string &path)
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

DirectoryScanner::DirectoryScanner()
{
    runtime = time(0);
}

void DirectoryScanner::scan_directory(const string &path)
{
    for (const auto &dirEntry : recursive_directory_iterator(path))
    {
        if (dirEntry.status().type() == filesystem::file_type::directory)
            continue;
        extension_checker(dirEntry.path());
    }
}

void DirectoryScanner::output_scan_result()
{
    runtime = (time(0) - runtime);
    struct tm *tmr = gmtime(&runtime);
    cout << "\n\n====== Scan result ======"
         << "\n\nProcessed files: " << this->files.get_amount()
         << "\n\nJS detects: " << this->jsSuspiciousFiles.get_amount()
         << "\n\nCMD detects: " << this->cmdSuspiciousFiles.get_amount()
         << "\n\nEXE detects: " << this->exeSuspiciousFiles.get_amount()
         << "\n\nErrors: " << this->get_errors_amount()
         << "\n\nExecution time: " << tmr->tm_hour << ":"
         << tmr->tm_min << ":" << tmr->tm_sec
         << "\n\n=========================\n\n";
}
