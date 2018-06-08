#include "LargeInteger.h"
#include "gtest/gtest.h"
#include <iostream>
#include <utility>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;


namespace
{


TEST(LargeIntegerCoverageLOL, LOL){
  //LargeInteger<6401> L1(9487);
}


class LargeIntegerConstructorTest : public testing::Test
{
protected:
  
  // naming convention: L_<BitLength>_<value>_<radix>
  LargeInteger <6400> L_6400_0_10;
  const QWORD* L_6400_0_10_internalBuffer;
  int L_6400_0_10_internalBufferLength;
  virtual void SetUp() {
    L_6400_0_10_internalBuffer = L_6400_0_10.GetInternalBuffer();
    L_6400_0_10_internalBufferLength = L_6400_0_10.GetInternalBufferLength();
  }
};


TEST_F(LargeIntegerConstructorTest, DefaultConstructor){
  for(int i = 0; i < L_6400_0_10_internalBufferLength; i++){
    EXPECT_EQ(0, L_6400_0_10_internalBuffer[i]);
  }
}

TEST_F(LargeIntegerConstructorTest, CopyConstructor){
  LargeInteger <6400> CoppiedToLargeInteger(L_6400_0_10);
  auto InternalBuffer = CoppiedToLargeInteger.GetInternalBuffer();
  auto InternalBufferLength = CoppiedToLargeInteger.GetInternalBufferLength();
  // buffer in new object should be different from original object
  ASSERT_NE(L_6400_0_10_internalBuffer, InternalBuffer);

  // buffer length should be equal
  ASSERT_EQ(L_6400_0_10_internalBufferLength, InternalBufferLength);

  // content should be equal
  for(int i = 0; i < L_6400_0_10_internalBufferLength; i++){
    EXPECT_EQ(InternalBuffer[i], L_6400_0_10_internalBuffer[i]);
  }
}

TEST_F(LargeIntegerConstructorTest, MoveConstructor){
  auto original_buffer = L_6400_0_10_internalBuffer;
  LargeInteger <6400> MovedToLargeInteger(std::move(L_6400_0_10));
  auto InternalBuffer = MovedToLargeInteger.GetInternalBuffer();
  auto InternalBufferLength = MovedToLargeInteger.GetInternalBufferLength();
  
  // the original object's internal buffer should be moved
  ASSERT_EQ(L_6400_0_10.GetInternalBuffer(), nullptr);

  // new object's internal buffer should be the same with original buffer
  ASSERT_EQ(InternalBuffer, original_buffer);

  // buffer length should be equal
  ASSERT_EQ(InternalBufferLength, L_6400_0_10_internalBufferLength);

  // content should be equal
  for(int i = 0; i < InternalBufferLength; i++){
    EXPECT_EQ(0, InternalBuffer[i]);
  }
}

TEST_F(LargeIntegerConstructorTest, QWORDConstructor){
  QWORD num = 0x0123456789ABCDEF;
  LargeInteger<6400> L(num);

  auto InternalBuffer = L.GetInternalBuffer();
  auto InternalBufferLength = L.GetInternalBufferLength();

  // all except first QWORD should be 0; first QWORD should be equal to num
  EXPECT_EQ(num, InternalBuffer[0]);
  for(int i = 1; i < InternalBufferLength; i++){
    EXPECT_EQ(0, InternalBuffer[i]);
  }
}

TEST_F(LargeIntegerConstructorTest, ConstructorFromDifferentLength){

  auto InternalBuffer = L_6400_0_10.GetInternalBuffer();
  auto InternalBufferLength = L_6400_0_10.GetInternalBufferLength();

  //overwritting internal binary data lol  
  for(int i = 0; i < InternalBufferLength; i++){
    InternalBuffer[i] = i;
  }

  LargeInteger<3200> L_3200(L_6400_0_10);
  LargeInteger<12800> L_12800(L_6400_0_10);
  
  auto L_3200_InternalBuffer = L_3200.GetInternalBuffer();
  auto L_3200_InternalBufferLength = L_3200.GetInternalBufferLength();
  auto L_12800_InternalBuffer = L_12800.GetInternalBuffer();
  auto L_12800_InternalBufferLength = L_12800.GetInternalBufferLength();

  // case 1: smaller LargeInteger
  for(int i = 0; i < L_3200_InternalBufferLength; i++){
    EXPECT_EQ(L_3200_InternalBuffer[i], i);
  }

  // case 2: larger LargeInteger
  for(int i = 0; i < InternalBufferLength; i++){
    EXPECT_EQ(L_12800_InternalBuffer[i], i);
  }
  for(int i = InternalBufferLength; i < L_12800_InternalBufferLength; i++){
    EXPECT_EQ(L_12800_InternalBuffer[i], 0);
  }
}

TEST(LargeIntegerSetFromStringAndConvertToStringTest, Radix16NormalInput){

  string str1 = "fecdba9876543210";
  int radix = 16;
  LargeInteger<6400> L;
  L.SetFromString(str1.c_str(), radix);

  EXPECT_EQ(string(L.ConvertToString(16)), str1);

  string str2 = "0000000000000000";
  L.SetFromString(str2.c_str(), radix);

  // truncate leading zeros
  EXPECT_EQ(string(L.ConvertToString(16)), "0");

  string str3 = "00000000000000000000000000aaa";
  L.SetFromString(str3.c_str(), radix);

  // truncate leading zeros
  EXPECT_EQ(string(L.ConvertToString(16)), "aaa");
}

TEST(LargeIntegerSetFromStringAndConvertToStringTest, RadixNotPowerOf2NormalInput){
  string str1 = "987654321098765432109876543210";
  int radix = 10;
  LargeInteger<6400> L;
  L.SetFromString(str1.c_str(), radix);

  EXPECT_EQ(string(L.ConvertToString(10)), str1);

  string str2 = "00000000000000000000000000000";
  L.SetFromString(str2.c_str(), radix);

  // truncate leading zeros
  EXPECT_EQ(string(L.ConvertToString(10)), "0");

  string str3 = "00000000000000000000000000888";
  L.SetFromString(str3.c_str(), radix);

  // truncate leading zeros
  EXPECT_EQ(string(L.ConvertToString(10)), "888");

}

TEST(LargeIntegerSetFromStringAndConvertToStringTest, InputCausingOverflow){

  // L will overflow if it's set from str1
  // this string need 6400+640 bits, so it will cause LargeInteger<6400> to overflow
  string str1 = "aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbb";

  int radix = 16;
  LargeInteger<6400> L;
 
  L.SetFromString(str1.c_str(), radix);
  // L's string representation will not equal to str1
  EXPECT_NE(string(L.ConvertToString(16)), str1);
}

TEST(LargeIntegerSetFromStringAndConvertToStringTest, RadixCauseThrow){
  // throw INVALID_RADIX, type is int
  string str1 = "0101010101010101";

  LargeInteger<6400> L;
  
  int radix = 1;
  EXPECT_THROW(L.SetFromString(str1.c_str(), radix), int);
  EXPECT_THROW(L.ConvertToString(radix), int);

  for(radix = 2; radix < 37; radix++){
    EXPECT_NO_THROW(L.SetFromString(str1.c_str(), radix));
  }

  EXPECT_THROW(L.SetFromString(str1.c_str(), radix), int);
  EXPECT_THROW(L.ConvertToString(radix), int);
}

TEST(LargeIntegerSetFromStringAndConvertToStringTest, InputCauseThrow){
  // throw ILLEGAL_CHARACTER, type is int
  string s2 = "01";
  string s2_throw = "x01";
  string s16 = "0123456789abcdef";
  string s16_throw = "0123456789abcdefg";

  string s36 = "0123456789abcdefghijklmnopqrstuvwxyz";
  string s36_throw = "0123456789abcdefghijklmnopqrstuvwxyz,";

  LargeInteger<6400> L;

  EXPECT_NO_THROW(L.SetFromString(s2.c_str(), 2));
  EXPECT_THROW(L.SetFromString(s2_throw.c_str(), 2), int);
  EXPECT_NO_THROW(L.SetFromString(s16.c_str(), 16));
  EXPECT_THROW(L.SetFromString(s16_throw.c_str(), 16), int);
  EXPECT_NO_THROW(L.SetFromString(s36.c_str(), 36));
  EXPECT_THROW(L.SetFromString(s36_throw.c_str(), 36), int);
  
}

} // namespace