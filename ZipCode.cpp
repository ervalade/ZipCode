/*
 * ZipCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <BarCode.h>
#include <ZipCode.h>
#include <cmath>//pow() : added automatically, right clic, source, Organize includes
#include <stdexcept>

const std::string ZipCode::OUT_OF_RANGE_MSG = "zip code MUST be between 1 and "
		+ std::to_string((int) pow(10, ZipCode::LENGTH) - 1);
const std::map<int, ZipCode::Digit> ZipCode::CONVERT_NUMBER_TO_CODE = { { 1,
		ZipCode::Digit::one }, { 2, ZipCode::Digit::two }, { 3,
		ZipCode::Digit::three }, { 4, ZipCode::Digit::four }, { 5,
		ZipCode::Digit::five }, { 6, ZipCode::Digit::six }, { 7,
		ZipCode::Digit::seven }, { 8, ZipCode::Digit::eight }, { 9,
		ZipCode::Digit::nine }, { 0, ZipCode::Digit::zero } };
//const int ZipCode::LENGTH = 5;

ZipCode::ZipCode(const unsigned int zipValue) { //liste d'initialisation
	if (zipValue < 1 || zipValue >= pow(10, this->value.size()))
		throw std::domain_error(ZipCode::OUT_OF_RANGE_MSG);
	int value(zipValue);
	/*
	 for (size_t i(0), unit(pow(10, this->value.size() - 1));
	 i < this->value.size(); i++, unit /= 10) {
	 this->value.at(i) = ZipCode::convert.at(value / unit);
	 value %= unit;
	 }
	 */
	unsigned int rank(pow(10, this->value.size() - 1));
	for (auto &digit : this->value) {
		digit = ZipCode::CONVERT_NUMBER_TO_CODE.at(value / rank);
		value %= rank;
		rank /= 10;	//next rang
	}
}

ZipCode::~ZipCode() {
	// TODO Auto-generated destructor stub
}

const ZipCode::Digits& ZipCode::getValue() const {
	return value;
}
/* operator << as member : friend not needed
 std::ostream & ZipCode::operator<<(std::ostream & os) {
 for (int i(0); i < this->value.size(); ++i) {
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

ZipCode::ZipCode(const BarCode &barCode) {
/**/
	for (size_t i(0); i < this->value.size(); i++) {
		this->value.at(i) = BarCode::CONVERT_CODE_TO_DIGIT.at(
				barCode.getValue().at(i));
	}
	if (BarCode::getKey(*this) != *(barCode.getValue().end()))
		throw std::domain_error(BarCode::INVALID_CODE_MSG);
/**/
	/*
	for (size_t i(0); i < this->value.size(); i++) {
		int digit(0);
		std::bitset<(int) BarCode::Code::nb_bits> codeBits(
				(int) barCode.getValue().at(i));
		for (size_t b(0); i < codeBits.size(); b++) {
			digit+= codeBits[b] * BarCode::BIT_WEIGHTS.at(b);
		}
		this->value.at(i)=ZipCode::Digit(digit);
	}
	*/
}

#define _ZIPCODE_UT_ //only to enable source, format, don't forget to comment in
#ifdef _ZIPCODE_UT_
/*
 g++ -D _ZIPCODE_UT_ -o ZipCodeUt BarCode.cpp ZipCode.cpp -std=c++14 -I ./ && ./ZipCodeUt
 */
