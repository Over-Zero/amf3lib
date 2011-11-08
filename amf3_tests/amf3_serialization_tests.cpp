#include "amf3_tests_pch.h"
#include "amf3_undefined.h"
#include "amf3_null.h"
#include "amf3_boolean.h"
#include "amf3_integer.h"
#include "amf3_double.h"
#include "amf3_string.h"
#include "test_packet.h"
#include <UnitTest++.h>

SUITE(Serialize)
{
    using namespace AMF3;

    TEST(Undefined)
    {
        std::ostringstream os;
        os << Undefined();
        CHECK_EQUAL(TestPacket::Hex("00"), TestPacket(os));
    }

    TEST(Null)
    {
        std::ostringstream os;
        os << Null();
        CHECK_EQUAL(TestPacket::Hex("01"), TestPacket(os));
    }

    TEST(BooleanFalse)
    {
        std::ostringstream os;
        os << Boolean(false);
        CHECK_EQUAL(TestPacket::Hex("02"), TestPacket(os));
    }

    TEST(BooleanTrue)
    {
        std::ostringstream os;
        os << Boolean(true);
        CHECK_EQUAL(TestPacket::Hex("03"), TestPacket(os));
    }

    TEST(Integer)
    {
        std::ostringstream os;
        os << Integer(0x1FFFFFFF);
        CHECK_EQUAL(TestPacket::Hex("04 FF FF FF FF"), TestPacket(os));
    }

    TEST(Double)
    {
        std::ostringstream os;
        os << Double(-1.0);
        CHECK_EQUAL(TestPacket::Hex("05 BF F0 00 00 00 00 00 00"), TestPacket(os));
    }

    TEST(String)
    {
        std::ostringstream os;
        os << String("123");
        CHECK_EQUAL(TestPacket::Hex("06 07 '123'"), TestPacket(os));
    }

    TEST(EmptyString)
    {
        std::ostringstream os;
        os << String();
        CHECK_EQUAL(TestPacket::Hex("06 01"), TestPacket(os));
    }
}
