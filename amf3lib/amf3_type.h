#ifndef AMF3_TYPE_H
#define AMF3_TYPE_H

#include "amf3_stream.h"

namespace AMF3
{
    class IType
    {
    public:
        virtual void Serialize(OutStream& stream) = 0;
        virtual void Deserialize(InStream& stream) = 0;
    };
}

#endif // AMF3_TYPE_H
