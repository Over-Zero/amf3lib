#include "amf3_tests_pch.h"
#include "amf3_integer.h"
#include <UnitTest++.h>

SUITE(Deserialize)
{
    using namespace AMF3;

    TEST(Value)
    {
        std::ostringstream os;
        os << Integer(500);

        Integer result;
        std::istringstream is(os.str());
        is >> result;

        CHECK_EQUAL(500u, result.GetInteger());
    }
}
