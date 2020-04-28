#include <cstdlib>
#include <iostream>//std:cin, std::cout

#include <UtilsCBarres.h>
//g++ -o zipCode2BarCode zipCode2BarCode.cpp UtilsCBarres.cpp -D NDEBUG -I ./
#ifndef NDEBUG
//g++ -o zipCode2BarCode zipCode2BarCode.cpp UtilsCBarres.cpp -I ./
UtilsCBarres::CodePostal codePostal;
#include <cstdlib> //atoi
#endif
/**
  CodePostal Vers CodesBarres
  */
void cpostalVersCBarres();

int main(int argc, char** argv) {
#ifndef NDEBUG
	codePostal=atoi(argv[1]);
#endif

	cpostalVersCBarres();
	return 0;
}
/**
  Affiche le code barres d'un code postal
  @param[in] cp - un code postal
  */
void afficherCB(UtilsCBarres::CodePostal codePostal);
void cpostalVersCBarres() {
#ifdef NDEBUG
	UtilsCBarres::CodePostal codePostal;
	std::cout<<"Votre code postal? ";
	std::cin>>codePostal;
#endif
	afficherCB(codePostal);
}

std::string cpostalVersChaine(const UtilsCBarres::CodePostal codePostal);
int calculCle(const UtilsCBarres::CodePostal codePostal);
void afficherChiffreCB(const char c);
void afficherCB(const UtilsCBarres::CodePostal codePostal) {
	std::string s = cpostalVersChaine(codePostal);
	std::cout<<"codePostalostalVersChaine= "<<s<<std::endl;
	int cle = calculCle(codePostal);
	std::cout<<"cle = "<<cle<<std::endl;
	std::cout<<"| ";
	for (int j = 0; j < s.size(); ++j) {
		afficherChiffreCB(UtilsCBarres::evalCarac(s, j));
	}
	afficherChiffreCB(UtilsCBarres::cvchiffre(cle));
	std::cout<<"|";
	std::cout<<std::endl;
}
std::string cpostalVersChaine(const UtilsCBarres::CodePostal codePostal){
	std::string rs;
	int cp=(int)codePostal;
	while (cp != 0) {
		rs += UtilsCBarres::cvchiffre(UtilsCBarres::xchiffre(cp));
		UtilsCBarres::xdiviser(cp);
	}
	while (rs.size() < UtilsCBarres::LONGUEUR_CODE_POSTAL ) {
		rs += "0";
	}
	UtilsCBarres::renverserTexte(rs);
	return rs;
}
int calculCle(const UtilsCBarres::CodePostal codePostal){
	int cle = 0;
	int s = UtilsCBarres::sommeChiffres(codePostal);
	if (UtilsCBarres::xchiffre(s) != 0) {
		cle = (UtilsCBarres::xchiffre(s/10) + 1)*10 - s;
	}
	return cle;
}
void afficherChiffreCB(const char c){
	switch (c) {
		case '1': std::cout<<":::|| "; break;
		case '2': std::cout<<"::|:| "; break;
		case '3': std::cout<<"::||: "; break;
		case '4': std::cout<<":|::| "; break;
		case '5': std::cout<<":|:|: "; break;
		case '6': std::cout<<":||:: "; break;
		case '7': std::cout<<"|:::| "; break;
		case '8': std::cout<<"|::|: "; break;
		case '9': std::cout<<"|:|:: "; break;
		case '0': std::cout<<"||::: "; break;
	}

}

