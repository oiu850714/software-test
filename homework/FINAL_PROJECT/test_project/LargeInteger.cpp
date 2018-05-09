/*

  LargeInteger.cpp
  Unsigned large integer class.

  Designer:    cin.getline
  Last update: 2012-07-21

*/





#ifndef _CIN_GETLINE_LARGE_INTEGER_CPP__
#define _CIN_GETLINE_LARGE_INTEGER_CPP__

#ifndef __cplusplus
#error *** This is a C++ library! ***
#endif

#include"TypeDefinition.h"
#include"LargeInteger.h"





// Anonymous namespace to contain some function used in this cpp file.
// Definition of some functions used in the class "LargeInteger".
namespace{

	// Declaration.
	QWORD FindSuperRadix(unsigned int  Radix, int*   PowerToSave);
	int   CharToNumber  (char          Digit, unsigned int Radix);
	char  NumberToChar  (unsigned int Number);
	void  ReverseString (char*  StrToReverse, size_t   StrLength);


	// Definitions.
	// Used in ConvertToString.
	QWORD FindSuperRadix(unsigned int Radix, int* PowerToSave){

		// Data: some pre-calculated data.
		static const QWORD SuperRadixTable[35]={0x8000000000000000llu, 0xa8b8b452291fe821llu, 0x4000000000000000llu,
		                                        0x6765c793fa10079dllu, 0x41c21cb8e1000000llu, 0x3642798750226111llu,
		                                        0x8000000000000000llu, 0xa8b8b452291fe821llu, 0x8ac7230489e80000llu,
		                                        0x4d28cb56c33fa539llu, 0x1eca170c00000000llu, 0x780c7372621bd74dllu,
		                                        0x1e39a5057d810000llu, 0x5b27ac993df97701llu, 0x1000000000000000llu,
		                                        0x27b95e997e21d9f1llu, 0x5da0e1e53c5c8000llu, 0xd2ae3299c1c4aedbllu,
		                                        0x16bcc41e90000000llu, 0x2d04b7fdd9c0ef49llu, 0x5658597bcaa24000llu,
		                                        0xa0e2073737609371llu, 0x0c29e98000000000llu, 0x14adf4b7320334b9llu,
		                                        0x226ed36478bfa000llu, 0x383d9170b85ff80bllu, 0x5a3c23e39c000000llu,
		                                        0x8e65137388122bcdllu, 0xdd41bb36d259e000llu, 0x0aee5720ee830681llu,
		                                        0x1000000000000000llu, 0x172588ad4f5f0981llu, 0x211e44f7d02c1000llu,
		                                        0x2ee56725f06e5c71llu, 0x41c21cb8e1000000llu};

		const static int SuperRadixPower[35]={63, 40, 31, 27, 24, 22, 21, 20, 19, 18,
		                                      17, 17, 16, 16, 15, 15, 15, 15, 14, 14,
		                                      14, 14, 13, 13, 13, 13, 13, 13, 13, 12,
		                                      12, 12, 12, 12, 12};


		// Note: no check for invalid radix. You have to make sure the radix
		//       is valid, or there will be a segment fault.
		*PowerToSave = SuperRadixPower[Radix-2];

		return SuperRadixTable[Radix-2];

		}


	// Convert a digit character to a number.
	int CharToNumber(char Digit, unsigned int Radix){

		int Number;


		// Dec digit.
		if( Digit>='0' && Digit<='9' )
			Number = Digit-'0';

		// Upper case digit.
		else if( Digit>='A' && Digit<='Z' )
			Number = Digit-'A'+10;

		// Lower case digit.
		else if( Digit>='a' && Digit<='z' )
			Number = Digit-'a'+10;

		// Illegal character.
		else
			throw ILLEGAL_CHARACTER;


		// If the digit is valid, i.e., it isn't over the radix.
		if( static_cast<unsigned int>(Number) < Radix )
			return Number;

		// Invalid.
		else
			throw ILLEGAL_CHARACTER;

		}


	// Convert a integer into an character.
	// No check for Number. If it's invalid, there will be a segment fault.
	char NumberToChar(unsigned int Number){

		static const char* NumberTable = "0123456789abcdefghijklmnopqrstuvwxyz";
		
		return NumberTable[Number];
		
		}


