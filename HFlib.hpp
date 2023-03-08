// Helpful Functions library (HFlib)
// created by Zaine Rehman
// from 12-7-22 to 3-7-23

#ifndef HFLIB_HPP_CHECK
#define HFLIB_HPP_CHECK

#include <iostream>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <chrono>
#include <string>
#include <type_traits>

// OS-specific includes
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// helpful functions library
namespace HFL 
{

// clear screen function
// 0 = 72 newlines (can be changed)
// 1 = system() based clear screen
// 2 = ANSI escape sequence
// 3 = Windows API (not windows 3 = 2)
// 4 = some weird sort of ANSI code?
inline void clear(uint8_t type = 3, uint16_t newLineCharNum = 72) {
	#ifndef _WIN32
	if (type == 3) type = 2;
	#endif
	switch (type) 
	{
		case 0:
			for (uint16_t i = 0; i <= newLineCharNum; ++i) std::cout << '\n';
			break;

		case 1:
			system("cls"); // :(
			break;

		case 2:
			std::cout<<"\e[1;1H\e[2J";
			break;
		
		#ifdef _WIN32
		case 3:
			HANDLE hOut;
			COORD Position;
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			Position.X = 0;
			Position.Y = 0;
			SetConsoleCursorPosition(hOut, Position);
			break;
		#endif

		case 4:
			std::cout << "\033[2J\033[1;1H";
			break;
	}
}

#ifdef _WIN32
// show terminal cursor, doesnt seem to wrok
void WIN_showConsoleCursor(const bool& showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// sets the console to utf-16
inline void utf16Console() {system("chcp 65001");}

#endif

// returns the name of the operating system
inline std::string getOsName() {
	#ifdef _WIN32
	return "Windows";
	#elif __APPLE__
	return "Mac";
	#elif __linux__
	return "Linux";
	#elif __FreeBSD__
	return "FreeBSD";
	#elif __unix
	return "Unix";
	#else
	return "Other";
	#endif
}
// taken from https://stackoverflow.com/questions/15580179/how-do-i-find-the-name-of-an-operating-system

// convert string to vector<char>
std::vector<char> strToCVec(const std::string& str) {
	std::vector<char> converted;
	for (char x : str) {
		converted.push_back(x);
	}
	return converted;
}

// convert vector<char> to string
std::string CVecToStr(const std::vector<char>& cvec) {
	std::string converted;
	for (char x : cvec) {
		converted += x;
	}
	return converted;
}

// converts std::type_info to a more readable std::string
// usage: 
// readTypeid(typeid(...).name())
// extraInfo: if true, returns extra information about the type when present
// NOTE: ONLY FOR GCC AS OF RIGHT NOW
std::string readTypeid (
	const std::type_info& type, 
	const bool& extraInfo = false
) {
	// loopup table for types
	std::vector<std::pair<std::string,std::string>> namesLookup {
		{"v",  "void"              },
		{"w",  "wchar_t"           },
		{"b",  "bool"              },
		{"c",  "char"              },
		{"a",  "signed char"       },
		{"h",  "unsigned char"     },
		{"s",  "short"             },
		{"t",  "unsigned short"    },
		{"i",  "int"               },
		{"j",  "unsigned int"      },
		{"l",  "long"              },
		{"m",  "unsigned long"     },
		{"x",  "long long"         },
		{"y",  "unsigned long long"},
		{"n",  "__int128"          },
		{"o",  "unsigned __int128" },
		{"f",  "float"             },
		{"d",  "double"            },
		{"e",  "long double"       },
		{"g",  "__float128"        },
		{"z",  "ellipsis"          },
		{"Di", "char32_t"          },
		{"Ds", "char16_t"          },
		{"Du", "char8_t"           },
		{"Da", "auto"              },
		{"Dc", "decltype(auto)"    },
		{"Dn", "std::nullptr_t"    }
	};

	std::string temp = std::string(type.name());
	if (temp.size() > 10) 
		if (temp.substr(0, 10) == "St6vectorI") 
			return "std::vector";

	for (auto x : namesLookup) 
		if (temp == x.first) return x.second;

	if (type == typeid(std::string)) 
		return "std::string";

	return "unknown";
}

// converts any angle to an angle between 0 and 360
float normalizeAngle(float angle) {
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


// returns the index(es) of a value in a vector
template <typename T>
std::vector<uint64_t> getIndexes(
	const std::vector<T>& vector,
	const T& value
) {
	std::vector<uint16_t> indexes;
	for (uint64_t i = 0; i < value.size(); i++) 
		if (vector[i] == value) indexes.push_back(i);
	return indexes;
}


// better random!
class BetterRand {
public:
	// adds this to random each time, optional
	int32_t extraRand;
	BetterRand(const int32_t& ExtraRand = 0) : extraRand(ExtraRand){};
	uint32_t genRand(
		const int32_t &extra = 4, 
		bool resetExtraRand = true, 
		int32_t resetERextraIt = 2
	) {
		if (resetExtraRand)
		  extraRand = genRand(resetERextraIt, false);
		// set random to unix time
		auto cool = std::chrono::system_clock::now();
		auto very =
		    (unsigned int)
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

// wrapper for std::vector
template <typename T>
class VecWrapper 
{
private:
	std::vector<T> internalVec;
	std::vector<std::string> vecLog {};
	uint64_t callNum = 0;

	void log (
		const std::string& function,
		const std::string& message
	) {
		if (!logBool) return;
		callNum++;
		std::string strToPush = 
			"[call "
			+ std::to_string(callNum) 
			+ "] <"
			+ function
			+ "> : "
			+ message;
		vecLog.push_back(strToPush);
	}

public:
	std::string printSep = ", ";
	bool logBool = true;
	std::vector<std::string>* storedLog = nullptr;
	
	// empty constructor
	VecWrapper() {
		log("constructor", "constructed wrapper (no args)");
	}

	// parameter pack constructor
	template <typename... Args>
	explicit VecWrapper(Args... args) {
		// i hate how this looks
		(internalVec.push_back(args), ...);
		log("constructor", "constructed wrapper with packed args");
	}

	~VecWrapper() {
		log("destructor", "destructed wrapper");
		if (storedLog != nullptr) {
			*storedLog = vecLog;
		}
	}
	
	// return size of vector
	uint64_t size() {
		log("size", "returned size");
		return internalVec.size();
	}

	// push back
	bool push_back(const T& value) {
		internalVec.push_back(value);
		log("push_back", "pushed back value");
		return true;
	}
	// pop back
	bool pop_back() {
		if (internalVec.empty()) {
			log("pop_back", "!attempted to pop empty vec!");
			return false;
		}
		internalVec.pop_back();
		log("pop_back", "popped back value");
		return true;
	}
	// push front
	bool push_front(const T& value) {
		internalVec.insert(internalVec.begin(), value);
		log("push_front", "pushed front value");
		return true;
	}
	// pop front
	bool pop_front() {
		if (internalVec.empty()) {
			log("pop_front", "!attempted to pop empty vec!");
			return false;
		}
		internalVec.erase(internalVec.begin());
		log("pop_front", "popped front value");
		return true;
	}

	// delete specific index
	bool del(const uint64_t& index) {
		if (index >= internalVec.size()) {
			log("del", "!attempted to delete value at index " + std::to_string(index) + " (out of bounds)!");
			return false;
		}
		internalVec.erase(internalVec.begin() + index);
		log("del", "deleted value at index " + std::to_string(index));
		return true;
	}

	// resize vector
	bool resize(const uint64_t& newSize) {
		internalVec.resize(newSize);
		log("resize", "resized vector to size " + std::to_string(newSize));
		return true;
	}

	// iterator begin
	typename std::vector<T>::iterator begin() {
		log("begin", "returned begin iterator");
		return internalVec.begin();
	}
	// iterator end
	typename std::vector<T>::iterator end() {
		log("end", "returned end iterator");
		return internalVec.end();
	}
	// reverse iterator begin
	typename std::vector<T>::reverse_iterator r_begin() {
		log("rbegin", "returned reverse begin iterator");
		return internalVec.rbegin();
	}
	// reverse iterator end
	typename std::vector<T>::reverse_iterator r_end() {
		log("rend", "returned reverse end iterator");
		return internalVec.rend();
	}

	// return vector
	std::vector<T> getVec() {
		log("getVec", "returned internal vector value");
		return &internalVec;
	}

	// return printable string version of vector
	std::string vToStr() {
		std::string str {};
		//if (std::is_convertible<T, std::string>::value) 
		for (uint64_t i = 0; i < internalVec.size(); i++)  {
			str += std::to_string(internalVec[i]) 
				+ (i == internalVec.size()-1 ? "" : printSep);
		}
		log("vToStr", "returned vector as string");
		return str;
	}

	// return log
	std::vector<std::string> getLog() {
		log("getLog", "returned log");
		return vecLog;
	}
	// return printable string version of log
	std::string logToStr(std::string& tSep = " ") {
		std::string str {};
		for (uint64_t i = 0; i < vecLog.size(); i++)
			str += 
				"{"
				+ vecLog[i]
				+ "}"
				+ tSep;
		log("logToStr", "returned log as string");
		return str;
	}

	// compare vector
	T operator== (const std::vector<T>& comparison) {
		log("operator==", "compared vector");
		return (internalVec == comparison);
	}

	// get value
	T operator[] (const uint64_t& index) {
		if (index >= internalVec.size()) {
			log("operator[]", "accessed index " + (std::string)index + " (out of bounds");
			// fuck, what the hell is the user doing
			return 1;
		}
		log("operator[]", "accessed index " + (std::string)index);
		return internalVec[index];
	}

	// return indexes where the value is present
	T operator() (const T& value) {
		std::vector<uint64_t> indexes {};
		for (uint64_t i = 0; i < internalVec.size(); i++) 
			if (internalVec[i] == value) 
				indexes.push_back(i);
		log("operator()", "returned indexes of value " + value);
		return indexes;
	}

	// remove the last element
	void operator-- () {
		internalVec.pop_back();
		log("operator--", "popped back");
	}

	// append value to vector
	void operator+= (const T& value) {
		internalVec.push_back(value);
		log("operator+=", "added value");
	}
	// append vector to vector
	void operator+= (const std::vector<T>& vec) {
		internalVec.insert(
			internalVec.end(), 
			vec.begin(), 
			vec.end()
		);
		log("operator+=", "added vector values");
	}
	// append VecWrapper vector to vector
	void operator+= (const VecWrapper& vec) {
		internalVec.insert(
			internalVec.end(), 
			vec.internalVec.begin(), 
			vec.internalVec.end()
		);
		log("operator+=", "added VecWrapper vector values");
	}

	// assign internal vector to new vector
	void operator= (std::vector<T> newish) {
		internalVec = newish;
		log("operator=", "assigned new vector");
	}
	// assign internal vector to new vector from other VecWrapper
	void operator= (VecWrapper newish) {
		internalVec = newish.internalVec;
		log("operator=", "assigned new vector from VecWrapper");
	}

	// ostream operator: print vector with sep in between
	friend std::ostream& operator<< (
		std::ostream& os, VecWrapper& VW
	) {
		os << VW.vToStr();
		VW.log("std::ostream operator<<", "printed vector");
		return os;
	}
};

// VARIABLES GO PAST HERE

// mathematical constants
namespace constants 
{
	constexpr long double pi     = 3.1415926535897932;
	constexpr long double e      = 2.7182818284590451;
	constexpr long double gRatio = 1.61803398874989  ;
}

// terminal ASCII colors
namespace TermColors 
{
	std::string reset   = "\u001b[0m";

	// normal

	std::string black   = "\u001b[30m";
	std::string red     = "\u001b[31m";
	std::string green   = "\u001b[32m";
	std::string yellow  = "\u001b[33m";
	std::string blue    = "\u001b[34m";
	std::string magenta = "\u001b[35m";
	std::string cyan    = "\u001b[36m";
	std::string white   = "\u001b[37m";

	// bright
	// sometimes doesnt work

	std::string BRI_black   = "\u001b[30m;1m";
	std::string BRI_red     = "\u001b[31m;1m";
	std::string BRI_green   = "\u001b[32m;1m";
	std::string BRI_yellow  = "\u001b[33m;1m";
	std::string BRI_blue    = "\u001b[34m;1m";
	std::string BRI_magenta = "\u001b[35m;1m";
	std::string BRI_cyan    = "\u001b[36m;1m";
	std::string BRI_white   = "\u001b[37m;1m";

	// backgrounds

	std::string BACK_black   = "\u001b[40m";
	std::string BACK_red     = "\u001b[41m";
	std::string BACK_green   = "\u001b[42m";
	std::string BACK_yellow  = "\u001b[43m";
	std::string BACK_blue    = "\u001b[44m";
	std::string BACK_magenta = "\u001b[45m";
	std::string BACK_cyan    = "\u001b[46m";
	std::string BACK_white   = "\u001b[47m";

	// bright backgrounds
	// sometimes doesnt work

	std::string BRI_BACK_black   = "\u001b[40m;1m";
	std::string BRI_BACK_red     = "\u001b[41m;1m";
	std::string BRI_BACK_green   = "\u001b[42m;1m";
	std::string BRI_BACK_yellow  = "\u001b[43m;1m";
	std::string BRI_BACK_blue    = "\u001b[44m;1m";
	std::string BRI_BACK_magenta = "\u001b[45m;1m";
	std::string BRI_BACK_cyan    = "\u001b[46m;1m";
	std::string BRI_BACK_white   = "\u001b[47m;1m";

	// others

	std::string BOLD   = "\u001b[1m";
	std::string UNDERL = "\u001b[4m";
	std::string REVRSD = "\u001b[7m";
}

// periodic table
static const std::vector<std::vector<std::string>> periodicTable 
{
	{"1.0079"  , "Hydrogen"      , "H" , "1"  },
	{"4.00260" , "Helium"        , "He", "2"  },
	{"6.941"   , "Lithium"       , "Li", "3"  },
	{"9.0122"  , "Beryllium"     , "Be", "4"  },
	{"10.811"  , "Boron"         , "B" , "5"  },
	{"12.0107" , "Carbon"        , "C" , "6"  },
	{"14.0067" , "Nitrogen"      , "N" , "7"  },
	{"15.9994" , "Oxygen"        , "O" , "8"  },
	{"18.9984" , "Fluorine"      , "F" , "9"  },
	{"20.1797" , "Neon"          , "Ne", "10" },
	{"22.9897" , "Sodium"        , "Na", "11" },
	{"24.305"  , "Magnesium"     , "Mg", "12" },
	{"26.9815" , "Aluminum"      , "Al", "13" },
	{"28.0855" , "Silicon"       , "Si", "14" },
	{"30.9738" , "Phosphorus"    , "P" , "15" },
	{"32.065"  , "Sulfur"        , "S" , "16" },
	{"35.453"  , "Chlorine"      , "Cl", "17" },
	{"39.0983" , "Potassium"     , "K" , "19" },
	{"39.948"  , "Argon"         , "Ar", "18" },
	{"40.078"  , "Calcium"       , "Ca", "20" },
	{"44.9559" , "Scandium"      , "Sc", "21" },
	{"47.867"  , "Titanium"      , "Ti", "22" },
	{"50.9415" , "Vanadium"      , "V" , "23" },
	{"51.9961" , "Chromium"      , "Cr", "24" },
	{"54.938"  , "Manganese"     , "Mn", "25" },
	{"55.845"  , "Iron"          , "Fe", "26" },
	{"58.6934" , "Nickel"        , "Ni", "28" },
	{"58.9332" , "Cobalt"        , "Co", "27" },
	{"63.546"  , "Copper"        , "Cu", "29" },
	{"65.39"   , "Zinc"          , "Zn", "30" },
	{"69.723"  , "Gallium"       , "Ga", "31" },
	{"72.64"   , "Germanium"     , "Ge", "32" },
	{"74.9216" , "Arsenic"       , "As", "33" },
	{"78.96 "  , "Selenium"      , "Se", "34" },
	{"79.904"  , "Bromine"       , "Br", "35" },
	{"83.8"    , "Krypton"       , "Kr", "36" },
	{"85.4678" , "Rubidium"      , "Rb", "37" },
	{"87.62"   , "Strontium"     , "Sr", "38" },
	{"88.9059" , "Yttrium"       , "Y" , "39" },
	{"91.224"  , "Zirconium"     , "Zr", "40" },
	{"92.9064" , "Niobium"       , "Nb", "41" },
	{"95.94"   , "Molybdenum"    , "Mo", "42" },
	{"98"      , "Technetium"    , "Tc", "43" },
	{"101.07"  , "Ruthenium"     , "Ru", "44" },
	{"102.905" , "Rhodium"       , "Rh", "45" },
	{"106.42"  , "Palladium"     , "Pd", "46" },
	{"107.868" , "Silver"        , "Ag", "47" },
	{"112.411" , "Cadmium"       , "Cd", "48" },
	{"114.818" , "Indium"        , "In", "49" },
	{"118.71"  , "Tin"           , "Sn", "50" },
	{"121.76"  , "Antimony"      , "Sb", "51" },
	{"126.904" , "Iodine"        , "I" , "53" },
	{"127.6"   , "Tellurium"     , "Te", "52" },
	{"131.293" , "Xenon"         , "Xe", "54" },
	{"132.905" , "Cesium"        , "Cs", "55" },
	{"137.327" , "Barium"        , "Ba", "56" },
	{"138.905" , "Lanthanum"     , "La", "57" },
	{"140.116" , "Cerium"        , "Ce", "58" },
	{"140.907" , "Praseodymium"  , "Pr", "59" },
	{"144.24"  , "Neodymium"     , "Nd", "60" },
	{"145"     , "Promethium"    , "Pm", "61" },
	{"150.36"  , "Samarium"      , "Sm", "62" },
	{"151.964" , "Europium"      , "Eu", "63" },
	{"157.25"  , "Gadolinium"    , "Gd", "64" },
	{"158.925" , "Terbium"       , "Tb", "65" },
	{"162.5"   , "Dysprosium"    , "Dy", "66" },
	{"164.930" , "Holmium"       , "Ho", "67" },
	{"167.259" , "Erbium"        , "Er", "68" },
	{"168.934" , "Thulium"       , "Tm", "69" },
	{"173.04"  , "Ytterbium"     , "Yb", "70" },
	{"174.967" , "Lutetium"      , "Lu", "71" },
	{"178.49"  , "Hafnium"       , "Hf", "72" },
	{"180.947" , "Tantalum"      , "Ta", "73" },
	{"183.84"  , "Tungsten"      , "W" , "74" },
	{"186.207" , "Rhenium"       , "Re", "75" },
	{"190.23"  , "Osmium"        , "Os", "76" },
	{"192.217" , "Iridium"       , "Ir", "77" },
	{"195.078" , "Platinum"      , "Pt", "78" },
	{"196.966" , "Gold"          , "Au", "79" },
	{"200.59"  , "Mercury"       , "Hg", "80" },
	{"204.383" , "Thallium"      , "Tl", "81" },
	{"207.2"   , "Lead"          , "Pb", "82" },
	{"208.980" , "Bismuth"       , "Bi", "83" },
	{"209"     , "Polonium"      , "Po", "84" },
	{"210"     , "Astatine"      , "At", "85" },
	{"222"     , "Radon"         , "Rn", "86" },
	{"223"     , "Francium"      , "Fr", "87" },
	{"226"     , "Radium"        , "Ra", "88" },
	{"227"     , "Actinium"      , "Ac", "89" },
	{"231.035" , "Protactinium"  , "Pa", "91" },
	{"232.038" , "Thorium"       , "Th", "90" },
	{"237"     , "Neptunium"     , "Np", "93" },
	{"238.028" , "Uranium"       , "U" , "92" },
	{"243"     , "Americium"     , "Am", "95" },
	{"244"     , "Plutonium"     , "Pu", "94" },
	{"247"     , "Curium"        , "Cm", "96" },
	{"247"     , "Berkelium"     , "Bk", "97" },
	{"251"     , "Californium"   , "Cf", "98" },
	{"252"     , "Einsteinium"   , "Es", "99" },
	{"257"     , "Fermium"       , "Fm", "100"},
	{"258"     , "Mendelevium"   , "Md", "101"},
	{"259"     , "Nobelium"      , "No", "102"},
	{"261"     , "Rutherfordium" , "Rf", "104"},
	{"262"     , "Lawrencium"    , "Lr", "103"},
	{"262"     , "Dubnium"       , "Db", "105"},
	{"264"     , "Bohrium"       , "Bh", "107"},
	{"266"     , "Seaborgium"    , "Sg", "106"},
	{"268"     , "Meitnerium"    , "Mt", "109"},
	{"272"     , "Roentgenium"   , "Rg", "111"},
	{"277"     , "Hassium"       , "Hs", "108"},
	{"281"     , "Darmstadtium"  , "Ds", "110"},
	{"285"     , "Copernicium"   , "Cn", "112"},
	{"286"     , "Nihonium"      , "Nh", "113"},
	{"289"     , "Flerovium"     , "Fl", "114"},
	{"289"     , "Moscovium"     , "Mc", "115"},
	{"293"     , "Livermorium"   , "Lv", "116"},
	{"294"     , "Tennessine"    , "Ts", "117"},
	{"295.216" , "Oganesson"     , "Og", "118"}
};

};

#endif
