#include "BigInt.h"
#include <string.h>
#include <iostream>

BigInt::BigInt()
{
    digits = 0;
    sign = 0;
    number = NULL;
}
BigInt::BigInt(long long int nr)
{
    int i;
    long long int copied = nr; // facem o copie a numarului pe care o prelucram pentru a afla numarul de cifre ale acestuia
    while(copied > 0)
         {
             digits++;
             nr = nr / 10;
         }
    if(nr < 0)                  // setam semnul numarului
        {
            sign = false;
            nr = -nr;
        }
    else
        sign = true;

    number = new short[digits];     // alocam dinamic un vector de tip short in care vom salva numarul
    for(i = digits-1; i >= 0; i--)  // introducem cifrele in vector astfel incat prima cifra a numarului sa se afle pe prima pozitie in vector
    {
        number[i] = nr % 10;
        nr = nr / 10;
    }
}

BigInt::BigInt(char* string)
{
    int i;
    if(string[0] == '-')              // verificam daca numarul este negativ
        {
            sign = false;
            digits = strlen(string)-1;
        }
    else
        {
            sign = true;
            digits = strlen(string);
        }
    number = new short[digits];     // alocam dinamic un vector de tip short in care vom salva numarul

    for(i = 0; i < digits; i++)     // introducem cifrele in vector astfel incat prima cifra a numarului sa se afle pe prima pozitie in vector
        {
            if(sign == false)
                number[i] = string[i+1]-'0';
            else
                number[i] = string[i]-'0';
        }
}

BigInt::BigInt(const BigInt &nr)     // copiem toate datele
{
    digits = nr.digits;
    sign = nr.sign;
    number = new short [nr.digits];
    int i;
    for(i = 0; i < digits; i++)
        number[i] = nr.number[i];
}

BigInt::~BigInt()
{
    sign = 0;
    digits = 0;
    delete []number;
}

BigInt BigInt::operator =(const BigInt &value)
{
    digits = value.digits;
    sign = value.sign;
    number = new short [value.digits];
    int i;
    for(i = 0; i < digits; i++)
        number[i] = value.number[i];

    return *this;
}

BigInt BigInt::operator =(long long int nr)
{
    int i;
    long long int copy = nr;
    digits = 0;
    while(copy != 0)
         {
             digits++;
             copy = copy / 10;
         }
    if(nr < 0)
        {
            sign = false;
            nr = -nr;
        }
    else
        sign = true;

    number = new short[digits];
    for(i = digits-1; i >= 0; i--)
    {
        number[i] = nr % 10;
        nr = nr / 10;
    }
    return *this;
}

BigInt BigInt::operator = (char *string)
{
    int i;
    if(string[0] == '-')
        {
            sign = false;
            digits = strlen(string)-1;
        }
    else
        {
            sign = true;
            digits = strlen(string);
        }
    number = new short[digits];

    for(i = 0; i < digits; i++)
        {
            if(sign == false)
                number[i] = string[i+1]-'0';
            else
                number[i] = string[i]-'0';
        }
    return *this;
}

int comparision(BigInt number_1, BigInt number_2) // compara daca number_1 este mai mic decat number_2 si returneaza 1 - pentru adevarat, -1 - pentru fals si 0 - daca sunt egale ca numar de cifre
{
    unsigned short no_1_digits, no_2_digits;
    no_1_digits = number_1.digits;
    no_2_digits = number_2.digits;

    if(no_1_digits < no_2_digits) return 1;
    if(no_1_digits > no_2_digits) return -1;

    int i;
    for(i = 0; i < no_1_digits; i++) {
        if(number_1.number[i] < number_2.number[i]) return 1;
        else if(number_1.number[i] > number_2.number[i]) return -1;
    }
    return 0;
}