	// Reverse a string.
	void ReverseString(char* StrToReverse, size_t StrLength){
		
		char         TmpChar;
		const size_t SwapEdge = StrLength/2;

		// Swaping loop.
		for(size_t Index=0; Index<SwapEdge; Index++){

			TmpChar                         = StrToReverse[Index];
			StrToReverse[            Index] = StrToReverse[StrLength-Index-1];
			StrToReverse[StrLength-Index-1] = TmpChar;

			}

		}


	}





// Definition of member functions of the class "LargeInteger".

// Default constructor.
template<size_t BitLength>
LargeInteger<BitLength>::LargeInteger(){

	NumberCell = reinterpret_cast<QWORD*>( operator new ( QWORDLength*8 ) );

	}



// Copy constructor.
template<size_t BitLength>
LargeInteger<BitLength>::LargeInteger(const LargeInteger<BitLength>& RHS){

	NumberCell = reinterpret_cast<QWORD*>( operator new ( QWORDLength*8 ) );

	for(int Index=0; Index<QWORDLength; Index++)
		NumberCell[Index]=RHS.NumberCell[Index];

	}



// Move constructor.
template<size_t BitLength>
LargeInteger<BitLength>::LargeInteger(LargeInteger<BitLength>&& RHS){
	
	NumberCell=RHS.NumberCell;
	RHS.NumberCell=0;
	
	}



// Construct from a QWORD variable.
template<size_t BitLength>
LargeInteger<BitLength>::LargeInteger(QWORD Number){
	
	NumberCell = reinterpret_cast<QWORD*>( operator new ( QWORDLength*8 ) );

	NumberCell[0]=Number;

	for(int Index=1; Index<QWORDLength; Index++)
		NumberCell[Index]=0;

	}



// Construct from different length.
template<size_t ThisBitLength>
template<size_t RHSBitLength>
LargeInteger<ThisBitLength>::LargeInteger(const LargeInteger<RHSBitLength>& RHS){

	int Index=0, CopyEdge;


	NumberCell = reinterpret_cast<QWORD*>( operator new ( QWORDLength*8 ) );

	// Choose the smaller.
	if( QWORDLength > LargeInteger<RHSBitLength>::QWORDLength )
		CopyEdge = LargeInteger<RHSBitLength>::QWORDLength;

	else
		CopyEdge = QWORDLength;

	// Start to copy.
	for(Index=0; Index<CopyEdge; Index++)
		this->NumberCell[Index]=RHS.NumberCell[Index];

	// Padding.
	while(Index<QWORDLength){

		this->NumberCell[Index]=0;
		Index++;

		}

	}



// Destructor.
template<size_t BitLength>
LargeInteger<BitLength>::~LargeInteger(){

	operator delete (NumberCell);
	NumberCell = 0;

	}



// Right shift.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator>>=(int NumberToShift){

	// Negative.
	if( NumberToShift<0 )
		return ((*this)<<=(-NumberToShift));


	const int QWORDOffset = NumberToShift/64;
	const int BitOffset   = NumberToShift%64;
	const int Edge        = (QWORDLength-1) - QWORDOffset;
	int       Index       = 0;


	// If NumberToShift isn't a multiple of 64.
	if( BitOffset ){
		
		// Shift step. Process the entries without the final one.
		for(Index=0; Index<Edge; Index++)
			NumberCell[Index] = (NumberCell[Index+QWORDOffset]  >>    BitOffset )|
			                    (NumberCell[Index+QWORDOffset+1]<<(64-BitOffset));
		
		// Check the range of the last entry in NumberCell and process the
		// final entry.
		if( QWORDLength > QWORDOffset ){

			NumberCell[Index] = NumberCell[Index+QWORDOffset]>>BitOffset;
			Index++;

			}
		
		}
	// If NumberToShift is a multiple of 64.
	else{
		
		// Shift.
		for(Index=0; Index<=Edge; Index++)
			NumberCell[Index] = NumberCell[Index+QWORDOffset];
		
		}
	
	
	// Padding step.
	while( Index<QWORDLength ){
		
		NumberCell[Index] = 0;
		Index++;
		
		}

	return *this;

	}



