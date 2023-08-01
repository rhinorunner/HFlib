#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <functional>

// Helpful Functions library
namespace hfl {

/**
 * @brief Converts any angle to an angle between 0 and 360.
 * 
 * @param angle the angle to convert
 * 
 * @return the converted angle
*/
constexpr float normalizeAngle(float angle) {
	while (angle < 0)    angle += 360;
	while (angle >= 360) angle -= 360;
	return angle;
}

/**
 * @brief Gets the difference between 2 angles.
 * 
 * @param angle1 the first angle
 * @param angle2 the second angle
 * 
 * @return the difference between the 2 angles
*/
uint16_t diffBetweenAngles(
	const uint16_t& angle1, 
	const uint16_t& angle2
) {
	uint16_t diffAdd = 0;
	uint16_t diffSub = 0;
	
	while (normalizeAngle(angle1 + diffAdd) != angle2) diffAdd++;
	while (normalizeAngle(angle1 - diffSub) != angle2) diffSub++;

	return (diffAdd < diffSub) ? diffAdd : diffSub;
}

/**
 * @brief Gets the greatest common denominator of 2 numbers.
 * 
 * @param a the first number
 * @param b the second number
 * 
 * @return the greatest common denominator of the 2 numbers
*/
int64_t gcd(
	const int64_t& a, 
	const int64_t& b
) {
	//#pragma COMPILER diagnostic push
	//#pragma COMPILER diagnostic ignored "-Wmisleading-indentation"
    if (!a)    return b;
    if (!b)    return a;
    if (a < b) return gcd(a, b % a);
               return gcd(b, a % b);
	//#pragma COMPILER diagnostic pop
}

class Real {
	virtual double eval();
};

class Rational : Real {
public:
	Rational(const double dec) {
		double decPart = dec - (int64_t)dec;
		// get the whole part
		[[maybe_unused]] int64_t wholePart = (int64_t)dec;
		// get the numerator
		int64_t numerator = decPart * 1000000000;
		// get the denominator
		int64_t denominator = 1000000000;
		// reduce the fraction
		int64_t gcd1 = gcd(numerator, denominator);
		numerator /= gcd1;
		denominator /= gcd1;
		// return the fraction
		num = numerator;
		den = denominator;
	}
	Rational(const int inum, const int iden) {
		num = inum;
		den = iden;
	}

	Rational multiply(Rational y) {
		Rational(num * y.num, den * y.den).simplify();
		return *this;
	}

	Rational divide(Rational y) {
		Rational(num * y.den, den * y.num).simplify();
		return *this;
	}

	Rational add(Rational y) {
		int64_t cd = gcd(den, y.den);
		int64_t dxnum = (cd/den) * num;
		int64_t dynum = (cd/y.den) * y.num;

		return Rational(dxnum + dynum, cd).simplify();
	}

	Rational subtract(Rational y) {
		Rational n = y.multiply(Rational(-1, 1));
		return this->add(n);
	}

	Rational simplify() {
		Rational(num / gcd(num, den), den/gcd(num,den));
		return *this;
	}

	double eval() {
		return num / den;
	}

private:
	int64_t num;
	int64_t den;
};

class Radical : Real {
private:
	Rational deg;
	Rational radicand;

	double eval() {
		return std::pow(radicand.eval(), 1/deg.eval());
	}

};


/**
 * @brief Converts an unsigned int into a number with a variable amount of bits.
 * 
 * @param val the value to convert
 * @param bits the amount of bits to convert to
 * 
 * @return the converted value
*/
constexpr inline uint64_t formatBits(
	const uint64_t& val,
	const uint16_t& bits
) {return val & UINT64_MAX >> (64-bits);}

class Gauss {
public:
	Gauss(int64_t sigma, int64_t mu) : stddiv(sigma), mean(mu) {}

	double get(double x) {
		double coeff = 1/(stddiv*sqrt(6.283185307179586));
		double expo = pow((x-stddiv)/mean, 2) * (-1/2);
		return coeff * exp(expo);
	}

	double sample() {
		return get((double)rand()/(double)rand());
	}
private:
	int64_t stddiv;
	int64_t mean;
};

/**
 * @brief A class for generating good random numbers.
*/
class Rand {
private:
	int64_t seed;

	Rand(int64_t s) : seed(s) {}
	Rand(void) {
		seed = std::chrono::system_clock::now().time_since_epoch().count() - __LINE__;
	}
	int64_t genRand() {
		seed = 
			std::chrono::system_clock::now().time_since_epoch().count() 
			* __LINE__
			* seed
			>> 3
			+ __LINE__
		;
		return seed;
	}
public:
	double getSample() {
		Gauss dist = Gauss(1, 0);
		return dist.sample();
	}
	double getSampleCustom(int64_t sigma, int64_t mu) {
		Gauss dist = Gauss(sigma, mu);
		return dist.sample();
	}
	int64_t getInt() {
		return genRand();
	}
	double getFloat() {
		return (double)genRand()/(double)genRand();
	}
};

/**
 * @brief Returns all the prime numbers up to a certain number.
 * 
 * @param ceiling the number to get primes up to
 * 
 * @return a vector of all the prime numbers up to the ceiling
*/
std::vector<uint64_t> getPrimes(uint64_t ceiling) {
	std::vector<std::pair<uint64_t, bool>> primes;
	std::vector<uint64_t> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	uint64_t maxToAdd = (uint64_t)sqrt(ceiling);
	
	primes.push_back({1,false});
	for (uint64_t i = 2; i < ceiling; i++) 
		primes.push_back({i,true});

	for (auto i : primes) {
		// if number is prime
		if (i.second) {
			primesReturn.push_back(i.first);

			if (i.first < maxToAdd) {
				for (uint64_t x = (i.first * 2); x <= ceiling; x += i.first) {
					if (x > ceiling) break;
					primes[x-1].second = false;
				}
			}
		}
	}
	return primesReturn;
}

/**
 * @brief Returns whether a number is prime or not.
 * 
 * @param n the number to check
 * 
 * @return whether the number is prime or not
*/
constexpr bool isPrime(uint64_t n) {
	if (n == 2) [[unlikely]] return true;
	if ((n < 2) || !(n % 2)) return false;
	
	float sq = ceil(sqrt(n));
	for (uint64_t i = 3; i <= sq; i += 2) {
		if (!(n % i)) return false;
	}
	return true;
}

/**
 * @brief Generates a random 64 bit integer using rand().
 * 
 * @param seed the seed to use for the random number
 * 
 * @return the random number
*/
inline uint64_t rand64(
	uint64_t seed = rand()
) {return ((uint64_t)(rand()) << 32) | seed;}

/**
 * @brief Calculates the factorial of a number. [SLOW IMPLEMENTATION]
 * 
 * @param num the number to calculate the factorial of
 * 
 * @return the factorial of the number
*/
constexpr inline double factorial(uint64_t num) {
	return ((num == 1) || !num) ? 1 : num * factorial(num - 1);
}

namespace constants 
{
	constexpr double pi             = 3.1415926535897932;
	constexpr double e              = 2.7182818284590451;
	constexpr double phi            = 1.6180339887498948;
	constexpr double tau            = 6.2831853071795862;
	constexpr double sqrt2          = 1.4142135623730950;
	constexpr double natLog2	    = 0.6931471805599453;
	constexpr double eulersConst    = 0.5772156649015329;
	constexpr double plankConst     = 6.62607015e-34    ;
	constexpr double avogardosConst = 6.02214076e+23    ;
	constexpr double magicAngle     = 0.9553166181245092;
	constexpr double primeConst     = 0.4146825098511116;
}

};