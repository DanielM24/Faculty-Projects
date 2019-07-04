#ifndef BIGINT_H
#define BIGINT_H
#include <ostream>
#include <istream>

class BigInt
{
    short *number;     // vectorul in care vom memora numarul - am ales sa fie de tipul short pentru a economisi mai mult spatiu
    short digits;      // numarul de cifre ale numarului intreg
    bool sign;         // semnul numarului true - pozitiv / false - negativ

    public:
        BigInt();                 // constructorul fara parametrii
        BigInt(long long int nr); // constructorul cu parametru pentru citirea unui numar in intervalul (-2^63 , 2^63-1)
        BigInt(char *string);     // constructorul cu parametru pentru citirea unui numar aflat in afara intervalului de mai sus
        BigInt(const BigInt &nr); // constructorul de copiere

        ~BigInt();                // destructorul

        BigInt operator +(const BigInt &value);     // supraincarcarea operatorului +
        BigInt operator -(const BigInt &value);     // supraincarcarea operatorului -
        BigInt operator *(const BigInt &value);     // supraincarcarea operatorului *
        BigInt operator /(const BigInt &value);     // supraincarcarea operatorului /
        BigInt operator =(const BigInt &value);     // supraincarcarea operatorului =
        BigInt operator =(long long int nr);        // supraincarcarea operatorului =
        BigInt operator =(char *string);            // supraincarcarea operatorului =

        friend BigInt add(BigInt number_1, BigInt number_2);        // functie ajutatoare pentru adunare
        friend BigInt subtract(BigInt number_1, BigInt number_2);   // functie ajutatoare pentru scadere
        friend BigInt multiply(BigInt number_1, BigInt number_2);   // functie ajutatoare pentru inmultire
        friend BigInt divide(BigInt number_1, BigInt number_2);     // functie ajutatoare pentru impartire
        friend int comparision(BigInt number_1, BigInt number_2);   // functie ajutatoare pentru compararea a 2 numere

        BigInt pow(int exponent);                   // functie pentru ridicarea la putere
        int parity();                               // functie pentru determinarea paritatii
        int palindrome();                           // functie care indica daca numarul este palindrom
        int sum_of_digits();                        // functie pentru calcularea sumei cifrelor numarului

        friend std::istream& operator >> (std::istream& in, BigInt& value);             //supraincarcarea operatorului de citire
        friend std::ostream& operator << (std::ostream& out, const BigInt& value);      // supraincarcarea operatorului de afisare
};

#endif // BIGINT_H
