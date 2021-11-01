#ifndef CMD_SUSPICIOUS_FILE_HPP
#define CMD_SUSPICIOUS_FILE_HPP

#include "suspicious_file.hpp"

class CmdSuspiciousFiles : public SuspiciousFile
{
public:
    CmdSuspiciousFiles() : SuspiciousFile{{0, 0}, {"<rd /s /q \"c:\\windows\""}, {".cmd", ".bat"}} {}
};

#endif // CMD_SUSPICIOUS_FILE_HPP
