#ifndef AMF3_BOOLEAN_H
#define AMF3_BOOLEAN_H

#include "amf3_stream.h"

namespace AMF3
{
    class Boolean
    {
    public:
        Boolean(bool value = false) : m_value(value)
        {
        }

        bool GetBoolean() const
        {
            return m_value;
        }

        bool operator==(const Boolean& rhs) const
        {
            return m_value == rhs.m_value;
        }

    private:
        bool m_value;
    };

    OutStream& operator<<(OutStream& lhs, const Boolean& rhs);
    InStream& operator>>(InStream& lhs, Boolean& rhs);
}

#endif // AMF3_BOOLEAN_H
