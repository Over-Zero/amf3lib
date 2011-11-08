#ifndef AMF3_NULL_H
#define AMF3_NULL_H

#include "amf3_type_base.h"

namespace AMF3
{
    class Null : public TypeBase<TYPE_NULL>
    {
    };

    OutStream& operator<<(OutStream& lhs, const Null& rhs);
    InStream& operator>>(InStream& lhs, Null& rhs);
}

#endif // AMF3_NULL_H