BigInt add(BigInt number_1, BigInt number_2)
{
    short keep_in_mind, digit_1, digit_2, sum, diff_between_digits;
    BigInt bigger_no = number_1 , smaller_no = number_2;
    keep_in_mind = digit_1 = digit_2 = sum = 0;

    if(number_1.digits < number_2.digits)
    {
            bigger_no = number_2;
            smaller_no = number_1;
    }

    int i;
    diff_between_digits = bigger_no.digits - smaller_no.digits;
    for(i = smaller_no.digits - 1; i >= 0; i--)
    {
        digit_1 = bigger_no.number[i + diff_between_digits];
        digit_2 = smaller_no.number[i];

        sum = digit_1 + digit_2 + keep_in_mind;
        keep_in_mind = sum / 10;
        bigger_no.number[i + diff_between_digits] = sum % 10;
    }


    for(i = bigger_no.digits - smaller_no.digits - 1; i >=0; i--)
    {
        sum = bigger_no.number[i] + keep_in_mind;
        bigger_no.number[i] = sum % 10;
        keep_in_mind = sum / 10;
    }

    if(keep_in_mind > 0)
    {
        short *temp = new short[bigger_no.digits + 1];
        temp[0] = keep_in_mind;
        for(i = 1; i <= bigger_no.digits; i++) {
            temp[i] = bigger_no.number[i - 1];
        }
        delete []bigger_no.number;
        bigger_no.number = temp;
        bigger_no.digits++;
    }

    int counter = bigger_no.digits;
    while(bigger_no.number[counter - 1] == 0) {
        counter--;
    }
    return bigger_no;
}
BigInt subtract(BigInt number_1, BigInt number_2)
{
    short keep_in_mind, digit_1, digit_2, sub, diff_between_digits;
    BigInt bigger_no = number_1 , smaller_no = number_2, result;
    keep_in_mind = digit_1 = digit_2 = sub = 0;

    if(comparision(number_1, number_2) == 1) {
        bigger_no = number_2;
        smaller_no = number_1;
    }

    result.number = new short[bigger_no.digits];
    result.digits = bigger_no.digits;
    int i;
    for(i=0; i < bigger_no.digits; i++)
        result.number[i] = 0;
    diff_between_digits = bigger_no.digits - smaller_no.digits;

    for(i = smaller_no.digits - 1; i >= 0; i--)
    {
        digit_1 = bigger_no.number[i+diff_between_digits];
        digit_2 = smaller_no.number[i];

        sub = digit_1 - digit_2 - keep_in_mind;

        if(sub < 0) {
            sub = sub + 10;
            keep_in_mind = 1;
        } else
            keep_in_mind = 0;

        result.number[i + diff_between_digits] = sub %10;
    }

    for(i = bigger_no.digits - smaller_no.digits -1; i >= 0; i--)
    {
        sub = bigger_no.number[i] - keep_in_mind;
        if(sub < 0) {
            sub = sub + 10;
            keep_in_mind = 1;
        } else
            keep_in_mind = 0;
        result.number[i] = sub%10;
    }

    int counter = 0;
    while(result.number[counter] == 0 && counter < result.digits) {
        counter++;
    }

    counter = result.digits - counter;

    if (counter == 0)
        counter = 1;

    for (i = 0; i < counter; i++)
        result.number[i] = result.number[i + (result.digits - counter)];

    result.digits = counter;

    result.sign = bigger_no.sign;

    return result;
}