// Left shift.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator<<=(int NumberToShift){

	// Negative.
	if( NumberToShift<0 )
		return ((*this)>>=(-NumberToShift));


	const int QWORDOffset = NumberToShift/64;
	const int BitOffset   = NumberToShift%64;
	const int Edge        = QWORDOffset;
	int       Index       = QWORDLength-1;


	// If NumberToShift isn't a multiple of 64.
	if( BitOffset ){
		
		// Shift step.
		for(Index=QWORDLength-1; Index>Edge; Index--)
			NumberCell[Index] = (NumberCell[Index-QWORDOffset]  <<    BitOffset )|
			                    (NumberCell[Index-QWORDOffset-1]>>(64-BitOffset));
		
		// Check the range of the last entry in NumberCell.
		if( QWORDLength > QWORDOffset ){

			NumberCell[Index] = NumberCell[Index-QWORDOffset]<<BitOffset;
			Index--;

			}
		
		}
	// If NumberToShift is a multiple of 64.
	else{
		
		// Shift.
		for(Index=QWORDLength-1; Index>=Edge; Index--)
			NumberCell[Index] = NumberCell[Index-QWORDOffset];
		
		}
	
	
	// Padding step.
	while( Index>=0 ){
		
		NumberCell[Index] = 0;
		Index--;
		
		}

	return *this;

	}



// Bitwise AND.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator&=(const LargeInteger<BitLength>& RHS){

	for(int Index=0; Index<QWORDLength; Index++)
		NumberCell[Index] &= RHS.NumberCell[Index];

	return *this;

	}



// Bitwise OR.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator|=(const LargeInteger<BitLength>& RHS){

	for(int Index=0; Index<QWORDLength; Index++)
		NumberCell[Index] |= RHS.NumberCell[Index];

	return *this;

	}



// Bitwise XOR.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator^=(const LargeInteger<BitLength>& RHS){

	for(int Index=0; Index<QWORDLength; Index++)
		NumberCell[Index] ^= RHS.NumberCell[Index];

	return *this;

	}



// Bitwise NOT.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator~() const{

	LargeInteger<BitLength> Result(*this);

	for(int Index=0; Index<QWORDLength; Index++)
		Result.NumberCell[Index] = ~(Result.NumberCell[Index]);

	return Result;

	}



// Right shift.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator>>(int NumberToShift) const{

	LargeInteger<BitLength> Result(*this);

	Result >>= NumberToShift;

	return Result;

	}



// Left shift.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator<<(int NumberToShift) const{

	LargeInteger<BitLength> Result(*this);

	Result <<= NumberToShift;

	return Result;

	}



// Logical operations.

// Logical equal.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator==(const LargeInteger<BitLength>& RHS) const{

	for(int Index=0; Index<QWORDLength; Index++){
		
		if( this->NumberCell[Index] != RHS.NumberCell[Index] )
			return false;

		}

	return true;

	}



// Logical not equal.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator!=(const LargeInteger<BitLength>& RHS) const{

	return ( !( (*this)==RHS ) );

	}



// Logical greater than or equal to.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator>=(const LargeInteger<BitLength>& RHS) const{

	int Index = QWORDLength;


	while(--Index){
		
		if( this->NumberCell[Index] != RHS.NumberCell[Index] )
			break;
		
		}

	// Equal to.
	if(Index<0)
		return true;

	// Not equal to.
	else
		return ( this->NumberCell[Index] >= RHS.NumberCell[Index] );

	}



// Logical less than or equal to.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator<=(const LargeInteger<BitLength>& RHS) const{

	int Index = QWORDLength;


	while(--Index){
		
		if( this->NumberCell[Index] != RHS.NumberCell[Index] )
			break;
		
		}

	// Equal to.
	if(Index<0)
		return true;

	// Not equal to.
	else
		return ( this->NumberCell[Index] <= RHS.NumberCell[Index] );

	}



// Logical greater than.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator>(const LargeInteger<BitLength>& RHS) const{

	return ( !( (*this)<=RHS ) );

	}



// Logical less than.
template<size_t BitLength>
bool LargeInteger<BitLength>::operator<(const LargeInteger<BitLength>& RHS) const{

	return ( !( (*this)>=RHS ) );

	}



// Convertions.

// Convert to boolean.
template<size_t BitLength>
LargeInteger<BitLength>::operator bool () const{

	for(int Index=0; Index<QWORDLength; Index++){

		if( NumberCell[Index] )
			return true;

		}

	return false;

	}



// Convert to QWORD.
template<size_t BitLength>
LargeInteger<BitLength>::operator QWORD () const{

	return NumberCell[0];

	}



// Convert to DWORD.
template<size_t BitLength>
LargeInteger<BitLength>::operator DWORD () const{

	return static_cast<DWORD>(NumberCell[0]);

	}



