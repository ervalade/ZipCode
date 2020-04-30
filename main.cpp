/*
 * main.cpp
 *
 *  Created on: 30 avr. 2020
 *      Author: eric
 */
#include <BarCode.h>
#include <ZipCode.h>
#include <istream>
#include <ostream>

int main(int argc, char **argv) {
	std::cout << " Enter a zip code  [0..99999]: ";
	int code(0);
	std::cin >> code;
	ZipCode zipCode(code);
	 BarCode barCode(zipCode);
	std::cout << barCode;
	return 0;
}


