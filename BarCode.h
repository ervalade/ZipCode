/*
 * BarCode.h
 *
 *  Created on: 28 avr. 2020
 *      Author: eric
 */

#ifndef BARCODE_H_
#define BARCODE_H_
#include <ZipCode.h>
#include <vector>
#include <map>

enum class Code {
  //      74210
  one = 0b00011,
  two = 0b00101,
  three = 0b00110,
  four = 0b01001,
  five = 0b01010,
  six = 0b01100,
  seven = 0b10001,
  eight = 0b10010,
  nine = 0b10100,
  zero = 0b11000
};
class BarCode {

  private:
    std::vector<Code> value; //+1 for zip code key
    static const std::map<Digit, Code> convert; //static-> défini une seule fois appelée variable (attribut) de classe

  public:
    BarCode(ZipCode zipCode);
    virtual ~BarCode();
    friend std::ostream& operator<<(std::ostream &os, BarCode &b);
    const std::vector<Code>& getValue() const;

  private:
    Code getKey(const ZipCode zipCode); //static-> défini une seule fois appelée méthode de classe
};

#endif /* BARCODE_H_ */
