/*
 * BarCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <BarCode.h>
#include <stddef.h>
#include <array>
#include <iterator>
#include <stdexcept>
#include <utility>

const std::map<ZipCode::Digit, BarCode::Code> BarCode::CONVERT_DIGIT_TO_CODE = {
		{ ZipCode::Digit::one, BarCode::Code::one }, { ZipCode::Digit::two,
				BarCode::Code::two }, { ZipCode::Digit::three,
				BarCode::Code::three }, { ZipCode::Digit::four,
				BarCode::Code::four }, { ZipCode::Digit::five,
				BarCode::Code::five }, { ZipCode::Digit::six, BarCode::Code::six }, {
				ZipCode::Digit::seven, BarCode::Code::seven }, {
				ZipCode::Digit::eight, BarCode::Code::eight }, {
				ZipCode::Digit::nine, BarCode::Code::nine }, {
				ZipCode::Digit::zero, BarCode::Code::zero } };
const std::array<int,(int)BarCode::Code::nb_bits>  BarCode::BIT_WEIGHTS={0,1,2,4,7};

//const std::array<int,(int)BarCode::Code::nb_bits>  BarCode::BIT_WEIGHTS={0,1,2,4,7};

const std::map<BarCode::Code, ZipCode::Digit> BarCode::CONVERT_CODE_TO_DIGIT = {
		{ BarCode::Code::one, ZipCode::Digit::one }, { BarCode::Code::two,
				ZipCode::Digit::two }, { BarCode::Code::three,
				ZipCode::Digit::three }, { BarCode::Code::four,
				ZipCode::Digit::four }, { BarCode::Code::five,
				ZipCode::Digit::five }, { BarCode::Code::six,
				ZipCode::Digit::six }, { BarCode::Code::seven,
				ZipCode::Digit::seven }, { BarCode::Code::eight,
				ZipCode::Digit::eight }, { BarCode::Code::nine,
				ZipCode::Digit::nine }, { BarCode::Code::zero,
				ZipCode::Digit::zero } };

BarCode::BarCode(const ZipCode &zipCode) :
		value( { 0 }) {
	for (auto &digit : zipCode.getValue()) {
		this->value.push_back(BarCode::CONVERT_DIGIT_TO_CODE.at(digit));
	}
	this->value.push_back(BarCode::getKey(zipCode));
}

BarCode::~BarCode() {
// TODO Auto-generated destructor stub
}
#include <numeric> //std::accumulate
#include <cmath> //modf

const BarCode::Codes& BarCode::getValue() const {
	return this->value;
}

BarCode::Code BarCode::getKey(const ZipCode zipCode) {
	zipCode.getValue();
	double sum =
	//calcul de la somme des  digits de zipCode
			std::accumulate((int*) (zipCode.getValue().begin()),
					(int*) (zipCode.getValue().end()), 0);
	double partieEntiere = 0.0;
	//récupération de la partie décimale (après la virgule)
	double partieDecimale = modf(sum / 10.0, &partieEntiere);
	//
	int cle = (int) (10.0 *
	//calcul du complément pour obtenir une unité
			(1.0 - partieDecimale)
	//ajouter 0.5 pour éviter arrondi valeur inférieurs lors du cast
			+ 0.5)
	//modulo 10 pour obtenir 0 si partie décimale =0
			% 10;
	return BarCode::CONVERT_DIGIT_TO_CODE.at((ZipCode::Digit) cle);
}

const std::string BarCode::INVALID_CODE_MSG = "Invalid code value";
const char BarCode::BEGIN_CHAR = '1';
const char BarCode::END_CHAR = '1';
const char BarCode::SEPARATOR_CHAR = ' ';

const std::map<std::string, BarCode::Code> BarCode::CONVERT_STRING_TO_CODE = { {
		"00011", BarCode::Code::one }, { "00101", BarCode::Code::two }, {
		"00110", BarCode::Code::three }, { "01001", BarCode::Code::four }, {
		"01010", BarCode::Code::five }, { "01100", BarCode::Code::six }, {
		"10001", BarCode::Code::seven }, { "10010", BarCode::Code::eight }, {
		"10100", BarCode::Code::nine }, { "11000", BarCode::Code::zero }, };

#include <algorithm> //std::remove_if
BarCode::BarCode(std::string barCode) {
	if (*barCode.begin() != BarCode::BEGIN_CHAR
			|| *(barCode.end() - 1) != BarCode::END_CHAR
			|| std::count(barCode.begin(), barCode.end(),
					BarCode::SEPARATOR_CHAR) != ZipCode::LENGTH + 2)
		throw std::domain_error(BarCode::INVALID_CODE_MSG);
	barCode.erase(
			std::remove_if(barCode.begin(), barCode.end(),
					BarCode::isSeparator), barCode.end());
	barCode.erase(barCode.begin());
	barCode.erase(barCode.end() - 1);
	try {
		for (size_t i(0); i < barCode.size(); i +=
				(size_t) BarCode::Code::nb_bits) {
			this->value.push_back(
					CONVERT_STRING_TO_CODE.at(
							barCode.substr(i,
									(size_t) BarCode::Code::nb_bits)));
			/* other solution
			 std::string grp=codeBarre.substr(i, (size_t)BarCode::Code::nb_bits);
			 if (std::count(grp.begin(),grp.end(),'1') !=2){
			 throw std::domain_error("bar code invalid");
			 }
			 this->value.push_back(BarCode::Code(std::stoi(grp,nullptr,2)));
			 */
		}
	} catch (std::out_of_range &e) {
		throw std::domain_error(BarCode::INVALID_CODE_MSG);
	}
}
#include <iomanip>
#include <bitset>
std::ostream& operator<<(std::ostream &os, BarCode &b) {
	os << BarCode::BEGIN_CHAR << BarCode::SEPARATOR_CHAR;
	for (auto &code : b.getValue()) {
		os << std::bitset<(int) BarCode::Code::nb_bits>((int) code)
				<< BarCode::SEPARATOR_CHAR;
	}
	os << BarCode::END_CHAR;
	return os;
}
bool BarCode::isSeparator(char c) {
	return c == BarCode::SEPARATOR_CHAR;
}
//#define _BARCODE_UT_ //only to enable completion and source, format, don't forget to comment in
#ifdef _BARCODE_UT_
/*
 g++ -D _BARCODE_UT_ -o BarCodeUt BarCode.cpp ZipCode.cpp  -std=c++14 -I ./ && ./BarCodeUt
 */
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <limits>
int main(int argc, char **argv) {

	{
		std::map<ZipCode*, BarCode::Codes> testCases = { //
				{ new ZipCode(1), { BarCode::Code::zero, BarCode::Code::zero,
						BarCode::Code::zero, BarCode::Code::zero,
						BarCode::Code::one, BarCode::Code::nine } }, //
						{ new ZipCode(12), { BarCode::Code::zero,
								BarCode::Code::zero, BarCode::Code::zero,
								BarCode::Code::one, BarCode::Code::two,
								BarCode::Code::seven } }, //
						{ new ZipCode(123), { BarCode::Code::zero,
								BarCode::Code::zero, BarCode::Code::one,
								BarCode::Code::two, BarCode::Code::three,
								BarCode::Code::four } }, //
						{ new ZipCode(1234), { BarCode::Code::zero,
								BarCode::Code::one, BarCode::Code::two,
								BarCode::Code::three, BarCode::Code::four,
								BarCode::Code::zero } }, //
						{ new ZipCode(12345), { BarCode::Code::one,
								BarCode::Code::two, BarCode::Code::three,
								BarCode::Code::four, BarCode::Code::five,
								BarCode::Code::five } }, //
						{ new ZipCode(6789), { BarCode::Code::zero,
								BarCode::Code::six, BarCode::Code::seven,
								BarCode::Code::eight, BarCode::Code::nine,
								BarCode::Code::zero } }, //
				};//
		std::cout
				<< "BarCode constructor BarCode(ZipCode zipCode) Tests -----------------"
				<< std::endl;
		for (auto &testCase : testCases) {
			std::cout << "Test value : " << *testCase.first << std::endl;
			BarCode barCode(*testCase.first);
			assert(barCode.getValue() == testCase.second);
		}
	}
	{
		std::map<ZipCode*, std::string> testCases = {	//
				{ new ZipCode(1), "1 11000 11000 11000 11000 00011 10100 1" },//
						{ new ZipCode(12),
								"1 11000 11000 11000 00011 00101 10001 1" },//
						{ new ZipCode(123),
								"1 11000 11000 00011 00101 00110 01001 1" },//
						{ new ZipCode(1234),
								"1 11000 00011 00101 00110 01001 11000 1" },//
						{ new ZipCode(12345),
								"1 00011 00101 00110 01001 01010 01010 1" },//
						{ new ZipCode(6789),
								"1 11000 01100 10001 10010 10100 11000 1" } };
		std::cout << "BarCode operator << Tests -----------------" << std::endl;
		for (auto &testCase : testCases) {
			std::cout << "Test value : " << *testCase.first << std::endl;
			BarCode barCode(*testCase.first);
			std::ostringstream oss;
			oss << barCode;
			assert(oss.str() == testCase.second);
		}
	}

	{

		std::map<std::string, BarCode::Codes> testCases = {	//
						{
								"1 00011 00101 00110 01001 01010 01100 1", //
								{ BarCode::Code::one, BarCode::Code::two,
										BarCode::Code::three,
										BarCode::Code::four,
										BarCode::Code::five, BarCode::Code::six } }, //
						{
								"1 10001 10010 10100 11000 01010 01100 1", //
								{ BarCode::Code::seven, BarCode::Code::eight,
										BarCode::Code::nine,
										BarCode::Code::zero,
										BarCode::Code::five, BarCode::Code::six } }, //
						{
								"1 a0001 10010 10100 11000 01010 01100 1", //test exception : char != {O,1}
								{ BarCode::Code::seven, BarCode::Code::eight,
										BarCode::Code::nine,
										BarCode::Code::zero,
										BarCode::Code::five, BarCode::Code::six } }, //
						{
								"2 10001 10010 10100 11000 01010 01100 1", //test exception : wrong begin char
								{ BarCode::Code::seven, BarCode::Code::eight,
										BarCode::Code::nine,
										BarCode::Code::zero,
										BarCode::Code::five, BarCode::Code::six } }, //
						{
								"1 10001 10010 10100 11000 01010 01100 2", //test exception : wrong end char
								{ BarCode::Code::seven, BarCode::Code::eight,
										BarCode::Code::nine,
										BarCode::Code::zero,
										BarCode::Code::five, BarCode::Code::six } }, //
						{
								"1 10001 10010 10100 11000 01010 1", //test exception : wrong number of digits
								{ BarCode::Code::seven, BarCode::Code::eight,
										BarCode::Code::nine,
										BarCode::Code::zero,
										BarCode::Code::five, BarCode::Code::six } }, //
				};
		std::cout
				<< "BarCode constructor BarCode(std::string barCode) Tests -----------------"
				<< std::endl;
		for (auto &testCase : testCases) {
			std::cout << "Test value : " << testCase.first << std::endl;
			try {

				BarCode barCode(testCase.first);
				//std::cout << barCode << std::endl;
				assert(barCode.getValue() == testCase.second);
			} catch (std::domain_error &e) {
				assert(e.what() == BarCode::INVALID_CODE_MSG);
			}
		}
	}
	return 0;
}

#endif

