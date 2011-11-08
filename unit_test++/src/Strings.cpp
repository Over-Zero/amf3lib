#include "Strings.h"
#include <cstring>
#include <cstdlib>

using namespace UnitTest;

size_t Strings::StrLen(const Char* value)
{
#ifdef _UNICODE
    return wcslen(value);
#else
    return strlen(value);
#endif
}

int Strings::StrCmp(const Char* str1, const Char* str2)
{
#ifdef _UNICODE
    return wcscmp(str1, str2);
#else
    return strcmp(str1, str2);
#endif
}

void Strings::StrCpy(Char* destination, const Char* source)
{
#ifdef _UNICODE
    std::wcscpy(destination, source);
#else
    std::strcpy(destination, source);
#endif
}

const Char* Strings::StrStr(const Char* where, const Char* what)
{
#ifdef _UNICODE
    return std::wcsstr(where, what);
#else
    return std::strstr(where, what);
#endif
}

Char* Strings::StrCat(Char* destination, const Char *source)
{
#ifdef _UNICODE
    return std::wcscat(destination, source);
#else
    return std::strcat(destination, source);
#endif
}

String Strings::Make(const char* value)
{
#ifdef _UNICODE
    String result;
    size_t reserveCount = std::strlen(value);
    result.resize(reserveCount);
    result.resize(std::mbstowcs(const_cast<Char*>(result.data()), value, reserveCount));
    return result;
#else
    return String(value);
#endif
}

std::string Strings::ToMultibyte(const String& value)
{
#ifdef _UNICODE
    std::string result;
    size_t reserveCount = std::wcslen(value.c_str()) * 4;
    result.resize(reserveCount);
    result.resize(std::wcstombs(const_cast<char*>(result.data()), value.c_str(), reserveCount));
    return result;
#else
    return value;
#endif
}