// Copy assignment.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator=(const LargeInteger<BitLength>& RHS){

	// Skip self-assignment. Efficiency consideration.
	if( this != &RHS ){

		for(int Index=0; Index<QWORDLength; Index++)
			this->NumberCell[Index] = RHS.NumberCell[Index];

		}

	return *this;

	}



// Move assignment.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator=(LargeInteger<BitLength>&& RHS){

	// Skip self-assignment. Corretness consideration.
	if( this != &RHS ){

		operator delete (this->NumberCell);
		(this->NumberCell) = RHS.NumberCell;
		RHS.NumberCell     = 0;

		}

	return *this;

	}



// Assignment.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator=(QWORD Number){

	NumberCell[0] = Number;

	for(int Index=1; Index<QWORDLength; Index++)
		NumberCell[Index] = 0;

	return *this;

	}



// Addition operation.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator+=(const LargeInteger<BitLength>& RHS){

	QWORD     AdditionResult = 0;
	DWORD*    DWORDNumber    = reinterpret_cast<DWORD*>(NumberCell);
	DWORD*    RHSDWORDNumber = reinterpret_cast<DWORD*>(RHS.NumberCell);
	const int ComputingEdge  = QWORDLength * 2;


	// Start to do addition operation.
	for(int Index=0; Index<ComputingEdge; Index++){


		// Unrolling this loop by doing two computation during one iteration.
		// Loop-unrolling - the first iteration.
		AdditionResult += DWORDNumber[Index];
		AdditionResult += RHSDWORDNumber[Index];

		DWORDNumber[Index] = static_cast<DWORD>(AdditionResult);

		AdditionResult >>= 32;
		Index++;


		// Loop-unrolling - the second iteration.
		AdditionResult += DWORDNumber[Index];
		AdditionResult += RHSDWORDNumber[Index];

		DWORDNumber[Index] = static_cast<DWORD>(AdditionResult);

		AdditionResult >>= 32;

		}

	return *this;

	}



// Subtraction operation.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator-=(const LargeInteger<BitLength>& RHS){

	// Use signed integer to do computaion.
	INT64     SubtractionResult = 0;
	DWORD*    DWORDNumber       = reinterpret_cast<DWORD*>(NumberCell);
	DWORD*    RHSDWORDNumber    = reinterpret_cast<DWORD*>(RHS.NumberCell);
	const int ComputingEdge     = QWORDLength * 2;


	// Start to do subtraction operation.
	for(int Index=0; Index<ComputingEdge; Index++){


		// Unrolling this loop by doing two computation during one iteration.
		// Loop-unrolling - the first iteration.
		SubtractionResult += DWORDNumber[Index];
		SubtractionResult -= RHSDWORDNumber[Index];

		DWORDNumber[Index] = static_cast<DWORD>(SubtractionResult);

		SubtractionResult >>= 32;
		Index++;


		// Loop unrolling - the second iteration.
		SubtractionResult += DWORDNumber[Index];
		SubtractionResult -= RHSDWORDNumber[Index];

		DWORDNumber[Index] = static_cast<DWORD>(SubtractionResult);

		SubtractionResult >>= 32;

		}

	return *this;

	}



// Multiplication operation.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator*=(const LargeInteger<BitLength>& RHS){

	LargeInteger<BitLength> Result        (               0);
	LargeInteger<BitLength> NumberToAdd   (           *this);
	const int               ComputingEdge = QWORDLength * 64;
	const QWORD             BitMask       = 1;
	int                     NumberToShift = 0;


	// Using addition operation to compute multiplication.
	for(int Index=0; Index<ComputingEdge; Index++){

		// Binary multiplication.
		if( RHS.NumberCell[Index/64] & ( BitMask<<(Index%64) ) ){

			NumberToAdd <<= NumberToShift;
			Result       += NumberToAdd;
			NumberToShift = 0;

			}

		NumberToShift++;

		}

	(*this) = static_cast< LargeInteger<BitLength>&& >(Result);

	return *this;

	}



