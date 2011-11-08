#ifndef AMF3_DOUBLE_H
#define AMF3_DOUBLE_H

#include "amf3_type_base.h"

namespace AMF3
{
    class Double : public TypeBase<TYPE_DOUBLE>
    {
    public:
        Double() : m_value(0)
        {
        }

        Double(double value) : m_value(value)
        {
        }

        double GetDouble() const
        {
            return m_value;
        }

        inline bool operator==(UInt32 value) const
        {
            return m_value == value;
        }

        inline bool operator!=(UInt32 value) const
        {
            return !(*this == value);
        }

    private:
        double m_value;
    };

    OutStream& operator<<(OutStream& lhs, const Double& rhs);
    InStream& operator>>(InStream& lhs, Double& rhs);
}

#endif // AMF3_DOUBLE_H
