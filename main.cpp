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
	unsigned int code(0);
	try {
		while (true) {
			std::cin >> code;
			ZipCode zipCode(code);
			BarCode barCode(zipCode);
			std::cout << barCode << std::endl;
		}
	} catch (const std::domain_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