BigInt multiply(BigInt number_1, BigInt number_2)
{
    short keep_in_mind = 0;
    short num1_digits = number_1.digits;
    short num2_digits = number_2.digits;
    short firstIndex, secondIndex;
    BigInt result, first, second;
    result.number = new short[num1_digits + num2_digits];
    if(number_1.number[0] == 0 || number_2.number[0] == 0)
    {
        result.digits = 1;
        result.number[0] = 0;
        result.sign = true;
        return result;
    }

    result.digits = num1_digits + num2_digits;
    firstIndex = result.digits-1;
    first = number_1;
    second = number_2;

    int i, first_digit,j_digit,j,sum;

    for(i = 0; i < result.digits; i++)
        result.number[i] = 0;
    for(i = num1_digits-1; i >= 0; i--)
    {
        keep_in_mind = 0;
        secondIndex = 0;
        first_digit = first.number[i];

        for(j = num2_digits-1; j>=0; j--)
        {
            j_digit = second.number[j];
            sum = (first_digit * j_digit) + result.number[firstIndex + secondIndex] + keep_in_mind;
            keep_in_mind = sum / 10;
            result.number[firstIndex + secondIndex] = sum % 10;
            secondIndex--;
        }

        if(keep_in_mind > 0) {
            result.number[firstIndex + secondIndex] = result.number[firstIndex + secondIndex] + keep_in_mind;
        }

        firstIndex--;
    }

    int counter = 0;
    while(result.number[counter] == 0 && counter < result.digits) {
        counter++;
    }

    counter = result.digits - counter;

    if (counter == 0)
        counter = 1;

    for (i = 0; i < counter; i++)
        result.number[i] = result.number[i + (result.digits - counter)];

    result.digits = counter;

    if((number_2.sign == false && number_1.sign == true) || (number_2.sign == true && number_1.sign == false)) result.sign = false;
    if(number_1.sign == true && number_2.sign == true) result.sign = true;
    if(number_1.sign == false && number_2.sign == false) result.sign = true;
    return result;
}

BigInt divide(BigInt number_1, BigInt number_2)
{
    BigInt dividend, divisor, result, rest;
    short resInt = -1;

    dividend = number_1;
    divisor = number_2;

    dividend.sign = divisor.sign = true;

    result = resInt;
    if(divisor.number[0] == 0)
        return result;
    resInt = 0;
    result = resInt;
    if(comparision(dividend, divisor) == 1)
        return result;

    do {
        rest = dividend - divisor;
        resInt++;
        dividend = rest;
    } while(comparision(divisor, rest) != -1);

    result = resInt;

    if((number_2.sign == false && number_1.sign == true) || (number_2.sign == true && number_1.sign == false)) result.sign = false;
    if(number_1.sign == true && number_2.sign == true) result.sign = true;
    if(number_1.sign == false && number_2.sign == false) result.sign = false;
    return result;
}


BigInt BigInt::operator +(const BigInt &value)
{
    BigInt result;
    if(sign == value.sign)
        result = add((*this),value);
    else
        result = subtract((*this),value);

    return result;
}

BigInt BigInt::operator - (const BigInt &value)
{
    BigInt result;
    BigInt new_value = value;
    if(new_value.sign == false)
        new_value.sign = true;
    else
        new_value.sign = false;
    if(new_value.sign == sign) {
        result = add((*this), new_value);
    } else {
        result = subtract((*this), new_value);
    }

    return result;
}

BigInt BigInt::operator *(const BigInt &value)
{
    return multiply((*this), value);
}


BigInt BigInt::operator /(const BigInt &value)
{
    return divide((*this), value);
}

BigInt BigInt::pow(int exponent)
{
    int i;
    BigInt result = *this;
    for(i = 1; i < exponent; i++)
        result = result * (*this);
    return result;
}

int BigInt::parity()
{
    if(digits >= 1)
        {
            if(number[digits-1] % 2 == 0)
                return 1;
            else
                return 0;
        }
    return 0;
}

int BigInt::palindrome()
{
    int i;
    for(i = 0; i < digits; i++)
    {
        if((*this).number[i]!=(*this).number[digits-i-1])
            return 0;
    }
    return 1;
}

int BigInt::sum_of_digits()
{
    int i,sum = 0;
    for(i = 0; i < digits; i++)
        sum = sum + number[i];
    return sum;
}

std::istream& operator >> (std::istream& in, BigInt& value)
{
    char *number;
    number = new char[100];
    in>>number;
    value=number;
    std::cout << "Value: " << value << std::endl;
    delete []number;
    return in;
}

std::ostream& operator << (std::ostream& out, const BigInt& value)
{
    int i;
    if(value.sign==false)
        out<<"-";
    for(i = 0; i < value.digits; i++)
        out<<value.number[i];
    return out;
}
