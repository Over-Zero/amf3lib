#ifndef UNITTEST_STRINGS_H
#define UNITTEST_STRINGS_H

#include <string>

namespace UnitTest {

#define UNITTEST_CONCATENATE(a, b) a ## b

#ifdef _UNICODE
#define UNITTEST_TEXT(STRING_LITERAL) UNITTEST_CONCATENATE(L, STRING_LITERAL)
    typedef wchar_t Char;
#else
#define UNITTEST_TEXT(STRING_LITERAL) STRING_LITERAL
    typedef char Char;
#endif

    typedef std::basic_string<Char> String;

    class Strings
    {
    public:
        static size_t StrLen(const Char* value);
        static int StrCmp(const Char* str1, const Char* str2);
        static void StrCpy(Char* destination, const Char* source);
        static const Char* StrStr(const Char* where, const Char* what);
        static Char* StrCat(Char* destination, const Char *source);

        static String Make(const char* value);
        static std::string ToMultibyte(const String& value);
    };

}

#endif
