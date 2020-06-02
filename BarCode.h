/*
 * BarCode.h
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#ifndef BARCODE_H_
#define BARCODE_H_
#include <vector>
#include <map>
#include <ZipCode.h>

#include <bitset>
class BarCode {
public:
	enum class Code {
		//      74210
		one = 0b00011,
		two = 0b00101,
		three = 0b00110,
		four = 0b01001,
		five = 0b01010,
		six = 0b01100,
		seven = 0b10001,
		eight = 0b10010,
		nine = 0b10100,
		zero = 0b11000,
		nb_bits = 5, // used for operator<< to determine bitset length
	};
	static const std::array<int,(int)BarCode::Code::nb_bits> BIT_WEIGHTS;//for conversion to ZipCode
	//vector instead of array => no direct dependency with  ZipCode length
	using Codes=std::vector<BarCode::Code>; //modern C++ style to replace typedef
	static const std::string INVALID_CODE_MSG;
	static const std::map< BarCode::Code,ZipCode::Digit> CONVERT_CODE_TO_DIGIT;

private:
	BarCode::Codes value;//CONVERT_DIGIT_TO_CODE  CONVERT_STRING_TO_CODE
	static const std::map<ZipCode::Digit, BarCode::Code> CONVERT_DIGIT_TO_CODE; //static-> défini une seule fois appelée variable (attribut) de classe
	static const std::map<std::string, BarCode::Code> CONVERT_STRING_TO_CODE;
	static const char BEGIN_CHAR;
	static const char END_CHAR;
	static const char SEPARATOR_CHAR;

public:
	BarCode(const ZipCode& zipCode);
	BarCode(std::string barCode);
	virtual ~BarCode();
	friend std::ostream& operator<<(std::ostream &os, BarCode &b);
	const BarCode::Codes& getValue() const;
	static BarCode::Code getKey(const ZipCode zipCode); //static-> défini une seule fois appelée méthode de classe

private:
	static bool isSeparator(char c);
};

#endif /* BARCODE_H_ */
