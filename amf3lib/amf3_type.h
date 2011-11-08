#ifndef AMF3_TYPES_H
#define AMF3_TYPES_H

namespace AMF3
{
    enum Type
    {
        TYPE_UNDEFINED = 0x00,
        TYPE_NULL = 0x01,
        TYPE_FALSE = 0x02,
        TYPE_TRUE = 0x03,
        TYPE_INTEGER = 0x04,
        TYPE_DOUBLE = 0x05,
        TYPE_STRING = 0x06,
        TYPE_XML_DOC = 0x07,
        TYPE_DATE = 0x08,
        TYPE_ARRAY = 0x09,
        TYPE_OBJECT = 0x0A,
        TYPE_XML = 0x0B,
        TYPE_BYTE_ARRAY = 0x0C
    };

    typedef unsigned __int32 UInt32;
}

#endif // AMF3_TYPES_H
