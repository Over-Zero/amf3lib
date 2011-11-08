#include "../UnitTest++.h"

#include "../MemoryOutStream.h"
#include "../Strings.h"

using namespace UnitTest;

namespace {

TEST(DefaultIsEmptyString)
{
    MemoryOutStream const stream;
    CHECK(stream.GetText() != 0);
    CHECK_EQUAL(UNITTEST_TEXT(""), stream.GetText());
}

TEST(StreamingTextCopiesCharacters)
{
    MemoryOutStream stream;
    stream << UNITTEST_TEXT("Lalala");
    CHECK_EQUAL(UNITTEST_TEXT("Lalala"), stream.GetText());
}

TEST(StreamingMultipleTimesConcatenatesResult)
{
    MemoryOutStream stream;
    stream << UNITTEST_TEXT("Bork") << UNITTEST_TEXT("Foo") << UNITTEST_TEXT("Bar");
    CHECK_EQUAL(UNITTEST_TEXT("BorkFooBar"), stream.GetText());
}

TEST(StreamingIntWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << (int)123;
    CHECK_EQUAL(UNITTEST_TEXT("123"), stream.GetText());
}

TEST(StreamingUnsignedIntWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << (unsigned int)123;
    CHECK_EQUAL(UNITTEST_TEXT("123"), stream.GetText());
}

TEST(StreamingLongWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << (long)(-123);
    CHECK_EQUAL(UNITTEST_TEXT("-123"), stream.GetText());
}

TEST(StreamingUnsignedLongWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << (unsigned long)123;
    CHECK_EQUAL(UNITTEST_TEXT("123"), stream.GetText());
}

TEST(StreamingFloatWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << 3.1415f;
    CHECK(Strings::StrStr(stream.GetText(), UNITTEST_TEXT("3.1415")));
}

TEST(StreamingDoubleWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << 3.1415;
    CHECK(Strings::StrStr(stream.GetText(), UNITTEST_TEXT("3.1415")));
}

TEST(StreamingPointerWritesCorrectCharacters)
{
    MemoryOutStream stream;
    int* p = (int*)0x1234;
    stream << p;
    CHECK(Strings::StrStr(stream.GetText(), UNITTEST_TEXT("1234")));
}

TEST(StreamingSizeTWritesCorrectCharacters)
{
    MemoryOutStream stream;
    size_t const s = 53124;
    stream << s;
    CHECK_EQUAL(UNITTEST_TEXT("53124"), stream.GetText());
}

#ifdef UNITTEST_USE_CUSTOM_STREAMS

TEST(StreamInitialCapacityIsCorrect)
{
    MemoryOutStream stream(MemoryOutStream::GROW_CHUNK_SIZE);
    CHECK_EQUAL((int)MemoryOutStream::GROW_CHUNK_SIZE, stream.GetCapacity());
}

TEST(StreamInitialCapacityIsMultipleOfGrowChunkSize)
{
    MemoryOutStream stream(MemoryOutStream::GROW_CHUNK_SIZE + 1);
    CHECK_EQUAL((int)MemoryOutStream::GROW_CHUNK_SIZE * 2, stream.GetCapacity());
}


TEST(ExceedingCapacityGrowsBuffer)
{
    MemoryOutStream stream(MemoryOutStream::GROW_CHUNK_SIZE);
    stream << UNITTEST_TEXT("012345678901234567890123456789");
    Char const* const oldBuffer = stream.GetText();
    stream << UNITTEST_TEXT("0123456789");
    CHECK(oldBuffer != stream.GetText());
}

TEST(ExceedingCapacityGrowsBufferByGrowChunk)
{
    MemoryOutStream stream(MemoryOutStream::GROW_CHUNK_SIZE);
    stream << UNITTEST_TEXT("0123456789012345678901234567890123456789");
    CHECK_EQUAL(MemoryOutStream::GROW_CHUNK_SIZE * 2, stream.GetCapacity());
}

TEST(WritingStringLongerThanCapacityFitsInNewBuffer)
{
    MemoryOutStream stream(8);
    stream << UNITTEST_TEXT("0123456789ABCDEF");
    CHECK_EQUAL(UNITTEST_TEXT("0123456789ABCDEF"), stream.GetText());
}

TEST(WritingIntLongerThanCapacityFitsInNewBuffer)
{
    MemoryOutStream stream(8);
    stream << UNITTEST_TEXT("aaaa") << 123456;;
    CHECK_EQUAL(UNITTEST_TEXT("aaaa123456"), stream.GetText());
}

TEST(WritingFloatLongerThanCapacityFitsInNewBuffer)
{
    MemoryOutStream stream(8);
    stream << UNITTEST_TEXT("aaaa") << 123456.0f;;
    CHECK_EQUAL(UNITTEST_TEXT("aaaa123456.000000f"), stream.GetText());
}

TEST(WritingSizeTLongerThanCapacityFitsInNewBuffer)
{
    MemoryOutStream stream(8);
    stream << UNITTEST_TEXT("aaaa") << size_t(32145);
    CHECK_EQUAL(UNITTEST_TEXT("aaaa32145"), stream.GetText());
}

#endif

}
