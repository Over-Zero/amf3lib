#include "amf3lib_pch.h"
#include "amf3_undefined.h"
#include "amf3_type_base_impl.h"

using namespace AMF3;

namespace AMF3
{
    OutStream& operator<<(OutStream& lhs, const Undefined& rhs)
    {
        PutMarker(lhs, rhs);
        return lhs;
    }

    InStream& operator>>(InStream& lhs, Undefined& rhs)
    {
        GetMarker(lhs, rhs);
        return lhs;
    }
}
