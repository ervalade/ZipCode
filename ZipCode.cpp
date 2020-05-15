/*
 * ZipCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <ZipCode.h>
#include <cmath>//pow() : added automatically, right clic, source, Organize includes
#include <string>
const std::string ZipCode::OUT_OF_RANGE_MSG = "zip code MUST be between 1 and 99999";
//	+ ((int) pow(10, ZipCode::LENGTH) - 1);

const std::map<int, Digit> ZipCode::convert = { { 1, Digit::one }, { 2,
		Digit::two }, { 3, Digit::three }, { 4, Digit::four },
		{ 5, Digit::five }, { 6, Digit::six }, { 7, Digit::seven }, { 8,
				Digit::eight }, { 9, Digit::nine }, { 0, Digit::zero } };
//const int ZipCode::LENGTH = 5;

ZipCode::ZipCode(const unsigned int zipValue) { //liste d'initialisation
	//convert int to std::array<Digit,5>
	//1000
	if (zipValue < 1 || zipValue >= pow(10, this->value.size()))
		throw ZipCode::OUT_OF_RANGE_MSG;
	int value = zipValue;
	/*
	 for (size_t i(0), unit(pow(10, this->value.size() - 1));
	 i < this->value.size(); i++, unit /= 10) {
	 this->value.at(i) = ZipCode::convert.at(value / unit);
	 value %= unit;
	 }
	 */
	unsigned int rank = pow(10, this->value.size() - 1);
	for (auto &digit : this->value) {
		digit = ZipCode::convert.at(value / rank);
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

const int ZipCode::getDigitNumber() const {
	return (int) this->value.size();
}

//#define _ZIPCODE_UT_ //only to enable source, format, don't forget to comment in
#ifdef _ZIPCODE_UT_
/*
 g++ -D _ZIPCODE_UT_ -o ZipCodeUt ZipCode.cpp -std=c++14 -I ./ && ./ZipCodeUt
 */
#include <iostream>//std::cout
#include <sstream>//std::ostringstream
#include <string>
#include <map>
#include <cassert>//assert
#include <iomanip>
int main(int argc, char **argv) {
	{
		std::cout << "ZipCode constructor Test -----------------" << std::endl;
		std::map<int, ZipCode::Digits> testCases = { //
				{ 1, { Digit::zero, Digit::zero, Digit::zero, Digit::zero,
						Digit::one } }, //
						{ 12, { Digit::zero, Digit::zero, Digit::zero,
								Digit::one, Digit::two } },  //
						{ 123, { Digit::zero, Digit::zero, Digit::one,
								Digit::two, Digit::three } }, //
						{ 1234, { Digit::zero, Digit::one, Digit::two,
								Digit::three, Digit::four } },  //
						{ 12345, { Digit::one, Digit::two, Digit::three,
								Digit::four, Digit::five } }, //
						{ 6789, { Digit::zero, Digit::six, Digit::seven,
								Digit::eight, Digit::nine } }, //
						{ 99999, { Digit::nine, Digit::nine, Digit::nine,
								Digit::nine, Digit::nine } }, //
						{ 0, { Digit::zero, Digit::zero, Digit::zero,
								Digit::zero, Digit::zero } }, // exception
						{ 100000, { Digit::zero, Digit::zero, Digit::zero,
								Digit::zero, Digit::zero } } //exception
				};
		for (auto &testCase : testCases) {
			try {
				std::cout << "Test stimuli : " << std::setw(ZipCode::LENGTH + 1)
						<< testCase.first << std::endl;
				ZipCode zipCode(testCase.first);
				assert(zipCode.getValue() == testCase.second);
			} catch (const std::string &e) {
				assert(e == ZipCode::OUT_OF_RANGE_MSG);
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
						{ 99999, "99999" }, //
						{ 0, ZipCode::OUT_OF_RANGE_MSG }, //
						{ 100000, ZipCode::OUT_OF_RANGE_MSG } //

				};
		for (auto &testCase : testCases) {
			try {
				std::cout << "Test stimuli : " << std::setw(ZipCode::LENGTH + 1)
						<< testCase.first << std::endl;
				ZipCode zipCode(testCase.first);
				//zipCode.operator<<(std::cout);// operator << as member  : friend not needed
				//	std::cout << zipCode << std::endl;
				std::ostringstream oss;
				oss << zipCode;
				assert(oss.str() == testCase.second);
			} catch (const std::string &e) {
				assert(e == testCase.second);
			}
		}
	}
	return 0;
}

#endif
