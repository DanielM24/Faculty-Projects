#include <iostream>
#include <ostream>
#include <cassert>
#include"AVLDictionary.h"
#include"node.h"

using namespace std;

int main()
{
	int value;
	Dictionary <int, int> Dictionar;
	Dictionary <int, int> CopyofDictionar;

	// Metoda de adaugare a unei perechi noi cheie - valoare
	Dictionar.add(1, 13);
	Dictionar.add(2, 2);
	Dictionar.add(3, 3);

	Dictionar.in_order();

	// Verificarea metodei de cautare dupa cheie
	assert(Dictionar.searchKey(1, value));   

	// Suprascrierea operatorului " = " pentru copierea unui dictionar
	CopyofDictionar = Dictionar;                 
	assert(!CopyofDictionar.isEmpty());

	// Suprascrierea operatorului " [] " pentru obtinerea valorii salvate pentru o anumita cheie;
	Dictionar.add(4, 10);
	int x = Dictionar[4];
    cout << "Valoarea salvata pentru cheia 1 este " << Dictionar[1] << "\n";
    cout << "Valoarea salvata pentru cheia 2 este " << Dictionar[2] << "\n";
    cout << "Valoarea salvata pentru cheia 3 este " << Dictionar[3] << "\n";
    cout << "Valoarea salvata pentru cheia 4 este " << Dictionar[4] << "\n";
    cout << "Valoarea salvata pentru cheia -14 este " << Dictionar[-14] << "\n";

	// Metoda de stergere a unei perechi din dictionar dupa cheie
	Dictionar.deleteAfterKey(5);
	assert(false == Dictionar.searchKey(5, value));

    assert(true == Dictionar.searchKey(4, value));
    Dictionar.deleteAfterKey(4);
    assert(false == Dictionar.searchKey(4, value));

    // Metoda ce elimina toate elementele din dictionar
	CopyofDictionar.add(1, 3);
	CopyofDictionar.add(2, 12);
	CopyofDictionar.add(3, 6);
	CopyofDictionar.add(4, 5);
	CopyofDictionar.deleteAllElements();
	assert(CopyofDictionar.isEmpty());

	system("pause");
	return 0;
}