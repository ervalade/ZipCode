/*
 * BarCode.h
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#ifndef BARCODE_H_
#define BARCODE_H_
#include <ZipCode.h>
#include <array>
#include <map>

enum class Code {
	one = 0b00011,
	two = 0b00101,
	three = 0b00110,
	four = 0b01001,
	five = 0b01010,
	six = 0b01100,
	seven = 0b10001,
	eight = 0b10010,
	nine = 0b10100,
	zero = 0b11000
};
class BarCode {

private:
	std::array<Code, ZipCode::LENGTH+1> value;//+1 for zip code key
	static const std::map<int, Code> convert;

public:
	BarCode(ZipCode zipCode);
	virtual ~BarCode();
	const std::array<Code, 5>& getValue() const;
	void setValue(const std::array<Code, 5> &value);

};

#endif /* BARCODE_H_ */
