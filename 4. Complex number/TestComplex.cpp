#include "Complex.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

const double EPSILON = 1e-12;

bool approxEqual(double x, double y)
{
	return std::fabs(x - y) < EPSILON;
}

std::string toString(const Complex& c)
{
	std::ostringstream os;
	os << c;
	return os.str();
}

void testConstructionAndFieldAccess()
{
	std::cout << "=== testConstructionAndFieldAccess ===" << std::endl;
	Complex zero;
	Complex real(4.5);
	Complex full(1.0, -2.0);
	std::cout << "zero = ";
	zero.show();
	std::cout << "real = ";
	real.show();
	std::cout << "full = ";
	full.show();
	assert(zero.re == 0.0 && zero.im == 0.0);
	assert(real.re == 4.5 && real.im == 0.0);
	assert(full.re == 1.0 && full.im == -2.0);

	full.re = 7.0;
	full.im += 3.0;
	std::cout << "full = ";
	full.show();
	assert(full.re == 7.0 && full.im == 1.0);

	Complex copy = full;
	copy.re = -1.0;
	assert(copy.re == -1.0);
	assert(full.re == 7.0);
}

void testStreamInsertion()
{
	std::cout << "=== testStreamInsertion ===" << std::endl;
	assert(toString(Complex(3.0, 4.0)) == "3 + 4i");
	assert(toString(Complex(3.0, -4.0)) == "3 - 4i");
	assert(toString(Complex(-1.5, 0.0)) == "-1.5 + 0i");
	assert(toString(Complex()) == "0 + 0i");

	const Complex c(2.0, -0.5);
	std::cout << "chained: " << c << " and " << Complex(1, 1) << std::endl;
	assert(toString(c) == "2 - 0.5i");
}

void testArithmeticOperators()
{
	std::cout << "=== testArithmeticOperators ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	std::cout << "a + b = ";
	(a + b).show();
	std::cout << "a - b = ";
	(a - b).show();
	std::cout << "a * b = ";
	(a * b).show();
	std::cout << "Complex(5.0, 5.0) / Complex(1.0, 2.0) = ";
	(Complex(5.0, 5.0) / Complex(1.0, 2.0)).show();
	assert(a + b == Complex(4.0, 1.0));
	assert(a - b == Complex(-2.0, 3.0));
	assert(a * b == Complex(5.0, 5.0));
	assert(Complex(5.0, 5.0) / Complex(1.0, 2.0) == Complex(3.0, -1.0));
	assert((a * b) / b == a);

	Complex q = a / b;
	assert(approxEqual(q.re, 0.1) && approxEqual(q.im, 0.7));

	assert(a == Complex(1.0, 2.0));
	assert(b == Complex(3.0, -1.0));
}

void testCompoundAssignmentOperators()
{
	std::cout << "=== testCompoundAssignmentOperators ===" << std::endl;
	Complex a(1.0, 2.0);
	const Complex b(3.0, -1.0);

	a += b;
	std::cout << "a = ";
	a.show();
	assert(a == Complex(4.0, 1.0));
	a -= b;
	std::cout << "a = ";
	a.show();
	assert(a == Complex(1.0, 2.0));
	a *= b;
	std::cout << "a = ";
	a.show();
	assert(a == Complex(5.0, 5.0));
	a /= b;
	std::cout << "a = ";
	a.show();
	assert(a == Complex(1.0, 2.0));

	assert(&(a += b) == &a);
	assert(&(a -= b) == &a);
	assert(&(a *= b) == &a);
	assert(&(a /= b) == &a);
}

void testCompoundAssignmentOnItself()
{
	std::cout << "=== testCompoundAssignmentOnItself ===" << std::endl;
	Complex a(1.0, 2.0);
	a += a;
	assert(a == Complex(2.0, 4.0));
	a *= a;
	std::cout << "a = ";
	a.show();
	assert(a == Complex(-12.0, 16.0));
	a /= a;
	assert(a == Complex(1.0, 0.0));
	a -= a;
	assert(a == Complex(0.0, 0.0));
}

void testChainedAddAssign()
{
	std::cout << "=== testChainedAddAssign ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	const Complex c(2.0, 0.5);

	std::cout << "a += b += c = ";
	(a += b += c).show();
	std::cout << "b = ";
	b.show();
	assert(b == Complex(5.0, -0.5));
	assert(a == Complex(6.0, 1.5));
	assert(c == Complex(2.0, 0.5));
}

void testParenthesizedAddAssign()
{
	std::cout << "=== testParenthesizedAddAssign ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	const Complex c(2.0, 0.5);

	std::cout << "(a += b) += c = ";
	((a += b) += c).show();
	std::cout << "b = ";
	b.show();
	assert(a == Complex(6.0, 1.5));
	assert(b == Complex(3.0, -1.0));
	assert(c == Complex(2.0, 0.5));
}

void testChainedMultiplyAssign()
{
	std::cout << "=== testChainedMultiplyAssign ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	const Complex c(2.0, 0.5);

	std::cout << "a *= b *= c = ";
	(a *= b *= c).show();
	std::cout << "b = ";
	b.show();
	assert(b == Complex(6.5, -0.5));
	assert(a == Complex(7.5, 12.5));
	assert(c == Complex(2.0, 0.5));
}

void testParenthesizedMultiplyAssign()
{
	std::cout << "=== testParenthesizedMultiplyAssign ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	const Complex c(2.0, 0.5);

	std::cout << "(a *= b) *= c = ";
	((a *= b) *= c).show();
	std::cout << "b = ";
	b.show();
	assert(a == Complex(7.5, 12.5));
	assert(b == Complex(3.0, -1.0));
	assert(c == Complex(2.0, 0.5));
}

