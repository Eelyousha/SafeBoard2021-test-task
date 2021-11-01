#ifndef JS_SUSPICIOUS_FILE_HPP
#define JS_SUSPICIOUS_FILE_HPP

#include "suspicious_file.hpp"

class JsSuspiciousFiles : public SuspiciousFile
{
public:
    JsSuspiciousFiles() : SuspiciousFile{{0, 0}, {"<script>evil_script()</script>"}, {".js"}} {}
};

#endif // JS_SUSPICIOUS_FILE_HPP