// Division operation.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator/=(const LargeInteger<BitLength>& RHS){

	// Division-by-zero.
	if( !static_cast<bool>(RHS) )
		throw DIVISION_BY_ZERO;


	// Valid divisor.
	LargeInteger<BitLength> Divisor      (RHS);
	LargeInteger<BitLength> Result       (  0);
	int                     OffsetCounter(  0);
	QWORD                   BitMask           ;


	// Search for the left-most bit 1.
	for(int Index=QWORDLength-1; Index>=0; Index--){

		if( Divisor.NumberCell[Index] ){
			
			BitMask=0x8000000000000000llu;

			while( !( BitMask & Divisor.NumberCell[Index] ) ){

				OffsetCounter++;
				BitMask >>= 1;

				}

			break;

			}

		OffsetCounter += 64;

		}

	Divisor <<= OffsetCounter;
	BitMask   = 1;


	// Binary approximation.
	do{

		if( (*this) >= Divisor ){

			Result.NumberCell[OffsetCounter/64]|=(BitMask<<(OffsetCounter%64));
			(*this) -= Divisor;

			}
		
		Divisor >>= 1;
		OffsetCounter--;

		}while( OffsetCounter >= 0 );

	(*this) = static_cast< LargeInteger<BitLength>&& >(Result);

	return (*this);	

	}



// Modulo operation. Almost the same as division operation.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator%=(const LargeInteger<BitLength>& RHS){

	// Modulo-by-zero.
	if( !static_cast<bool>(RHS) )
		throw MODULO_BY_ZERO;


	// Valid divisor.
	LargeInteger<BitLength> Divisor      (RHS);
	int                     OffsetCounter(  0);


	// Search for the left-most bit 1.
	for(int Index=QWORDLength-1; Index>=0; Index--){

		if( Divisor.NumberCell[Index] ){
			
			QWORD BitMask = 0x8000000000000000llu;
			
			while( !( BitMask & Divisor.NumberCell[Index] ) ){

				OffsetCounter++;
				BitMask >>= 1;

				}

			break;

			}

		OffsetCounter += 64;

		}

	Divisor <<= OffsetCounter;

	// Binary approximation.
	do{

		if( (*this) >= Divisor ){

			(*this) -= Divisor;

			}
		
		Divisor>>=1;
		OffsetCounter--;

		}while( OffsetCounter >= 0 );

	return (*this);

	}



// Positive.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator+() const{

	return (*this);

	}



// Negative.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator-() const{

	LargeInteger<BitLength> Result(0);

	Result -= (*this);

	return Result;

	}



// Increment.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator++(){

	int Index=0;

	for(Index=0; Index<QWORDLength; Index++){

		if( NumberCell[Index] == 0xffffffffffffffffllu )
			NumberCell[Index]=0;
		else
			break;

		}

	if( Index < QWORDLength )
		NumberCell[Index]++;

	return *this;

	}



// Increment.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator++(int){

	LargeInteger<BitLength> Result(*this);

	++(*this);

	return Result;

	}



// Decrement.
template<size_t BitLength>
LargeInteger<BitLength>& LargeInteger<BitLength>::operator--(){

	int Index = 0;

	for(Index=0; Index<QWORDLength; Index++){

		if( NumberCell[Index] == 0 )
			NumberCell[Index] = 0xffffffffffffffffllu;
		else
			break;

		}

	if(Index<QWORDLength)
		NumberCell[Index]--;

	return *this;

	}



// Decrement.
template<size_t BitLength>
LargeInteger<BitLength> LargeInteger<BitLength>::operator--(int){

	LargeInteger<BitLength> Result(*this);

	--(*this);

	return Result;

	}



// Other member function.

// Copy data from this object into a buffer without casting.
template<size_t BitLength>
void LargeInteger<BitLength>::GetRawData(void* OutputDataBuffer) const{

	char*       PtrOutputBuffer = reinterpret_cast<      char*>(OutputDataBuffer);
	const char* PtrThisBuffer   = reinterpret_cast<const char*>(      NumberCell);
	const int   CopyEdge        = QWORDLength * 8;


	// Copy byte-by-byte to avoid alignment problem.
	for(int Index=0; Index<CopyEdge; Index++)
		PtrOutputBuffer[Index] = PtrThisBuffer[Index];

	}



// Copy data into this object without casting.
template<size_t BitLength>
void LargeInteger<BitLength>::SetRawData(const void* InputDataBuffer){

	char*        PtrThisBuffer  = reinterpret_cast<      char*>(     NumberCell);
	const char*  PtrInputBuffer = reinterpret_cast<const char*>(InputDataBuffer);
	const int    CopyEdge       = QWORDLength * 8;


	// Copy byte-by-byte to avoid alignment problem.
	for(int Index=0; Index<CopyEdge; Index++)
		PtrThisBuffer[Index] = PtrInputBuffer[Index];

	}



