#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <chrono>

// Helpful Functions library
namespace HFL {

// converts radians to degrees
constexpr double radToDeg(const double& rad) 
	{return rad * (180 / 3.1415926535929);}
// converts degrees to radians
constexpr double degToRad(const double& deg) 
	{return deg * (3.1415926535929 / 180);}

// converts any angle to an angle between 0 and 360
constexpr float normalizeAngle(float angle) {
	while (angle < 0)    angle += 360;
	while (angle >= 360) angle -= 360;
	return angle;
}

// gets the difference between 2 angles
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

// returns the gcd of 2 numbers
int64_t gcd(
	const int64_t& a, 
	const int64_t& b
) {
    if (!a)    return b;
    if (!b)    return a;
    if (a < b) return gcd(a, b % a);
               return gcd(b, a % b);
}

// converts a decimal to a fraction
std::string decToFrac(const double& dec) {
	// get the decimal part
	double decPart = dec - (int64_t)dec;
	// get the whole part
	int64_t wholePart = (int64_t)dec;
	// get the numerator
	int64_t numerator = decPart * 1000000000;
	// get the denominator
	int64_t denominator = 1000000000;
	// reduce the fraction
	int64_t gcd1 = gcd(numerator, denominator);
	numerator /= gcd1;
	denominator /= gcd1;
	// return the fraction
	return 
		  std::to_string(wholePart) 
		+ " " 
		+ std::to_string(numerator) 
		+ "/" 
		+ std::to_string(denominator);
}

// solves for thr pythagorean theorem
// input the side to solve for and 2 side values
// if solving for A/B use val 1 as C
double pyth(
	const char& side, 
	const double& val1, 
	const double& val2
) {
	if (side == 'c') 
		return sqrt(pow(val1, 2) + pow(val2, 2));
	return sqrt(pow(val1, 2) - pow(val2, 2));
}

// solves for the quadratic formula
// returns both solutions
std::pair<double,double> quadratic(
	const double& a,
	const double& b,
	const double& c
) {
	double R1, R2;
	try { R1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); } 
	catch (...) {R1 = 0;}
	try { R2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); } 
	catch (...) {R2 = 0;}
	return {R1,R2};
}

// converts an unsigned int into a number with a variable amount of bits
constexpr inline uint64_t formatBits(
	const uint64_t& val,
	const uint16_t& bits
) {return val & UINT64_MAX >> (64-bits);}

// better random!
class BetterRand {
public:
	// adds this to random each time, optional
	uint64_t extraRand;
	BetterRand(const uint64_t& ExtraRand = 0) : extraRand(ExtraRand){};
	uint64_t genRand(
		const uint64_t &extra = 4, 
		bool resetExtraRand = true, 
		uint64_t resetERextraIt = 2
	) {
		if (resetExtraRand)
		  extraRand = genRand(resetERextraIt, false);
		// set random to unix time
		auto cool = std::chrono::system_clock::now();
		auto very =
		    (uint64_t)
			std::chrono::time_point_cast<std::chrono::milliseconds>
			(cool).time_since_epoch().count();
		// add random()
		if (extra >= 1)
			very -= rand();
		// add line number
		if (extra >= 2)
			very += __LINE__;
		// add an iteration (extra = 2)
		if (extra >= 3)
			very += genRand(2, false);
		// bitshift right or left based on another iteration
		if (extra >= 4)
			(genRand(2, false)) % 2 ? very >>= 1 : very <<= 1;
		
		// do stuff for the rest of the time i guess
		if (extra >= 5) {
			for (uint32_t i = 0; i < extra-5; i++) {
				switch(genRand(2, false) % 4) 
				{
					case 0:
						very += genRand(((genRand(2) % 4)+1), false);
						break;
					case 1:
						very -= genRand(((genRand(2) % 4)+1), false);
						break;
					case 2:
						very *= genRand(((genRand(2) % 4)+1), false);
						break;
					case 3:
						very /= genRand(((genRand(2) % 4)+1), false);
						break;
				}
			}
		}		
		return (very + extraRand);
	}
};

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