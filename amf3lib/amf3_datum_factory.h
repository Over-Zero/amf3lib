#ifndef AMF3_DATUM_FACTORY_H
#define AMF3_DATUM_FACTORY_H

#include "amf3_type.h"

namespace AMF3
{
    class IDatum;

    class TypeFactory
    {
    public:
        virtual IDatum* CreateDatum(Type type);
    };
}
#endif // AMF3_DATUM_FACTORY_H