#include <iostream>//std::cout
#include <sstream>//std::ostringstream
#include <string>
#include <map>
#include <cassert>//assert
#include <iomanip>
int main(int argc, char **argv) {
	{
		std::cout << "ZipCode constructor ZipCode(int) Test -----------------"
				<< std::endl;
		std::map<int, ZipCode::Digits> testCases = { //
				{ 1, { ZipCode::Digit::zero, ZipCode::Digit::zero,
						ZipCode::Digit::zero, ZipCode::Digit::zero,
						ZipCode::Digit::one } }, //
						{ 12, { ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::zero, ZipCode::Digit::one,
								ZipCode::Digit::two } },  //
						{ 123, { ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::one, ZipCode::Digit::two,
								ZipCode::Digit::three } }, //
						{ 1234, { ZipCode::Digit::zero, ZipCode::Digit::one,
								ZipCode::Digit::two, ZipCode::Digit::three,
								ZipCode::Digit::four } },  //
						{ 12345, { ZipCode::Digit::one, ZipCode::Digit::two,
								ZipCode::Digit::three, ZipCode::Digit::four,
								ZipCode::Digit::five } }, //
						{ 6789, { ZipCode::Digit::zero, ZipCode::Digit::six,
								ZipCode::Digit::seven, ZipCode::Digit::eight,
								ZipCode::Digit::nine } }, //
						{ 99999, { ZipCode::Digit::nine, ZipCode::Digit::nine,
								ZipCode::Digit::nine, ZipCode::Digit::nine,
								ZipCode::Digit::nine } }, //
						{ 0, { ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::zero } }, // exception
						{ 100000, { ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::zero, ZipCode::Digit::zero,
								ZipCode::Digit::zero } } //exception
				};
		for (auto &testCase : testCases) {
			try {
				std::cout << "Test stimuli : " << std::setw(ZipCode::LENGTH + 1)
						<< testCase.first << std::endl;
				ZipCode zipCode(testCase.first);
				assert(zipCode.getValue() == testCase.second);
			} catch (const std::domain_error &e) {
				assert(e.what() == ZipCode::OUT_OF_RANGE_MSG);
			}
		}
	}

	{
		std::cout << "ZipCode operator << Test -----------------" << std::endl;
		std::map<int, std::string> testCases = { //
				{ 1, "00001" }, //
						{ 12, "00012" }, //
						{ 123, "00123" }, //
						{ 1234, "01234" }, //
						{ 12345, "12345" }, //
						{ 6789, "06789" }, //
						{ 99999, "99999" } //
				};
		for (auto &testCase : testCases) {
			std::cout << "Test stimuli : " << std::setw(ZipCode::LENGTH + 1)
					<< testCase.first << std::endl;
			ZipCode zipCode(testCase.first);
			//zipCode.operator<<(std::cout);// operator << as member  : friend not needed
			//	std::cout << zipCode << std::endl;
			std::ostringstream oss;
			oss << zipCode;
			assert(oss.str() == testCase.second);
		}
	}
	{
		std::map<std::string, ZipCode::Digits> testCases = { //
				{ "1 11000 01100 10001 10010 10100 11000 1", {
						ZipCode::Digit::zero, ZipCode::Digit::six,
						ZipCode::Digit::seven, ZipCode::Digit::eight,
						ZipCode::Digit::nine } }, {
						"1 00011 00101 00110 01001 01010 01010 1", {
								ZipCode::Digit::one, ZipCode::Digit::two,
								ZipCode::Digit::three, ZipCode::Digit::four,
								ZipCode::Digit::five } }, {
						"1 11000 01100 10001 10010 10100 10100 1", { //exception wrong key
						ZipCode::Digit::zero, ZipCode::Digit::six,
								ZipCode::Digit::seven, ZipCode::Digit::eight,
								ZipCode::Digit::nine } } };
		std::cout
				<< "ZipCode constructor ZipCode(BarCode) Test -----------------"
				<< std::endl;
		for (auto &testCase : testCases) {
			try {
				std::cout << "Test stimuli : " << testCase.first << std::endl;
				//BarCode barCode(ZipCode(testCase.first));
				ZipCode zipCode(BarCode(testCase.first));
				assert(zipCode.getValue() == testCase.second);
			} catch (const std::domain_error &e) {
				assert(e.what() == BarCode::INVALID_CODE_MSG);
			}
		}
	}
	return 0;
}

#endif
