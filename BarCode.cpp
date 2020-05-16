/*
 * BarCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <BarCode.h>

const std::map<ZipCode::Digit, BarCode::Code> BarCode::convert = { {
		ZipCode::Digit::one, Code::one }, { ZipCode::Digit::two, Code::two }, {
		ZipCode::Digit::three, Code::three },
		{ ZipCode::Digit::four, Code::four },
		{ ZipCode::Digit::five, Code::five },
		{ ZipCode::Digit::six, Code::six },
		{ ZipCode::Digit::seven, Code::seven }, { ZipCode::Digit::eight,
				Code::eight }, { ZipCode::Digit::nine, Code::nine }, {
				ZipCode::Digit::zero, Code::zero } };

BarCode::BarCode(ZipCode zipCode) :
		value( { 0 }) {
	//convert ZipCode to value : 95014 ->> 0b10100, 0b01010 ,....
	//1; 379
// 9, 5,0,1,4
	//9 -> 10000,...
	//1000,100,10,1
	for (auto &digit : zipCode.getValue()) {
		this->value.push_back(BarCode::convert.at(digit));
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
	return BarCode::convert.at((ZipCode::Digit) cle);
}
#include <iomanip>
#include <bitset>
std::ostream& operator<<(std::ostream &os, BarCode &b) {
	os << "1 ";
	for (auto &code : b.getValue()) {
		os << std::bitset<(int)BarCode::Code::nb_bits>((int) code) << ' ';
//os << std::bitset<5>((int) code) << ' '; // TO DO : try replacing 5 by ?
	}
	os << '1';
	return os;
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
		std::cout << "BarCode constructor Tests -----------------" << std::endl;
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
	return 0;
}

#endif

