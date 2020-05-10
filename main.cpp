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
	std::cout << " Enter a zip code  [1..99999]: ";
	try {
		unsigned int code(0);
		std::cin >> code;
		ZipCode zipCode(code);
		BarCode barCode(zipCode);
		std::cout << barCode;
	} catch (const std::string &e) {
		std::cerr << e;
	}
	return 0;
}
