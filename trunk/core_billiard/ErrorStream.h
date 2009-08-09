#pragma once
namespace my_phys_x {

class ErrorStream : public NxUserOutputStream
{
public:
    void reportError(NxErrorCode e, const char* message, const char* file, int line)
    {}

    NxAssertResponse reportAssertViolation(const char* message, const char* file, int line);

    void print(const char* message)
    {}
};

}