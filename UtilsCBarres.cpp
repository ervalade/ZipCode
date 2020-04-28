#include <UtilsCBarres.h>

char UtilsCBarres::evalCarac(const std::string& txt,int p) {
	return txt[p];
}


void UtilsCBarres::fixerCarac(std::string& txt, int p, char c) {
	txt[p] = c;
}


void UtilsCBarres::renverserTexte(std::string& txt) {
	for (int j=0, k=txt.length()-1; j < k; ++j, --k) {
		char tmp = UtilsCBarres::evalCarac(txt,j);
		UtilsCBarres::fixerCarac(txt, j, UtilsCBarres::evalCarac(txt, k));
		UtilsCBarres::fixerCarac(txt, k, tmp);
	}
}


char UtilsCBarres::cvchiffre(int n) {
	return static_cast<char>(n+static_cast<int>('0'));
}


int UtilsCBarres::xchiffre(int n) {
	return n%10;
}


void UtilsCBarres::xdiviser(int& n) {
	n/=10;
}


void UtilsCBarres::xmultiplier(int& n) {
	n*=10;
}


int UtilsCBarres::sommeChiffres(int n) {
	int resultat=0;
	while (n!=0) {
		resultat+=n%10;
		n /= 10;
	}
	return resultat;
}


