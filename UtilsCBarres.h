#include <string> //std::string
namespace UtilsCBarres {

	/** Type Code Postal */
	typedef int CodePostal;
	/** Longueur d'un Code Postal */
	const int LONGUEUR_CODE_POSTAL = 5;

	/**
	  p-ième caractère d'une chaine
	  example : evalCarac("btssnir",1) -> 't'
	  @param[in] txt - un texte
	  @param[in] p - indice
	  @return p-ième caractère de txt
	 */
	char evalCarac(const std::string& txt,int p);

	/**
	  Fixe le p-ieme caractere d'une chaine
	  example : std::string s("btssnir");evalCarac(s,0,'B') -> s : "Btssnir"
	 */
	void fixerCarac(std::string& txt, int p, char c);

	/**
	  Renverse un texte
	  example : std::string s("btssnir");renverserTexte(s) -> s : "rinsstb"
	  @param[in,out] txt - un texte
	 */
	void renverserTexte(std::string& txt);

	/**
	  Conversion d'un chiffre en Ascii
	  example : cvchiffre(61) -> 'a'
	  @param[in] n - un entier dans [0..9]
	  @return la conversion d'un chiffre en Ascii
	 */
	char cvchiffre(int n);
	/**
	  Chiffre de poids faible d'un entier
	  example : xchiffre(65) -> 5
	  @param[in] n - un entier positif
	  @return le chiffre de poids faible de n
	 */
	int xchiffre(int n);

	/**
	  Perte du chiffre de poids faible d'un entier
	  example : int i=78;xdiviser(i) -> i : 7
	  @param[in,out] n - un entier positif
	 */
	void xdiviser(int& n);

	/**
	  Gain d'un chiffre de poids faible d'un entier
	  example :  int i=78;xmultiplier(i) -> i : 780
	  @param[in,out] n - un entier positif
	 */
	void xmultiplier(int& n);

	/**
	  Somme des chiffres d'un entier
	  example :  sommeChiffres(12345) -> 15
	  @param[in] n - un entier positif
	  @return la somme des chiffres de n
	 */
	int sommeChiffres(int n);
}
