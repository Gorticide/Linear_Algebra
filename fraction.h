
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>

class Fraction
{
    private:
        int num, den;
        void normalize();
        int gcf(int a, int b);
        int lcm(int a, int b);

	public:
		Fraction() {set(0, 1);}
		Fraction(int n, int d) {set(n, d);}
		Fraction(int n) {set(n, 1);}
		Fraction (const Fraction &src);
		Fraction (std::string);

		void set(int n, int d) {num = n; den = d; normalize();}

		int getNum() const {return num;}
		int getDen() const {return den;}
		Fraction add(const Fraction &other);
    Fraction sub(const Fraction &other);
		Fraction mult(const Fraction &other);
    Fraction div(const Fraction &other);
		Fraction operator+(const Fraction &other) {return add(other);}
    Fraction operator-(const Fraction &other) {return sub(other);}
		Fraction operator*(const Fraction &other) {return mult(other);}
    Fraction operator/(const Fraction &other) {return div(other);}
		int operator==(const Fraction &other);
		friend std::ostream &operator<<(std::ostream &os, Fraction &fr);
};

#endif
