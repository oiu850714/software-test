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

} // namespace