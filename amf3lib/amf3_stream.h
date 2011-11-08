#ifndef AMF3_STREAM_H
#define AMF3_STREAM_H

#include "amf3_defs.h"
#include <iostream>

namespace AMF3
{
    typedef std::basic_istream<char> InStream;
    typedef std::basic_ostream<char> OutStream;

    inline bool GetByte(InStream& stream, UInt8& byte)
    {
        char c;
        stream >> c;
        bool result = !stream.fail() && !stream.eof();
        if (result)
        {
            byte = static_cast<UInt8>(c);
        }
        else
        {
            stream.setstate(std::ios_base::failbit);
        }
        return result;
    }
}

#endif // AMF3_STREAM_H
