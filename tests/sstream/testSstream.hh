// Copyright 2021, joshiayush Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of joshiayush Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CJSON_TESTS_SSTREAM_TESTSSTREAM_HH_
#define CJSON_TESTS_SSTREAM_TESTSSTREAM_HH_

#include <gtest/gtest.h>

#include <cstring>

#include "data/sstream/sstream.h"
#include "utils.hh"

#define _ARBITRARY_SSTREAM_TESTING_LENGTH 2147483648

class StringStreamTest : public ::testing::Test {
 protected:
  void TearDown() override { StringStreamDealloc(&sstream); }

 protected:
  StringStream sstream;
};

TEST_F(StringStreamTest, StringStreamDefAllocFunctionTest) {
  sstream = StringStreamDefAlloc();
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(sstream.length, 0);
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      SSTREAM_DEFAULT_SIZE, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(StringStreamTest,
       StringStreamAllocFunctionWithArbitrarySstreamLengthTest) {
  sstream = StringStreamAlloc(_ARBITRARY_SSTREAM_TESTING_LENGTH);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(sstream.length, 0);
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      _ARBITRARY_SSTREAM_TESTING_LENGTH, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(StringStreamTest, StringStreamStrAllocFunctionWithConstCharPointerTest) {
  const char* teststr =
      "Mohika says I'm that exam question that everyone left without "
      "understanding :(.";
  sstream = StringStreamStrAlloc(teststr);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(std::strcmp(sstream.data, teststr), 0);
  ASSERT_EQ(sstream.length, std::strlen(teststr));
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      sstream.length, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(
    StringStreamTest,
    StringStreamStrAllocFunctionWithConstCharPointerWithEmbededNullByteTest) {
  const char* teststr =
      "Mohika\0says\0I'm\0that\0exam\0question\0that\0everyone\0left\0without\0"
      "understanding\0:(.";
  sstream = StringStreamStrAlloc(teststr);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(std::strcmp(sstream.data, teststr), 0);
  ASSERT_EQ(sstream.length, std::strlen(teststr));
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      sstream.length, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(
    StringStreamTest,
    StringStreamStrNAllocFunctionWithConstCharPointerWithEmbededNullByteTest) {
  const char* teststr =
      "Mohika\0says\0I'm\0that\0exam\0question\0that\0everyone\0left\0without\0"
      "understanding\0:(;"
      "\0\0I\0did\0not\0get\0a\0chance\0to\0even\0attempt\0that\0exam\0:(.";
  const size_t strlen_ = 134;
  sstream = StringStreamStrNAlloc(teststr, strlen_);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(std::strncmp(sstream.data, teststr, strlen_), 0);
  ASSERT_EQ(sstream.length, strlen_);
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      sstream.length, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(StringStreamTest, StringStreamReallocFunctionTestForReallocNotRequired) {
  sstream = StringStreamAlloc(_ARBITRARY_SSTREAM_TESTING_LENGTH);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(sstream.length, 0);
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      _ARBITRARY_SSTREAM_TESTING_LENGTH, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
  ASSERT_EQ(
      StringStreamRealloc(&sstream, _ARBITRARY_SSTREAM_TESTING_LENGTH / 2),
      SSTREAM_REALLOC_NOT_REQUIRED);
  ASSERT_EQ(sstream.capacity, capacity);
}

TEST_F(StringStreamTest, StringStreamReallocFunctionTestForReallocSuccess) {
  sstream = StringStreamAlloc(_ARBITRARY_SSTREAM_TESTING_LENGTH);
  ASSERT_NE(sstream.data, (void*)0);
  ASSERT_EQ(sstream.length, 0);
  size_t capacity;
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      _ARBITRARY_SSTREAM_TESTING_LENGTH, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
  ASSERT_EQ(
      StringStreamRealloc(&sstream, _ARBITRARY_SSTREAM_TESTING_LENGTH * 2),
      SSTREAM_REALLOC_SUCCESS);
  ASSERT_EQ(sstream.length, 0);
  cjson::testing::sstream::utils::ComputeStringStreamBufferCapacity(
      _ARBITRARY_SSTREAM_TESTING_LENGTH * 2, capacity);
  ASSERT_EQ(sstream.capacity, capacity);
}

#endif  // CJSON_TESTS_SSTREAM_TESTSSTREAM_HH_
