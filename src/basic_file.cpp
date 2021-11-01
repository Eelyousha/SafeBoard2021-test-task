#include "basic_file.hpp"

BasicFile::BasicFile(unsigned amount = 0, unsigned errorsAmount = 0) : amount(amount), errorsAmount(errorsAmount) {}

unsigned BasicFile::get_amount() const { return amount; }

unsigned BasicFile::get_errors_amount() const { return errorsAmount; }

void BasicFile::operate_file(const string &path)
{
    ifstream input_file(path);
    if (!input_file.is_open())
    {
        errorsAmount++;
        return;
    }

    amount++;
}
