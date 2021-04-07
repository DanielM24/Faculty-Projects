#include <iostream>
#include <BigInt.h>
using namespace std;

int main()
{
    int x;
    BigInt number1, number2;
    cout<<"number 1 = ";
    cin>>number1;

    cout<<"number 2 = ";
    cin>>number2;
    // Adunarea numerelor intregi
    cout<<"number 1 + number 2 = ";
    cout<<number1 + number2<<"\n";
    // Scaderea numerelor intregi
    cout<<"number 1 - number 2 = ";
    cout<<number1 - number2<<"\n";
    // Inmultirea numerelor intregi
    cout<<"number 1 * number 2 = ";
    cout<<number1 * number2<<"\n";
    // Impartirea numerelor intregi
    cout<<"number 1 / number 2 = ";
    cout<<number1 / number2<<" r = "<< number1 - number2*(number1 / number2)<<"\n";
    // Ridicarea la putere a numerelor intregi
    cout<<"(number 1)^x ... insert x = ";
    cin>>x;
    cout<<"( "<<number1<<" )^"<<x<<" = "<<number1.pow(x)<<"\n";

    cout<<"(number 2)^x ... insert x = ";
    cin>>x;
    cout<<"( "<<number2<<" )^"<<x<<" = "<<number2.pow(x)<<"\n";
    // Paritatea numerelor intregi
    cout<<"parity of number 1 : ";
    if(number1.parity() == 1)
        cout<<"even ; \n";
    else
        cout<<"odd ; \n";

    cout<<"parity of number 2 : ";
    if(number2.parity() == 1)
        cout<<"even ; \n";
    else
        cout<<"odd ; \n";
    // Verificam daca numarul intreg este palindrom
    if(number1.palindrome() == 1)
    cout<<number1<<" is palindrome; \n";
    else
    cout<<number1<<" is not palindrome; \n";

    if(number2.palindrome() == 1)
    cout<<number2<<" is palindrome; \n";
    else
    cout<<number2<<" is not palindrome; \n";
    // Suma cifrelor unui numar intreg
    cout<<"number 1' sum of digits is = "<<number1.sum_of_digits()<<"\n";

    cout<<"number 2' sum of digits is = "<<number2.sum_of_digits();

    return 0;
}
