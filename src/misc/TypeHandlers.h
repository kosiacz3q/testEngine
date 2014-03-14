#include <sstream>


#ifndef TYPEHANDLERS_
#define TYPEHANDLERS_

#include <string>

double toReal(const char* c);

template <typename T>
static std::string toStr(const T& val)
{
    std::stringstream out;
    out << val;
    return out.str();
}

#endif
