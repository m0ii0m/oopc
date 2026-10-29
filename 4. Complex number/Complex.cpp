#include "Complex.h"
#include <cmath>

Complex::Complex(double re, double im) : re(re), im(im) {}

Complex& Complex::operator+=(const Complex& other)
{
	re += other.re;
	im += other.im;
	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	re -= other.re;
	im -= other.im;
	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	double newRe = re * other.re - im * other.im;
	double newIm = re * other.im + im * other.re;
	re = newRe;
	im = newIm;
	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	double denominator = other.re * other.re + other.im * other.im;
	double newRe = (re * other.re + im * other.im) / denominator;
	double newIm = (im * other.re - re * other.im) / denominator;
	re = newRe;
	im = newIm;
	return *this;
}

double Complex::amplitude() const
{
	return std::hypot(re, im);
}

double Complex::phase() const
{
	return std::atan2(im, re);
}

Complex operator+(Complex lhs, const Complex& rhs)
{
	return lhs += rhs;
}

Complex operator-(Complex lhs, const Complex& rhs)
{
	return lhs -= rhs;
}

Complex operator*(Complex lhs, const Complex& rhs)
{
	return lhs *= rhs;
}

Complex operator/(Complex lhs, const Complex& rhs)
{
	return lhs /= rhs;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return lhs.re == rhs.re && lhs.im == rhs.im;
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

void Complex::show() const
{
	std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << c.re << (c.im < 0 ? " - " : " + ") << std::fabs(c.im) << "i";
	return os;
}