void testMixedWithDouble()
{
	std::cout << "=== testMixedWithDouble ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex b(3.0, -1.0);
	Complex c(3.5);

	std::cout << "a + 7.2 = ";
	(a + 7.2).show();
	std::cout << "7.2 + a = ";
	(7.2 + a).show();
	std::cout << "b * 5.1 = ";
	(b * 5.1).show();
	std::cout << "5.1 * b = ";
	(5.1 * b).show();
	std::cout << "c == 3.5 = " << (c == 3.5) << std::endl;
	std::cout << "3.5 == c = " << (3.5 == c) << std::endl;
	assert(a + 7.2 == Complex(1.0 + 7.2, 2.0));
	assert(7.2 + a == a + 7.2);
	assert(b * 5.1 == Complex(3.0 * 5.1, -5.1));
	assert(5.1 * b == b * 5.1);
	assert(c == 3.5);
	assert(3.5 == c);
	assert(c != 3.0);
	assert(3.0 != c);
	assert(a != 1.0);

	assert(a - 1.0 == Complex(0.0, 2.0));
	assert(1.0 - a == Complex(0.0, -2.0));
	assert(a / 2.0 == Complex(0.5, 1.0));
	assert(10.0 / Complex(1.0, 2.0) == Complex(2.0, -4.0));

	a += 1.0;
	a *= 2.0;
	assert(a == Complex(4.0, 4.0));
	a -= 4.0;
	a /= 4.0;
	assert(a == Complex(0.0, 1.0));
}

void testComparisonOperators()
{
	std::cout << "=== testComparisonOperators ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex same(1.0, 2.0);
	Complex otherRe(9.0, 2.0);
	Complex otherIm(1.0, 9.0);
	std::cout << "a == same = " << (a == same) << std::endl;
	std::cout << "a != same = " << (a != same) << std::endl;
	std::cout << "a == otherRe = " << (a == otherRe) << std::endl;
	assert(a == same && !(a != same));
	assert(a != otherRe && !(a == otherRe));
	assert(a != otherIm && !(a == otherIm));
	assert(a == a);
}

void testAmplitudeAndPhase()
{
	std::cout << "=== testAmplitudeAndPhase ===" << std::endl;
	Complex a(3.0, 4.0);
	std::cout << "a.amplitude() = " << (a.amplitude()) << std::endl;
	std::cout << "a.phase() = " << (a.phase()) << std::endl;
	assert(a.amplitude() == 5.0);
	assert(approxEqual(a.phase(), std::atan2(4.0, 3.0)));

	assert(approxEqual(Complex(1.0, 0.0).phase(), 0.0));
	assert(approxEqual(Complex(0.0, 1.0).phase(), M_PI / 2));
	assert(approxEqual(Complex(-1.0, 0.0).phase(), M_PI));
	assert(approxEqual(Complex(0.0, -1.0).phase(), -M_PI / 2));
	assert(approxEqual(Complex(1.0, -1.0).phase(), -M_PI / 4));
	assert(approxEqual(Complex(-1.0, -1.0).amplitude(), std::sqrt(2.0)));
	assert(Complex().amplitude() == 0.0);
	assert(Complex().phase() == 0.0);

	double r = a.amplitude();
	double phi = a.phase();
	Complex rebuilt(r * std::cos(phi), r * std::sin(phi));
	assert(approxEqual(rebuilt.re, a.re) && approxEqual(rebuilt.im, a.im));
}

void testConstComplex()
{
	std::cout << "=== testConstComplex ===" << std::endl;
	const Complex a(1.0, 2.0);
	const Complex b(3.0, -1.0);
	Complex c(2.0, 0.5);

	std::cout << "a = ";
	a.show();
	std::cout << "a + b = ";
	(a + b).show();
	std::cout << "a * c = ";
	(a * c).show();
	assert(a.re == 1.0 && a.im == 2.0);
	assert(a + b == Complex(4.0, 1.0));
	assert(a - b == Complex(-2.0, 3.0));
	assert(a * b == Complex(5.0, 5.0));
	assert((a * b) / b == a);
	assert(a + 7.2 == 7.2 + a);
	assert(b * 5.1 == 5.1 * b);
	assert(a != b);
	assert(Complex(3.0, 4.0) == Complex(3.0, 4.0));

	c += a;
	assert(c == Complex(3.0, 2.5));
	c *= b;
	assert(c == Complex(11.5, 4.5));

	const Complex p(0.0, 2.0);
	assert(p.amplitude() == 2.0);
	assert(approxEqual(p.phase(), M_PI / 2));
}

void testDivisionByZero()
{
	std::cout << "=== testDivisionByZero ===" << std::endl;
	Complex a(1.0, 2.0);
	Complex q = a / Complex();
	std::cout << "q = ";
	q.show();
	assert(std::isnan(q.re) || std::isinf(q.re));
}

int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	testConstructionAndFieldAccess();
	testStreamInsertion();
	testArithmeticOperators();
	testCompoundAssignmentOperators();
	testCompoundAssignmentOnItself();
	testChainedAddAssign();
	testParenthesizedAddAssign();
	testChainedMultiplyAssign();
	testParenthesizedMultiplyAssign();
	testMixedWithDouble();
	testComparisonOperators();
	testAmplitudeAndPhase();
	testConstComplex();
	testDivisionByZero();
	std::cout << "All tests passed" << std::endl;
	return 0;
}
