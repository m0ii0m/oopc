#ifndef POLY_H
#define POLY_H

#include <ostream>
#include <vector>

class Poly {
  public:
	Poly();
	Poly(double d);

	size_t getSize() const;

	double& operator[](size_t i);
	double operator[](size_t i) const;
	double operator()(double d) const;
	friend std::ostream& operator<<(std::ostream& os, const Poly& p);
	friend Poly operator+(const Poly& p1, const Poly& p2);
	friend Poly operator-(const Poly& p1, const Poly& p2);
	friend Poly operator*(const Poly& p1, const Poly& p2);

  private:
	std::vector<double> coef;
};

#endif
