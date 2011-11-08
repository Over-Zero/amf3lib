#ifndef AMF3_TYPE_BASE_IMPL_H
#define AMF3_TYPE_BASE_IMPL_H

#include "amf3_type_base.h"

namespace AMF3
{
    template<TypeMarker TYPE_MARKER>
    void PutMarker(OutStream& stream, const TypeBase<TYPE_MARKER>&)
    {
        stream << static_cast<UInt8>(TYPE_MARKER);
    }

    template<TypeMarker TYPE_MARKER>
    bool GetMarker(InStream& stream, const TypeBase<TYPE_MARKER>&)
    {
        UInt8 byte;
        bool result = GetByte(stream, byte);
        if (result && byte != TYPE_MARKER)
        {
            stream.setstate(std::ios_base::failbit);
            result = false;
        }
        return result;
    }
}

#endif // AMF3_TYPE_BASE_IMPL_H
