#ifndef AMF3_STRING_H
#define AMF3_STRING_H

#include "amf3_type_base.h"
#include <string>

namespace AMF3
{
    class String : public TypeBase<TYPE_STRING>
    {
    public:
        String()
        {
        }

        String(const std::string& value) : m_value(value)
        {
        }

        const std::string& GetString() const
        {
            return m_value;
        }

        inline bool operator==(const std::string& value) const
        {
            return m_value == value;
        }

        inline bool operator!=(const std::string& value) const
        {
            return !(m_value == value);
        }

    private:
        std::string m_value;
    };

    OutStream& operator<<(OutStream& lhs, const String& rhs);
    InStream& operator>>(InStream& lhs, String& rhs);
}

#endif // AMF3_STRING_H
