#include "amf3lib_pch.h"
#include "amf3_boolean.h"

using namespace AMF3;

namespace AMF3
{
    OutStream& operator<<(OutStream& lhs, const Boolean& rhs)
    {
        lhs << static_cast<UInt8>(rhs.GetBoolean() ? TYPE_TRUE : TYPE_FALSE);
        return lhs;
    }

    InStream& operator>>(InStream& lhs, Boolean& rhs)
    {
        UInt8 byte;
        if (!GetByte(lhs, byte) || (byte != TYPE_TRUE && byte != TYPE_FALSE))
        {
            lhs.setstate(std::ios_base::failbit);
        }
        else
        {
            rhs = Boolean(byte == TYPE_TRUE);
        }
        return lhs;
    }
}
