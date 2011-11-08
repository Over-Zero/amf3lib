#include "amf3_tests_pch.h"
#include "amf3_uint29.h"
#include <UnitTest++.h>

SUITE(UInt29)
{
    using namespace AMF3;

    TEST(Value0)
    {
        std::ostringstream os;
        os << UInt29(0);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0u, result.GetValue());
    }

    TEST(Value7F)
    {
        std::ostringstream os;
        os << UInt29(0x7F);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x7Fu, result.GetValue());
    }

    TEST(Value80)
    {
        std::ostringstream os;
        os << UInt29(0x7F);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x7Fu, result.GetValue());
    }

    TEST(Value3FFF)
    {
        std::ostringstream os;
        os << UInt29(0x3FFF);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x3FFFu, result.GetValue());
    }

    TEST(Value4000)
    {
        std::ostringstream os;
        os << UInt29(0x4000);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x4000u, result.GetValue());
    }

    TEST(Value1FFFFF)
    {
        std::ostringstream os;
        os << UInt29(0x1FFFFF);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x1FFFFFu, result.GetValue());
    }

    TEST(Value200000)
    {
        std::ostringstream os;
        os << UInt29(0x200000);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x200000u, result.GetValue());
    }

    TEST(Value1FFFFFFF)
    {
        std::ostringstream os;
        os << UInt29(0x1FFFFFFF);

        UInt29 result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(0x1FFFFFFFu, result.GetValue());
    }

    TEST(Value20000000)
    {
        std::ostringstream os;
        CHECK_THROW(os << UInt29(0x20000000), const char*);
    }
}
