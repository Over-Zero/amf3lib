#ifndef TEST_PACKET_H
#define TEST_PACKET_H

#include "amf3_stream.h"
#include <string>
#include <sstream>

/// A special utility class which stands as a binary data storage.
/// It simplifies binary data representation and printing through
/// the defined 'hex data' syntax.
///
/// Sequence 0x01, 0x2, 0x03 in hexadecimal representation:
/// "010203" or "01 02 03".
/// ASCII character (32 <= code <= 126) sequence 'a', 'b', 'c':
/// "'abc'".
/// The hexadecimal and character values can be combined. The sequence of
/// 0xAB, 0xCD, 'a' and 'b' may look like:
/// "ABcd 'ab'" or "ab CD 'a' 'b'".
/// The 'hex data' syntax supports inline comments. The sequence of
/// 0xAB, 0xCD, 'a' and 'b' may also look like:
/// "ABCD (header data) 'ab' (payload)".
/// 
class TestPacket
{
public:
    std::string m_data;

    typedef unsigned __int8 UInt8;
    typedef unsigned __int32 UInt32;

    static TestPacket Hex(const char* pHexData);

    TestPacket()
    {
    }

    TestPacket(const std::string& data)
        : m_data(data.c_str(), data.size())
    {
    }

    TestPacket(const std::ostringstream& data)
        : m_data(data.str())
    {
    }

    TestPacket(const char* pData, size_t size)
        : m_data(pData, size)
    {
    }

    const std::string& GetData(void) const
    {
        return m_data;
    }

    size_t GetSize(void) const
    {
        return m_data.size();
    }

    void CopyTo(UInt8* pBuffer, UInt32& size);

    template<class T0>
    TestPacket WithValues(T0 value) const
    {
        TestPacket result(m_data);
        result.Replace(0, value);
        return result;
    }

    template<class T0, class T1>
    TestPacket WithValues(T0 v0, T1 v1) const
    {
        TestPacket result(m_data);
        result.Replace(0, v0);
        result.Replace(1, v1);
        return result;
    }

    template<class T0, class T1, class T2>
    TestPacket WithValues(T0 v0, T1 v1, T2 v2) const
    {
        TestPacket result(m_data);
        result.Replace(0, v0);
        result.Replace(1, v1);
        result.Replace(2, v2);
        return result;
    }

    template<class T0, class T1, class T2, class T3>
    TestPacket WithValues(T0 v0, T1 v1, T2 v2, T3 v3) const
    {
        TestPacket result(m_data);
        result.Replace(0, v0);
        result.Replace(1, v1);
        result.Replace(2, v2);
        result.Replace(3, v3);
        return result;
    }

    template<class T0, class T1, class T2, class T3, class T4>
    TestPacket WithValues(T0 v0, T1 v1, T2 v2, T3 v3, T4 v4) const
    {
        TestPacket result(m_data);
        result.Replace(0, v0);
        result.Replace(1, v1);
        result.Replace(2, v2);
        result.Replace(3, v3);
        result.Replace(4, v4);
        return result;
    }

    template<class T0, class T1, class T2, class T3, class T4, class T5>
    TestPacket WithValues(T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) const
    {
        TestPacket result(m_data);
        result.Replace(0, v0);
        result.Replace(1, v1);
        result.Replace(2, v2);
        result.Replace(3, v3);
        result.Replace(4, v4);
        result.Replace(5, v5);
        return result;
    }

    bool operator==(const TestPacket& rhs) const
    {
        return m_data == rhs.m_data;
    }

    bool operator!=(const TestPacket& rhs) const
    {
        return !(*this == rhs);
    }

private:
    template<class T>
    void Replace(size_t position, T value)
    {
        std::string specificator;
        {
            std::ostringstream os;
            os << "{" << position << "}";
            specificator = os.str();
        }
        size_t i;
        while ((i = m_data.find(specificator)) != std::string::npos)
        {
            std::ostringstream os;
            os << m_data.substr(0, i) << value << m_data.substr(i + specificator.size());
            m_data = os.str();
        }
    }
};

AMF3::OutStream& operator<<(AMF3::OutStream& lhs, const TestPacket& rhs);

#endif // TEST_PACKET_H
