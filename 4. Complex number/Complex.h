#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
  public:
	double re;
	double im;

	Complex(double re = 0.0, double im = 0.0);

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	double amplitude() const;
	double phase() const;
	void show() const;
};

Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& os, const Complex& c);

#endif