// Convert the data into specified radix.
template<size_t BitLength>
const char* LargeInteger<BitLength>::ConvertToString(unsigned int Radix) const{

	// Invalid radix.
	if( Radix<2 || Radix>36 )
		throw INVALID_RADIX;


	// Buffer to store the output string.
	static char StrOutputNumber[ (QWORDLength*64) +1 ];


	switch(Radix){

		// 2^n cases.
		case  2:
		case  4:
		case  8:
		case 16:
		case 32:

			PowerOfTwoConvertToString(Radix, StrOutputNumber);
			break;

		// Regular case.
		default:

			RegularConvertToString(Radix, StrOutputNumber);
			break;
		
		}

	return StrOutputNumber;

	}



// Set number from a c-style string.
template<size_t BitLength>
void LargeInteger<BitLength>::SetFromString(const char* StrNumber, unsigned int Radix){

	// Invalid radix.
	if( Radix<2 || Radix>36 )
		throw INVALID_RADIX;


	switch(Radix){

		// 2^n cases.
		case  2:
		case  4:
		case  8:
		case 16:
		case 32:
		
			PowerOfTwoSetFromString(StrNumber, Radix);
			break;

		// Regular cases.
		default:
			
			RegularSetFromString(StrNumber, Radix);
			break;

		}

	}



// Return the size of the data buffer.
template<size_t BitLength>
size_t LargeInteger<BitLength>::GetBufferSize(void) const{

	return (QWORDLength * 8);

	}



// Convert the data into specified radix - using regular algorithm.
template<size_t BitLength>
void LargeInteger<BitLength>::RegularConvertToString(unsigned int Radix, char* StrToWrite) const{

	// No check for invalid radix.
	int         RemainNumberIndex  = 0;
	int         FixedOffsetCounter = (QWORDLength-1) * 64;
	int         OffsetCounter;
	int         StringIndex        = 0;
	int         Power              = 1;
	QWORD       ShiftedSuperRadix  = FindSuperRadix(Radix, &Power);
	QWORD       BitMask            = 0x8000000000000000llu;

	// RemainNumber store the dividend and the remainder in turn.
	LargeInteger<BitLength> RemainNumber[2] = {*this, 0};
	LargeInteger<BitLength> Divisor;


	// Shift the divisor left-most bit 1.
	// Search for the left-most bit 1.
	// The radix must small enough to store in one QWORD.
	while( !( BitMask & ShiftedSuperRadix ) ){

		FixedOffsetCounter++;
		ShiftedSuperRadix <<= 1;

		}


	// Get the remainder of the super radix.
	do{

		// Prepare for this round.
		OffsetCounter = FixedOffsetCounter;
		BitMask       = 1;

		for(int Index=0; Index < (QWORDLength-1); Index++)
			Divisor.NumberCell[Index]=0;

		Divisor.NumberCell[QWORDLength-1] = ShiftedSuperRadix;



		// Binary approximation.
		do{

			if( RemainNumber[RemainNumberIndex] >= Divisor ){

				RemainNumber[1-RemainNumberIndex].NumberCell[OffsetCounter/64]|=(BitMask<<(OffsetCounter%64));
				RemainNumber[  RemainNumberIndex] -= Divisor;

				}

			Divisor >>= 1;
			OffsetCounter--;

			}while( OffsetCounter >= 0 );


		// Remainder must not over the range of QWORD, using ragular operation
		// of QWORD to speed up the process of converting a number into a string.
		for(int Index=0; Index<Power; Index++){
			
			StrToWrite[StringIndex] = NumberToChar( RemainNumber[RemainNumberIndex].NumberCell[0] % Radix );
			StringIndex++;
			(RemainNumber[RemainNumberIndex].NumberCell[0])/=Radix;

			}


		// Prepare for the next round.
		RemainNumberIndex = 1-RemainNumberIndex;


		}while( static_cast<bool>(RemainNumber[RemainNumberIndex]) );


	// Kill the useless zero.
	while(StrToWrite[StringIndex-1]=='0' && StringIndex>1)
		StringIndex--;

	// Zero terminator.
	StrToWrite[StringIndex] = 0;

	// Reverse the string stored in the string buffer.
	ReverseString(StrToWrite, StringIndex);

	}



