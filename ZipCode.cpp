/*
 * ZipCode.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#include <ZipCode.h>
//const int ZipCode::LENGTH = 5;

ZipCode::ZipCode(const unsigned int value) { //liste d'initialisation
	//convert int to std::array<Digit,5>
	//1000
	for (int i = 10000; i > 0; i /= 10) {
	}
}

ZipCode::~ZipCode() {
	// TODO Auto-generated destructor stub
}
/* // NOT NEEDED ANYMORE
#include <UtilsCBarres.h>

std::string ZipCode::toString() {
	std::string rs;
	int cp = this->value;
	while (cp != 0) {
		rs += UtilsCBarres::cvchiffre(UtilsCBarres::xchiffre(cp));
		UtilsCBarres::xdiviser(cp);
	}
	while (rs.size() < UtilsCBarres::LONGUEUR_CODE_POSTAL) {
		rs += "0";
	}
	UtilsCBarres::renverserTexte(rs);
	return rs;
}
*////
int ZipCode::getKey() {
	int cle = 0;
	int s = UtilsCBarres::sommeChiffres(this->value);
	if (UtilsCBarres::xchiffre(s) != 0) {
		cle = (UtilsCBarres::xchiffre(s / 10) + 1) * 10 - s;
	}
	return cle;
}
