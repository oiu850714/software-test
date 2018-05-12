#include "LargeInteger.h"
#include "gtest/gtest.h"

/*

  LargeInteger.h
  Unsigned large integer class.


  Note: the number stored in this class is in little-endian binary. And all
        the binary data stored in the memory is considered encoded in LE too.
        If your system is a BE system, please rewrite this library.

        Fixed-width, little-endian binary, dynamiclly allocated.

  Designer:    cin.getline
  Last update: 2012-07-21

*/

// #ifndef _CIN_GETLINE_LARGE_INTEGER_H__
// #define _CIN_GETLINE_LARGE_INTEGER_H__

// #ifndef __cplusplus
// #error *** This is a C++ library! ***
// #endif

// #include "TypeDefinition.h"

// #define DIVISION_BY_ZERO 1
// #define MODULO_BY_ZERO 2
// #define INVALID_RADIX 3
// #define ILLEGAL_CHARACTER 4

// // Declartion.

// // BitLength indicates the minimun number of bits that this class can store.
// template <size_t BitLength> class LargeInteger {

//   // Interface.
// public:
//   // Constructors.
//   LargeInteger();
//   LargeInteger(const LargeInteger<BitLength> &RHS);
//   LargeInteger(LargeInteger<BitLength> &&RHS);
//   LargeInteger(QWORD Number);

//   // Construct from other bit length.
//   template <size_t RHSBitLength>
//   explicit LargeInteger(const LargeInteger<RHSBitLength> &RHS);

//   // Destructor.
//   ~LargeInteger();

//   // Bitwise operators.
//   LargeInteger<BitLength> &operator>>=(int NumberToShift);
//   LargeInteger<BitLength> &operator<<=(int NumberToShift);
//   LargeInteger<BitLength> &operator&=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator|=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator^=(const LargeInteger<BitLength> &RHS);

//   LargeInteger<BitLength> operator~() const;
//   LargeInteger<BitLength> operator>>(int NumberToShift) const;
//   LargeInteger<BitLength> operator<<(int NumberToShift) const;

//   // Comparison operators.
//   bool operator==(const LargeInteger<BitLength> &RHS) const;
//   bool operator!=(const LargeInteger<BitLength> &RHS) const;
//   bool operator>=(const LargeInteger<BitLength> &RHS) const;
//   bool operator<=(const LargeInteger<BitLength> &RHS) const;
//   bool operator>(const LargeInteger<BitLength> &RHS) const;
//   bool operator<(const LargeInteger<BitLength> &RHS) const;

//   // Convertions.
//   explicit operator bool() const;
//   explicit operator QWORD() const;
//   explicit operator DWORD() const;

//   // Assignment operators.
//   LargeInteger<BitLength> &operator=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator=(LargeInteger<BitLength> &&RHS);
//   LargeInteger<BitLength> &operator=(QWORD Number);

//   // Arithmetic operators.
//   LargeInteger<BitLength> &operator+=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator-=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator*=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator/=(const LargeInteger<BitLength> &RHS);
//   LargeInteger<BitLength> &operator%=(const LargeInteger<BitLength> &RHS);

//   LargeInteger<BitLength> operator+() const;
//   LargeInteger<BitLength> operator-() const;
//   LargeInteger<BitLength> operator++(int);
//   LargeInteger<BitLength> &operator++();
//   LargeInteger<BitLength> operator--(int);
//   LargeInteger<BitLength> &operator--();

//   // Other member functions.

//   // I/O data without casting.
//   void GetRawData(void *OutputDataBuffer) const;
//   void SetRawData(const void *InputDataBuffer);

//   // I/O via a string.
//   const char *ConvertToString(unsigned int Radix) const;
//   void SetFromString(const char *StrNumber, unsigned int Radix);

//   // Presented in byte.
//   size_t GetBufferSize(void) const;

//   // Private members.
// private:
//   QWORD *NumberCell;
//   static const int QWORDLength =
//       (BitLength > 0) ? ((BitLength / 64) + ((BitLength % 64) ? 1 : 0)) : 1;

//   // Output functions used by the public function ConvertToString.
//   void RegularConvertToString(unsigned int Radix, char *StrToWrite) const;
//   void PowerOfTwoConvertToString(unsigned int Radix, char *StrToWrite) const;

//   // Input functions used by the public function SetFromString.
//   void RegularSetFromString(const char *StrNumber, unsigned int Radix);
//   void PowerOfTwoSetFromString(const char *StrNumber, unsigned int Radix);

//   // Friend declaration.
//   template <size_t OtherBitLength> friend class LargeInteger;
// };

// // Arthematic operator declaration.

// // Opertor+
// template <size_t Length>
// LargeInteger<Length> operator+(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator+(const LargeInteger<Length> &LHS,
//                                  LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator+(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator+(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator-
// template <size_t Length>
// LargeInteger<Length> operator-(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> operator-(const LargeInteger<Length> &LHS,
//                                LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator-(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator-(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator*
// template <size_t Length>
// LargeInteger<Length> operator*(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator*(const LargeInteger<Length> &LHS,
//                                  LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator*(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator*(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator/
// template <size_t Length>
// LargeInteger<Length> operator/(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> operator/(const LargeInteger<Length> &LHS,
//                                LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator/(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator/(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator%
// template <size_t Length>
// LargeInteger<Length> operator%(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> operator%(const LargeInteger<Length> &LHS,
//                                LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator%(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator%(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Bitwise operator declaration.

// // Operator&
// template <size_t Length>
// LargeInteger<Length> operator&(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator&(const LargeInteger<Length> &LHS,
//                                  LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator&(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator&(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator|
// template <size_t Length>
// LargeInteger<Length> operator|(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator|(const LargeInteger<Length> &LHS,
//                                  LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator|(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator|(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// // Operator^
// template <size_t Length>
// LargeInteger<Length> operator^(const LargeInteger<Length> &LHS,
//                                const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator^(const LargeInteger<Length> &LHS,
//                                  LargeInteger<Length> &&RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator^(LargeInteger<Length> &&LHS,
//                                  const LargeInteger<Length> &RHS);

// template <size_t Length>
// LargeInteger<Length> &&operator^(LargeInteger<Length> &&LHS,
//                                  LargeInteger<Length> &&RHS);

// #include "LargeInteger.cpp"
// #endif
