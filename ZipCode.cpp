/*
 * ZipCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <ZipCode.h>
const std::map<int, Digit> ZipCode::convert = { { 1, Digit::one }, { 2,
		Digit::two }, { 3, Digit::three }, { 4, Digit::four },
		{ 5, Digit::five }, { 6, Digit::six }, { 7, Digit::seven }, { 8,
				Digit::eight }, { 9, Digit::nine }, { 0, Digit::zero } };
//const int ZipCode::LENGTH = 5;

ZipCode::ZipCode(const unsigned int zipValue) { //liste d'initialisation
	//convert int to std::array<Digit,5>
	//1000
	if (zipValue < 1 || zipValue > 99999)
		throw std::string("zip code MUST be between 1 and 99999");
	int value = zipValue;
	for (int i = 0, unit = 10000; i < ZipCode::LENGTH; i++, unit /= 10) {
		this->value.at(i) = ZipCode::convert.at(value / unit);
		value %= unit;
	}
}

ZipCode::~ZipCode() {
	// TODO Auto-generated destructor stub
}

const std::array<Digit, ZipCode::LENGTH>& ZipCode::getValue() const {
	return value;
}
/* operator << as member : friend not needed
 std::ostream & ZipCode::operator<<(std::ostream & os) {
 for (int i = 0; i < ZipCode::LENGTH; ++i) {
 os << (int)this->value.at(i);
 }
 return os;
 }
 */
std::ostream& operator<<(std::ostream &os, const ZipCode &z) {
	//z.operator <<(os);// operator << as member  : friend not needed
	for (auto &digit : z.getValue()) {
		os << (int) digit;
	}
	return os;
}

#ifdef _ZIPCODE_UT_
/*
g++ -D _ZIPCODE_UT_ -o ZipCodeUt ZipCode.cpp -std=c++14 -I ./ && ./ZipCodeUt
 */
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>

int main(int argc, char **argv) {
	std::map<int,std::string> testCases={
			{1,"00001"},
			{12,"00012"},
			{123,"00123"},
			{1234,"01234"},
			{12345,"12345"},
			{6789,"06789"},
			{99999,"99999"},
			{0,"zip code MUST be between 1 and 99999"},
			{100000,"zip code MUST be between 1 and 99999"}

	};
	for(auto const testCase:testCases){
		try{
		ZipCode zipCode(testCase.first);
	//zipCode.operator<<(std::cout);// operator << as member  : friend not needed
	//	std::cout << zipCode << std::endl;
		std::ostringstream oss;

		oss <<zipCode ;
	assert(oss.str()==testCase.second);
		}catch(const std::string& e){
			assert(e==testCase.second);
		}
	}
	return 0;
}

#endif
