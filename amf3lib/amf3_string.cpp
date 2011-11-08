#include "amf3lib_pch.h"
#include "amf3_string.h"
#include "amf3_uint29.h"
#include "amf3_type_base_impl.h"

namespace AMF3
{
    OutStream& operator<<(OutStream& lhs, const String& rhs)
    {
        PutMarker(lhs, rhs);
        UInt32 size = (rhs.GetString().size() << 1) | 0x01;
        lhs << UInt29(size) << rhs.GetString();
        return lhs;
    }

    InStream& operator>>(InStream& lhs, String& rhs)
    {
        for (;;)
        {
            if (!GetMarker(lhs, rhs))
            {
                break;
            }

            UInt8 byte;
            if (!GetByte(lhs, byte))
            {
                break;
            }

            // References are not supported
            if (!(byte & 0x01))
            {
                lhs.setstate(std::ios_base::failbit);
                break;
            }

            size_t size = byte >> 1;
            // TODO: True unicode not implemented
            for (size_t i = 0; i < size; ++i)
            {
                break;
            }
        }
        return lhs;
    }
}
