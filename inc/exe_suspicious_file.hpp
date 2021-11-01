#ifndef EXE_SUSPICIOUS_FILE_HPP
#define EXE_SUSPICIOUS_FILE_HPP

#include "suspicious_file.hpp"

class ExeSuspiciousfiles : public SuspiciousFile
{
public:
    ExeSuspiciousfiles() : SuspiciousFile{{0, 0}, {"CreateRemoteThread", "CreateProcess"}, {".exe", ".dll"}} {}
};

#endif // EXE_SUSPICIOUS_FILE_HPP
