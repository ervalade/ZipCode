/*
 * BarCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <BarCode.h>

const std::map<int, Code> BarCode::convert = { { 1, Code::one },
		{ 2, Code::two }, { 3, Code::three }, { 4, Code::four },
		{ 5, Code::five }, { 6, Code::six }, { 7, Code::seven }, { 8,
				Code::eight }, { 9, Code::nine }, { 0, Code::zero } };

BarCode::BarCode(ZipCode zipCode) {
	//convert ZipCode to value : 95014 ->> 0b10100, 0b01010 ,....
	//1; 379
// 9, 5,0,1,4
	//9 -> 10000,...
	//1000,100,10,1
	for (int i = 0; i < ZipCode::LENGTH; i++) {///  0
		this->value.at(i) = BarCode::convert.at(zipCode.at(i));
	}
	this->value[this->value.size()] =BarCode::convert.at(zipCode.getKey());
	//*(this->value.end()) =BarCode::convert.at(zipCode.getKey());

}

const std::array<Code, 5>& BarCode::getValue() const {
return value;
}

void BarCode::setValue(const std::array<Code, 5> &value) {
this->value = value;
}

BarCode::~BarCode() {
// TODO Auto-generated destructor stub
}

