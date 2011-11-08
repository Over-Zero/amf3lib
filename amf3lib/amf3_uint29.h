#ifndef AMF_UINT29_H
#define AMF_UINT29_H

#include "amf3_defs.h"
#include "amf3_stream.h"

namespace AMF3
{
    class UInt29
    {
    public:
        UInt29() : m_value(0)
        {

        }

        UInt29(UInt32 value) : m_value(value)
        {

        }

        inline UInt32 GetValue() const
        {
            return m_value;
        }

        inline UInt29& operator=(UInt32 value)
        {
            m_value = value;
            return *this;
        }

        inline bool operator==(UInt32 value) const
        {
            return m_value == value;
        }

        inline bool operator!=(UInt32 value) const
        {
            return !(*this == value);
        }

        static bool IsValid(UInt32 value);

    private:
        UInt32 m_value;
    };

    OutStream& operator<<(OutStream& lhs, const UInt29& rhs);
    InStream& operator>>(InStream& lhs, UInt29& rhs);
}

#endif // AMF_UINT29_H
