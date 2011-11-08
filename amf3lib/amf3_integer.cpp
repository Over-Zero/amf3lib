#include "amf3lib_pch.h"
#include "amf3_integer.h"
#include "amf3_uint29.h"
#include "amf3_type_base_impl.h"

using namespace AMF3;

OutStream& AMF3::operator<<(OutStream& lhs, const Integer& rhs)
{
    PutMarker(lhs, rhs);
    lhs << UInt29(rhs.GetInteger());
    return lhs;
}

InStream& AMF3::operator>>(InStream& lhs, Integer& rhs)
{
    if (GetMarker(lhs, rhs))
    {
        UInt29 result;
        lhs >> result;
        if (!lhs.fail())
        {
            rhs = result.GetValue();
        }
    }

    return lhs;
}
