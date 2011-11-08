#ifndef AMF3_UNDEFINED_H
#define AMF3_UNDEFINED_H

#include "amf3_type_base.h"

namespace AMF3
{
    class Undefined : public TypeBase<TYPE_UNDEFINED>
    {
    };

    OutStream& operator<<(OutStream& lhs, const Undefined& rhs);
    InStream& operator>>(InStream& lhs, Undefined& rhs);
}

#endif // AMF3_UNDEFINED_H