// Convert the data into 2^n radix - using faster algorithm.
template<size_t BitLength>
void LargeInteger<BitLength>::PowerOfTwoConvertToString(unsigned int Radix, char* StrToWrite) const{

	// No check for the radix.
	LargeInteger<BitLength> NumberToConvert(*this);
	QWORD TmpNumber;
	QWORD FilterMask = Radix - 1;
	int   StrIndex   = 0;
	int   Power;
	int   QWORDShiftUnit;
	int   LargeIntegerShiftUnit;


	FindSuperRadix(Radix, &Power);


	// Compute the power of 2 which Radix is.
	for(QWORDShiftUnit=1; (Radix>>QWORDShiftUnit)!=1; QWORDShiftUnit++);

	LargeIntegerShiftUnit = Power * QWORDShiftUnit;


	do{

		TmpNumber = NumberToConvert.NumberCell[0];

		for(int Index=0; Index<Power; Index++){

			StrToWrite[StrIndex] = NumberToChar(TmpNumber & FilterMask);
			StrIndex++;
			TmpNumber >>= QWORDShiftUnit;
			
			}

		NumberToConvert >>= LargeIntegerShiftUnit;
		
		}while( static_cast<bool>(NumberToConvert) );


	// Kill the useless zero.
	while(StrToWrite[StrIndex-1]=='0' && StrIndex>1)
		StrIndex--;

	// Zero terminator.
	StrToWrite[StrIndex] = 0;

	ReverseString(StrToWrite, StrIndex);

	}



// Set this object via a string - using regular algorithm.
template<size_t BitLength>
void LargeInteger<BitLength>::RegularSetFromString(const char* StrNumber, unsigned int Radix){
	
	// No chaeck for the radix.
	QWORD TempNumber          = 0;
	QWORD MultiplyBase        = 0;
	int   StrIndex            = 0;
	int   Digit               = 0;
	int   SuperRadixPower     = 0;


	(*this) = 0;
	FindSuperRadix(Radix, &SuperRadixPower);


	// Main loop traversing the string.
	while( StrNumber[StrIndex] ){

		// Initialize the variables.
		MultiplyBase = 1;
		TempNumber   = 0;

		// Loop until reach the super radix bound.
		for(int Index=0; Index<SuperRadixPower && StrNumber[StrIndex]!=0; Index++){

			Digit = CharToNumber(StrNumber[StrIndex], Radix);

			TempNumber    = (TempNumber*Radix) + static_cast<QWORD>(Digit);
			MultiplyBase *= Radix;
			StrIndex++;

			}

		(*this) *= MultiplyBase;
		(*this) += TempNumber;

		}


	}



// Set this object via a string - using faster algorithm.
template<size_t BitLength>
void LargeInteger<BitLength>::PowerOfTwoSetFromString(const char* StrNumber, unsigned int Radix){
	
	// No chaeck for the radix.
	QWORD TempNumber          = 0;
	int   StrIndex            = 0;
	int   ShiftUnit           = 1;
	int   Digit               = 0;
	int   SuperRadixPower     = 0;
	int   NumberOfBitsToShift = 0;


	(*this) = 0;
	FindSuperRadix(Radix, &SuperRadixPower);

	for(ShiftUnit=1; (Radix>>ShiftUnit)!=1; ShiftUnit++);


	// Main loop traversal the string.
	while( StrNumber[StrIndex] ){

		// Initialize the variables.
		NumberOfBitsToShift = 0;
		TempNumber          = 0;

		// Loop until reach the super radix bound.
		for(int Index=0; Index<SuperRadixPower && StrNumber[StrIndex]!=0; Index++){

			Digit = CharToNumber(StrNumber[StrIndex], Radix);

			TempNumber = (TempNumber<<ShiftUnit) | static_cast<QWORD>(Digit);
			NumberOfBitsToShift += ShiftUnit;
			StrIndex++;

			}

		(*this)<<=NumberOfBitsToShift;
		this->NumberCell[0] |= TempNumber;

		}
	
	
	}





// Operator definitions.

// Arthematic operator: operator+
// Lvalue + Lvalue
template<size_t Length>
LargeInteger<Length> operator+(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result+=RHS;

	return Result;

	}



// Lvalue + Rvalue
template<size_t Length>
LargeInteger<Length>&& operator+(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	RHS+=LHS;

	return static_cast< LargeInteger<Length>&& >(RHS);

	}



