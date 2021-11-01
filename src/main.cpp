#include "directory_scanner.hpp"

using namespace std;



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
