#include <iostream>
#include <bitset>
/*
 * g++ -o ZipCode ZipCode.cpp -std=c++14
*/
int main(int argc,char **argv){
	int zipCode(0);
	while (true){
		std::cin >> zipCode;
		std::cout <<  std::bitset<17>(zipCode)<< std::endl;//cr required!
	}
	return 0;
}
