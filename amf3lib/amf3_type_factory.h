#ifndef AMF3_DATUM_FACTORY_H
#define AMF3_DATUM_FACTORY_H

#include "amf3_defs.h"

namespace AMF3
{
    class IType;

    class TypeFactory
    {
    public:
        virtual IType* CreateDatum(TypeMarker type);
    };
}
#endif // AMF3_DATUM_FACTORY_H
