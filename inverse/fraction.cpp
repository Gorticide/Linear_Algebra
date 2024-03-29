// Class automatically generated by Dev-C++ New Class wizard

#include "fraction.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

Fraction::Fraction(Fraction const &src)
{
     num = src.num;
     den = src.den;
}

Fraction::Fraction(double trouble)  {
	num = trouble*decimals;/*once specified before, for ex. 100 */
	den = decimals;
	normalize();
}

Fraction::Fraction(std::string fractString)
{
     int divPos = fractString.find("/");
     char numString[80] = ""; //Quick patch, make the array big enough (hopefully)
     char denString[80] = "";

     strcpy(numString, fractString.substr(0, divPos).c_str());
     num = atoi(numString);

     if (divPos == -1)
     {
        den = 1;
     }

     else
     {
        strcpy(denString, fractString.substr(divPos + 1).c_str());
        den = atoi(denString);
     }
}

void Fraction::normalize()
{
     if (den == 0 || num == 0)
     {
          num = 0;
          den = 1;
     }

     if (den < 0)
     {
          num *= -1;
          den *= -1;
     }

     int n = gcf(num, den);
     num = num/n;
     den = den/n;
}

int Fraction::gcf(int a, int b)
{
    if (a % b == 0)
       return abs(b);
    else
       return gcf(b, a % b);
}

int Fraction::lcm(int a, int b)
{
    return (a / gcf(a, b)) * b;
}

Fraction Fraction::add(const Fraction &other)
{
    Fraction fract;
    int lcd = lcm(den, other.den);
    int quot1 = lcd/den;
    int quot2 = lcd/other.den;
    fract.set(num * quot1 + other.num * quot2, lcd);
    fract.normalize();
    return fract;
}

Fraction Fraction::mult(const Fraction &other)
{
    Fraction fract;
    fract.set(num * other.num, den * other.den);
    return fract;
}

Fraction Fraction::div(const Fraction &other)
{
    Fraction fract;
    fract.set(num * other.den, den * other.num);
    return fract;
}

int Fraction::operator==(const Fraction &other)
{
    return (num == other.num && den == other.den);
}

std::ostream &operator<<(std::ostream &os, Fraction &fr)
{
    if (fr.num == 0) os << 0;
    else {
      if (fr.den == 1) os << fr.num;
      else os << fr.num << "/" << fr.den;
    }
    return os;
}
