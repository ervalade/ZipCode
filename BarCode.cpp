/*
 * BarCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <BarCode.h>

const std::map<Digit, Code> BarCode::convert = { { Digit::one, Code::one },
		{ Digit::two, Code::two }, {Digit:: three, Code::three }, { Digit::four, Code::four },
		{ Digit::five, Code::five }, { Digit::six, Code::six }, { Digit::seven, Code::seven }, { Digit::eight,
				Code::eight }, { Digit::nine, Code::nine }, { Digit::zero, Code::zero } };

BarCode::BarCode(ZipCode zipCode):value({0}) {
	//convert ZipCode to value : 95014 ->> 0b10100, 0b01010 ,....
	//1; 379
// 9, 5,0,1,4
	//9 -> 10000,...
	//1000,100,10,1
//	for (int i = 0; i < zipCode.getValue().size(); i++) {///  0
		for (auto& digit:zipCode.getValue()){
			this->value.back() = BarCode::convert.at(digit);
			std::cout <<(*this)<<std::endl;

		//this->value.at(i) = BarCode::convert.at(zipCode. getValue(). at(i));
	}
//	this->value.at(this->value.size()) =this->getKey(zipCode);
	this->value.back()=BarCode::getKey(zipCode);
//	this->value[this->value.size()] =BarCode::convert.at(zipCode.getKey());

	//*(this->value.end()) =BarCode::convert.at(zipCode.getKey());

}

BarCode::~BarCode() {
// TODO Auto-generated destructor stub
}
#include <numeric> //std::accumulate
#include <cmath> //modf

const std::array<Code, ZipCode::LENGTH + 1>& BarCode::getValue() const {
	return value;
}

Code BarCode::getKey(const ZipCode zipCode) {
	zipCode.getValue();
	double sum=
		//calcul de la somme des  digits
		std::accumulate((int*)(zipCode.getValue().begin()),	(int*)(zipCode.getValue().end()),0);
//	std::accumulate(zipCode.getValue().begin(),	zipCode.getValue().end(),0);

	double partieEntiere=0.0;
	//récupération de la partie décimale (après la virgule)
	double partieDecimale=modf(sum/10.0,&partieEntiere);
	//
	int cle=(int)(10.0*
			//calcul du complément pour obtenir une unité
			(1.0 - partieDecimale)
			//ajouter 0.5 pour évitr arrondi valeur inférieurs lors du cast
			+0.5)
		//modulo 10 pour obtenir 0 si partie décimale =0
		%10;
	return BarCode::convert.at((Digit)cle);
}
#include <iomanip>
#include <bitset>
std::ostream& operator<<(std::ostream &os, BarCode &b) {
	for (auto &code : b.getValue()) {
		std::cout << std::bitset<5>((int)code)<<' ';
	//	os << std::setw( 5) << std::setbase(2)<< (int) code<<' ';
	}
	return os;
}

#ifdef _BARCODE_UT_
/*
 g++ -D _BARCODE_UT_ -o BarCodeUt BarCode.cpp ZipCode.cpp  -std=c++14 -I ./ && ./BarCodeUt
 */
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>

int main(int argc, char **argv) {
	BarCode barCode(ZipCode(95014));
	std::cout << barCode << std::endl;
	/*
	std::map<ZipCode,std::string> testCases={
			{ZipCode(0),"00000"}};
	*/
	/*
			{1,"00001"},
			{12,"00012"},
			{123,"00123"},
			{1234,"01234"},
			{12345,"12345"}
	};
	*/
	/*
	for(auto const testCase:testCases){
		ZipCode zipCode(testCase.first);
	//zipCode.operator<<(std::cout);// operator << as member  : friend not needed
	//	std::cout << zipCode << std::endl;
		std::ostringstream oss;
		oss <<zipCode ;
	assert(oss.str()==testCase.second);
	}
	*/
	return 0;
}

#endif


