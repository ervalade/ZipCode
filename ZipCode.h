/*
 * ZipCode.h
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#ifndef ZIPCODE_H_
#define ZIPCODE_H_
#include <string>

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
class ZipCode {
private:
	static const int LENGTH=5;
	std::array<Digit,ZipCode::LENGTH> value;
public:
	ZipCode(const unsigned  int value=0);//construteur : appeler automatiquement à l'instanciation
	virtual ~ZipCode();//destructeur appeler automatiquement à la suppression
//	std::string toString(); NOT NEEDED ANYMORE
	int getKey();
};

#endif /* ZIPCODE_H_ */
