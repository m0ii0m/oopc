#include "Poly.h"
#include <cmath>

using namespace std;

static const double EPSILON = 1e-12;

static bool isZero(double d)
{
	return fabs(d) < EPSILON;
}

Poly::Poly() {}

Poly::Poly(double d) : coef{d} {}

size_t Poly::getSize() const
{
	size_t n = coef.size();
	while (n > 0 && isZero(coef[n - 1]))
		n--;
	return n;
}

void Poly::trim()
{
	while (!coef.empty() && isZero(coef.back()))
		coef.pop_back();
}

double& Poly::operator[](size_t i)
{
	if (i >= coef.size())
		coef.resize(i + 1, 0.0);
	return coef[i];
}

double Poly::operator[](size_t i) const
{
	return i < coef.size() ? coef[i] : 0.0;
}

double Poly::operator()(double d) const
{
	double res = 0.0;
	for (size_t i = 0; i < coef.size(); i++) {
		res += coef[i] * pow(d, i);
	}
	return res;
}

ostream& operator<<(ostream& os, const Poly& p)
{
	bool first = true;
	for (size_t i = p.getSize(); i-- > 0;) {
		double c = p[i];
		if (isZero(c))
			continue;

		if (first)
			os << (c < 0.0 ? "-" : "");
		else
			os << (c < 0.0 ? " - " : " + ");

		double a = fabs(c);
		if (a != 1.0 || i == 0)
			os << a;
		if (i >= 1)
			os << "x";
		if (i >= 2)
			os << "^" << i;

		first = false;
	}
	if (first)
		os << 0;
	return os;
}

Poly operator+(const Poly& p1, const Poly& p2)
{
	Poly res;
	for (size_t i = 0; i < max(p1.getSize(), p2.getSize()); i++) {
		res[i] = p1[i] + p2[i];
	}
	res.trim();
	return res;
}

Poly operator-(const Poly& p1, const Poly& p2)
{
	Poly res;
	for (size_t i = 0; i < max(p1.getSize(), p2.getSize()); i++) {
		res[i] = p1[i] - p2[i];
	}
	res.trim();
	return res;
}

Poly operator*(const Poly& p1, const Poly& p2)
{
	Poly res;
	for (size_t i = 0; i < p1.getSize(); i++)
		for (size_t j = 0; j < p2.getSize(); j++)
			res[i + j] += p1[i] * p2[j];
	res.trim();
	return res;
}