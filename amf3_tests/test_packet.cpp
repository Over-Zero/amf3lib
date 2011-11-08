#include "amf3_tests_pch.h"
#include "test_packet.h"
#include <iomanip>
#include <string>

#undef _T
#define _T(A) A

namespace
{
    typedef std::ostream OutStream;
    typedef unsigned __int8 UInt8;

    enum State
    {
        STATE_INIT,
        STATE_STRING,
        STATE_HEX
    };

    void OpenPrintState(OutStream& stream, State state, bool empty)
    {
        if (state == STATE_STRING)
        {
            stream << (empty ? _T("'") : _T(" '"));
        }
        else
        {
            stream << (empty ? _T("") : _T(" "));
        }
    }

    void ClosePrintState(OutStream& stream, State state)
    {
        if (state == STATE_STRING)
        {
            stream << _T("'");
        }
    }
}

OutStream& operator<<(OutStream& lhs, const TestPacket& rhs)
{
    typedef std::string::const_iterator Itor;

    State state = STATE_INIT;
    bool empty = true;

    Itor end = rhs.GetData().end();
    for (Itor i = rhs.GetData().begin(); i != end; ++i)
    {
        UInt8 c = static_cast<UInt8>(*i);

        State newState = (c >= 32 && c <= 126 || c == '\r' || c == '\n')
            ? STATE_STRING : STATE_HEX;

        if (newState != state)
        {
            ClosePrintState(lhs, state);
            OpenPrintState(lhs, newState, empty);
        }

        if (newState == STATE_STRING)
        {
            if (c == '\r')
            {
                lhs << "\\r";
            }
            else if (c == '\n')
            {
                lhs << "\\n" << std::endl;
            }
            else
            {
                lhs << c;
            }
        }
        else
        {
            if (state == newState)
            {
                lhs << ' ';
            }
            lhs << std::setw(2) << std::setfill('0') << std::hex
                << std::uppercase << static_cast<int>(c);
        }

        state = newState;
        empty = false;
    }

    ClosePrintState(lhs, state);

    return lhs;
}

namespace
{
    bool Decode(char hex, char& byte)
    {
        bool result = true;

        if ('0' <= hex && hex <= '9')
        {
            byte += hex - '0';
        }
        else if ('A' <= hex && hex <= 'F')
        {
            byte += hex - 'A' + 0x0A;
        }
        else if ('a' <= hex && hex <= 'f')
        {
            byte += hex - 'a' + 0x0A;
        }
        else
        {
            result = false;
        }

        return result;
    }
}

TestPacket TestPacket::Hex(const char* pHexData)
{
    enum ParseState
    {
        PARSE_DIGIT1,
        PARSE_DIGIT2,
        PARSE_STRING,
        PARSE_DECIMAL,
        PARSE_COMMENT
    };

    std::string result;
    const char* pCursor;
    ParseState state = PARSE_DIGIT1;
    char byte = 0;
    char c;

    for (pCursor = pHexData; (c = *pCursor) != '\0'; ++pCursor)
    {
        switch (state)
        {
        case PARSE_DIGIT1:
            if (Decode(c, byte))
            {
                byte <<= 4;
                state = PARSE_DIGIT2;
            }
            else if (c == ' ')
            {
                // Skip spaces
            }
            else if (c == '\'')
            {
                state = PARSE_STRING;
            }
            else if (c == '[')
            {
                state = PARSE_DECIMAL;
            }
            else if (c == '(')
            {
                state = PARSE_COMMENT;
            }
            break;

        case PARSE_DIGIT2:
            if (Decode(c, byte))
            {
                result += byte;
                byte = 0;
                state = PARSE_DIGIT1;
                break;
            }
            throw "Bad hexadecimal value";

        case PARSE_STRING:
            if (c == '\'')
            {
                state = PARSE_DIGIT1;
            }
            else
            {
                result += c;
            }
            break;

        case PARSE_DECIMAL:
            if (c == ']')
            {
                result += byte;
                byte = 0;
                state = PARSE_DIGIT1;
            }
            else
            {
                if ('0' <= c && c <= '9')
                {
                    UInt32 value = byte * 10 + c - '0';
                    if (value > 0xFF)
                    {
                        throw "Too big decimal";
                    }
                    byte = static_cast<char>(value);
                    break;
                }
                throw "Invalid decimal digit";
            }
            break;

        case PARSE_COMMENT:
            if (c == ')')
            {
                state = PARSE_DIGIT1;
            }
            break;
        }
    }

    return result;
}

void TestPacket::CopyTo(UInt8* pBuffer, UInt32& size)
{
    std::memcpy(pBuffer, m_data.data(), m_data.size());
    size = static_cast<UInt32>(m_data.size());
}
