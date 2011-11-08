#include "amf3lib_pch.h"
#include "amf3_integer.h"
#include "amf3_uint29.h"

using namespace AMF3;

OutStream& AMF3::operator<<(OutStream& lhs, const Integer& rhs)
{
    if (UInt29::IsValid(rhs.GetInteger()))
    {
        lhs << UInt29(rhs.GetInteger());
    }
    else
    {
        throw "Not implemented";
    }
    return lhs;
}
