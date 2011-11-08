#include "amf3lib_pch.h"
#include "amf3_uint29.h"
#include "binary_utils.h"

//                   (hex) : (binary)
// 0x00000000 - 0x0000007F : 0xxxxxxx
// 0x00000080 - 0x00003FFF : 1xxxxxxx 0xxxxxxx
// 0x00004000 - 0x001FFFFF : 1xxxxxxx 1xxxxxxx 0xxxxxxx
// 0x00200000 - 0x3FFFFFFF : 1xxxxxxx 1xxxxxxx 1xxxxxxx xxxxxxxx
// 0x40000000 - 0xFFFFFFFF : throw range exception

namespace AMF3
{
    bool UInt29::IsValid(UInt32 value)
    {
        return value <= 0x1FFFFFFF;
    }

    OutStream& operator<<(OutStream& lhs, const UInt29& rhs)
    {
        UInt32 value = rhs.GetValue();
        if (value <= 0x0000007F)
        {
            lhs << static_cast<char>(value);
        }
        else if (value <= 0x00003FFF)
        {
            lhs << (char)(B8(10000000) | ((B16(00111111, 10000000) & value) >> 7));
            lhs << (char)(B8(00000000) | ((B16(00000000, 01111111) & value)));
        }
        else if (value <= 0x001FFFFF)
        {
            lhs << (char)(B8(10000000) | ((B24(00011111, 11000000, 00000000) & value) >> 14));
            lhs << (char)(B8(10000000) | ((B24(00000000, 00111111, 10000000) & value) >> 7));
            lhs << (char)(B8(00000000) | ((B24(00000000, 00000000, 01111111) & value)));
        }
        // There is an error in the specification:
        // 0x3FFFFFFF has 30 significant bits, not 29
        else if (value <= 0x1FFFFFFF)
        {
            lhs << (char)(B8(10000000) | ((B32(00011111, 11000000, 00000000, 00000000) & value) >> 22));
            lhs << (char)(B8(10000000) | ((B32(00000000, 00111111, 10000000, 00000000) & value) >> 15));
            lhs << (char)(B8(10000000) | ((B32(00000000, 00000000, 01111111, 00000000) & value) >> 8));
            lhs << (char)(B8(00000000) | ((B32(00000000, 00000000, 00000000, 11111111) & value)));
        }
        else
        {
            throw "Integer is out of range";
        }

        return lhs;
    }

    InStream& operator>>(InStream& lhs, UInt29& rhs)
    {
        unsigned char bytes[4] = {0};
        size_t count = 0;
        char c;
        while (count < 4)
        {
            lhs >> c;
            if (lhs.eof() || lhs.fail())
            {
                lhs.setstate(std::ios_base::failbit);
                return lhs;
            }

            if ((c & B8(10000000)) == 0 || count == 3)
            {
                bytes[count++] = c;
                break;
            }
            else
            {
                bytes[count++] = c & B8(01111111);
            }
        }

        UInt32 value = 0;
        for (size_t i = 0; i < count; ++i)
        {
            value <<= i < 3 ? 7 : 8;
            value |= bytes[i];
        }

        rhs = value;

        return lhs;
    }
}
