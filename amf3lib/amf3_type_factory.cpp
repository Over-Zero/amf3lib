#include "amf3lib_pch.h"
#include "amf3_type_factory.h"
#include "amf3_undefined.h"

using namespace AMF3;

IType* TypeFactory::CreateDatum(TypeMarker type)
{
    IType* pResult = 0;
    switch (type)
    {
    case TYPE_UNDEFINED:
        pResult = new Undefined;
        break;

            //TYPE_UNDEFINED = 0x00,
            //TYPE_NULL = 0x01,
            //TYPE_FALSE = 0x02,
            //TYPE_TRUE = 0x03,
            //TYPE_INTEGER = 0x04,
            //TYPE_DOUBLE = 0x05,
            //TYPE_STRING = 0x06,
            //TYPE_XML_DOC = 0x07,
            //TYPE_DATE = 0x08,
            //TYPE_ARRAY = 0x09,
            //TYPE_OBJECT = 0x0A,
            //TYPE_XML = 0x0B,
            //TYPE_BYTE_ARRAY = 0x0C
    }

    return pResult;
}
