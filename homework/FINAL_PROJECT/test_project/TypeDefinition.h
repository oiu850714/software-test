/*

  Type definitions used by cin.getline.

  Note:
     1) Before porting any program to other platform, please modify this header.
     2) If you have to include Windows.h, please include it before you include
        this header.

*/

#include <cstddef>



#ifndef CIN_GETLINE_TYPE_DEF_H__
#define CIN_GETLINE_TYPE_DEF_H__

#ifdef _WINDEF_



// 64-bit unsigned int definition used under Windows.
typedef unsigned __int64 QWORD;



#else



// Some type definition.

// Unsigned data types.
typedef unsigned char       BYTE;
typedef unsigned short int  WORD;
typedef unsigned int       DWORD;
typedef unsigned long long QWORD;



// Signed data types.
typedef signed char      INT8;
typedef signed short int INT16;
typedef signed int       INT32;
typedef signed long long INT64;



#endif

#endif
