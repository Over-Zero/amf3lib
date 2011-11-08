#include "amf3lib_pch.h"
#include "amf3_double.h"
#include "amf3_type_base_impl.h"

using namespace AMF3;

OutStream& AMF3::operator<<(OutStream& lhs, const Double& rhs)
{
    PutMarker(lhs, rhs);

    double value = rhs.GetDouble();
    const UInt8* pValue = reinterpret_cast<const UInt8*>(&value);
    for (size_t i = 0; i < 8; ++i)
    {
        lhs << pValue[7 - i];
    }
    return lhs;
}

InStream& AMF3::operator>>(InStream& lhs, Double& rhs)
{
    if (GetMarker(lhs, rhs))
    {
        UInt8 bytes[8];
        for (size_t i = 0; i < sizeof(bytes); ++i)
        {
            if (!GetByte(lhs, bytes[sizeof(bytes) - 1 - i]))
            {
                return lhs;
            }
        }

        rhs = *reinterpret_cast<double*>(bytes);
    }
    return lhs;
}
