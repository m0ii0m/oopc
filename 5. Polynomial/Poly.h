#ifndef POLY_H
#define POLY_H

#include <ostream>
#include <vector>

class Poly {
  public:
	Poly();
	Poly(double d);

	size_t getSize() const;
	void trim();

	double& operator[](size_t i);
	double operator[](size_t i) const;
	double operator()(double d) const;

  private:
	std::vector<double> coef;
};

std::ostream& operator<<(std::ostream& os, const Poly& p);
Poly operator+(const Poly& p1, const Poly& p2);
Poly operator-(const Poly& p1, const Poly& p2);
Poly operator*(const Poly& p1, const Poly& p2);

#endif
