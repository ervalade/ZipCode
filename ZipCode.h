/*
 * ZipCode.h
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#ifndef ZIPCODE_H_
#define ZIPCODE_H_
/*
 * @startuml
 * class ZipCode{
 * - value :int
 * }
 * class BarCode{
 * - value:string
 * }
 * ZipCode -- BarCode
 * @enduml
 */
enum class Digit {
	one = 1,
	two = 2,
	three = 3,
	four = 4,
	five = 5,
	six = 6,
	seven = 7,
	eight = 8,
	nine = 9,
	zero = 0
};
#include <array>
#include <iostream>
#include <map>
#include <string>

class ZipCode {
public:
	static const int LENGTH = 5; //static-> défini une seule fois appelée variable (attribut) de classe
	static const std::string OUT_OF_RANGE_MSG;
	//std::ostream & operator<<(std::ostream & os);operator << as member : friend not needed
	friend std::ostream& operator<<(std::ostream &os, const ZipCode &z);
	//typedef std::array<Digit, ZipCode::LENGTH> Digits; //C style
	using Digits=std::array<Digit, ZipCode::LENGTH>; //modern C++ style
private:
	ZipCode::Digits value; //défini pour chaque objet (instance de classe) appelée variable d'instance
	static const std::map<int, Digit> convert; //static-> défini une seule fois appelée variable (attribut) de classe

public:
	ZipCode(const unsigned int zipValue = 0); //construteur : appeler automatiquement à l'instanciation
	const ZipCode::Digits& getValue() const;
	virtual ~ZipCode();	//destructeur appeler automatiquement à la suppression
	const int getDigitNumber() const;
};

#endif /* ZIPCODE_H_ */