// Rvalue + Lvalue
template<size_t Length>
LargeInteger<Length>&& operator+(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS+=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue + Rvalue
template<size_t Length>
LargeInteger<Length>&& operator+(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS+=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Arthematic operator: operator-
// Lvalue - Lvalue
template<size_t Length>
LargeInteger<Length> operator-(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result-=RHS;

	return Result;

	}



// Lvalue - Rvalue
template<size_t Length>
LargeInteger<Length> operator-(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	LargeInteger<Length> Result(LHS);

	Result-=RHS;

	return Result;

	}



// Rvalue - Lvalue
template<size_t Length>
LargeInteger<Length>&& operator-(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS-=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue - Rvalue
template<size_t Length>
LargeInteger<Length>&& operator-(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS-=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Arthematic operator: operator*
// Lvalue * Lvalue
template<size_t Length>
LargeInteger<Length> operator*(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result*=RHS;

	return Result;

	}



// Lvalue * Rvalue
template<size_t Length>
LargeInteger<Length>&& operator*(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	RHS*=LHS;

	return static_cast< LargeInteger<Length>&& >(RHS);

	}



// Rvalue * Lvalue
template<size_t Length>
LargeInteger<Length>&& operator*(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS*=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue * Rvalue
template<size_t Length>
LargeInteger<Length>&& operator*(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS*=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Arthematic operator: operator/
// Lvalue / Lvalue
template<size_t Length>
LargeInteger<Length> operator/(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result/=RHS;

	return Result;

	}



// Lvalue / Rvalue
template<size_t Length>
LargeInteger<Length> operator/(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	LargeInteger<Length> Result(LHS);

	Result/=RHS;

	return Result;

	}



// Rvalue / Lvalue
template<size_t Length>
LargeInteger<Length>&& operator/(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS/=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue / Rvalue
template<size_t Length>
LargeInteger<Length>&& operator/(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS/=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Arthematic operator: operator%
// Lvalue % Lvalue
template<size_t Length>
LargeInteger<Length> operator%(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result%=RHS;

	return Result;

	}



// Lvalue % Rvalue
template<size_t Length>
LargeInteger<Length> operator%(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	LargeInteger<Length> Result(LHS);

	Result%=RHS;

	return Result;

	}



// Rvalue % Lvalue
template<size_t Length>
LargeInteger<Length>&& operator%(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS%=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue % Rvalue
template<size_t Length>
LargeInteger<Length>&& operator%(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS%=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Bitwise operator: operator&
// Lvalue & Lvalue
template<size_t Length>
LargeInteger<Length> operator&(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result&=RHS;

	return Result;

	}



// Lvalue & Rvalue
template<size_t Length>
LargeInteger<Length>&& operator&(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	RHS&=LHS;

	return static_cast< LargeInteger<Length>&& >(RHS);

	}



// Rvalue & Lvalue
template<size_t Length>
LargeInteger<Length>&& operator&(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS&=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue & Rvalue
template<size_t Length>
LargeInteger<Length>&& operator&(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS&=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Bitwise operator: operator|
// Lvalue | Lvalue
template<size_t Length>
LargeInteger<Length> operator|(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result|=RHS;

	return Result;

	}



// Lvalue | Rvalue
template<size_t Length>
LargeInteger<Length>&& operator|(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	RHS|=LHS;

	return static_cast< LargeInteger<Length>&& >(RHS);

	}



// Rvalue | Lvalue
template<size_t Length>
LargeInteger<Length>&& operator|(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS|=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue | Rvalue
template<size_t Length>
LargeInteger<Length>&& operator|(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS|=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Bitwise operator: operator^
// Lvalue ^ Lvalue
template<size_t Length>
LargeInteger<Length> operator^(const LargeInteger<Length>& LHS, const LargeInteger<Length>& RHS){

	LargeInteger<Length> Result(LHS);

	Result^=RHS;

	return Result;

	}



// Lvalue ^ Rvalue
template<size_t Length>
LargeInteger<Length>&& operator^(const LargeInteger<Length>& LHS, LargeInteger<Length>&& RHS){

	RHS^=LHS;

	return static_cast< LargeInteger<Length>&& >(RHS);

	}



// Rvalue ^ Lvalue
template<size_t Length>
LargeInteger<Length>&& operator^(LargeInteger<Length>&& LHS, const LargeInteger<Length>& RHS){

	LHS^=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}



// Rvalue ^ Rvalue
template<size_t Length>
LargeInteger<Length>&& operator^(LargeInteger<Length>&& LHS, LargeInteger<Length>&& RHS){

	LHS^=RHS;

	return static_cast< LargeInteger<Length>&& >(LHS);

	}





#endif
