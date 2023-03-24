
# Helpful Functions Libary

###### created by Zaine Rehman
###### *Latest release is v1.0.0, published 3-23-23* <!-- :) -->

# 
### What is Helpful Functions Library?
Helpful Functions Library (HFlib) is a collection of C++ implementation files that provide helpful functions, classes, and variables for various different purposes.

# 
### Usage
There are currently 5 different files:
- `HF_basics.hpp`
- `HF_math.hpp`
- `HF_misc.hpp`
- `HF_types.hpp`
- `HFlib.hpp`

Each file holds different functions according to what they would be used for (for example, `HF_math` has math related things and `HF_types` has variable types.) 
`HFlib.hpp` includes all other HFlib files. 

To use, simply place the `HFlib` folder inside your project directory and include `.hpp` files from it. **Everything will be inside of the `HFL` namespace.**

# 
### HFlib.hpp
The main file. It includes all of the other files, so if you `include` it there is no reason to include any of the other files. 

# 
### HF_basics.hpp
This file holds basic functions, such as a clear screen function or a function that gets the OS name. 

## 
#### clear
`inline void clear(uint8_t type = 3, uint16_t newLineCharNum = 72)`

Clears the terminal screen. 
`uint8_t type`: changes the method in which the screen is cleared. 
`uint16_t newLineCharNum`: changes the number of newline characters printed to the terminal when `type == 0`

types (changed with `type`):
- 0 = 72 newlines (can be changed with newLineCharNum)
- 1 = system() based clear screen
- 2 = ANSI escape sequence
- 3 = Windows API *(if not using windows, this will use type 2)*
- 4 = different ANSI code


###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << "I will be cleared\n";
    HFL::clear();
    std::cout << "You will only see me\n";
    return 0;
}
```
output: 
```
You will only see me
```

## 
#### getOsName
`inline std::string getOsName()`

Returns a string that holds the name of the OS being used. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << HFL::getOsName() << '\n';
    return 0;
}
```
output (on a Windows machine):
```
Windows
```
##
#### WIN_setConsoleCursor
`void WIN_setConsoleCursor(const bool& showFlag)`
###### *Windows only*
###### !!! DOES NOT WORK !!!
Sets the cursor visibility. 

##
#### WIN_utf16Console
`inline void WIN_utf16Console()`

###### *Windows only*
Sets the console from the default 8-bits to 16-bits. 
###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << "∞" << '\n';
    HFL::WIN_utf16Console();
    std::cout << "∞" << '\n';
    return 0;
}
```
output:
```
Γê₧
Active code page: 65001
∞
```
*please note that `Active code page: 65001` will be printed when the function is used, so using `HFL::clear()` afterward is recommended.*

##
#### strToCVec
`std::vector<char> strToCVec(const std::string& str)`

Converts `std::string` to `std::vector<char>`

##
#### cVecToStr
`std::string CVecToStr(const std::vector<char>& cvec)`

Converts `std::vector<char>` to `std::string`

##
#### getIndexes
`template <typename T> std::vector<uint64_t> getIndexes(const std::vector<T>& vector,const T& value)`

Returns the indexes that the vector has the values at. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::vector<char> vec {'a','b','a','e'};
    auto indexes = HFL::getIndexes<char>(vec,'a');

    for (auto& i : indexes) {
        std::cout << (short)i << '\n';
    }

    return 0;
}
```
output:
```
0
2
```

#
### HF_math.hpp
This file holds functions related to math

##
#### radToDeg
`constexpr double radToDeg(const double& rad)`

Converts a radian value to degrees. 

##
#### degToRad
`constexpr double degToRad(const double& deg)`

Converts a degree value to radians. 

##
#### normalizeAngle
`constexpr float normalizeAngle(float angle)`

Turns any angle (in degrees) into an angle between 0 and 360. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << HFL::normalizeAngle(400) << '\n';
	std::cout << HFL::normalizeAngle(0) << '\n';
	std::cout << HFL::normalizeAngle(-330) << '\n';
	std::cout << HFL::normalizeAngle(3821) << '\n';
	std::cout << HFL::normalizeAngle(360) << '\n';
    return 0;
}
```
output:
```
40
0
30
221
0
```

##
#### diffBetweenAngles
`uint16_t diffBetweenAngles(const uint16_t& angle1, const uint16_t& angle2)`

Returns the difference between 2 angles in degrees. 
note: angles should be passed in between 0 and 360

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << HFL::diffBetweenAngles(0,90) << '\n';
	std::cout << HFL::diffBetweenAngles(-39,339) << '\n';
	std::cout << HFL::diffBetweenAngles(67,55) << '\n';
    return 0;
}
```
output:
```
90
2
12
```

##
#### gcd
`int64_t gcd(const int64_t& a, const int64_t& b)`

Returns the greatest common denominator of 2 numbers. 

##
#### decToFrac
`std::string decToFrac(const double& dec)`

Turns a decimal into a fraction. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << HFL::decToFrac(.002) << '\n';
	std::cout << HFL::decToFrac(355.2323) << '\n';
	std::cout << HFL::decToFrac(HFL::constants::pi) << '\n';
	std::cout << HFL::decToFrac(.19038492835) << '\n';
    return 0;
}
```
output:
```
0 1/500
355 2323/10000
3 141592653/1000000000
0 5949529/31250000
```

##
#### pyth
`double pyth(const char& side, const double& val1, const double& val2`

Solves for a missing triangle side using the pythagorean theorem. 
Input the side to solve for (`side`) and the 2 side values (`val1`,`val2`). 
If solving for A or B, use `val1` as side C. 

##
#### quadratic
`std::pair<double,double> quadratic(const double& a,const double& b,const double& c)`
###### !!! DOES NOT WORK !!!

Solves the quadratic formula and returns both the + and - answers (if an answer is impossible then 0 will be returned)

##
##### formatBits
`constexpr inline uint64_t formatBits(const uint64_t& val,const uint16_t& bits)`

Converts an unsigned int into a number with a variable amount of bits. 

###### Example:
```cpp
int main() {
	uint8_t val = 200;
	// turn 200 into the value it would be stores as in a 4 bit integer
	std::cout << HFL::formatBits(val,4) << '\n';
    return 0;
}
```
output:
```
8
```

##
#### BetterRand

A class that provides better random numbers than `random()` or `rand()`. 

##### *constructors:*

###### `BetterRand(const uint64_t& ExtraRand = 0)`
`ExtraRand` adds its value to the randomly generated number before it is returned in `genRand()`. 

##### *methods:*

##### genRand
`uint64_t genRand(const uint64_t &extra = 4, bool resetExtraRand = true, uint64_t resetERextraIt = 2)`

Returns a random number. 
The 3 parameters create more randomness, it's kind of unnecessary to pass values in honestly. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
	HFL::BetterRand rand;
	std::cout << rand.genRand() << '\n';
	std::cout << rand.genRand(444) << '\n';
	std::cout << rand.genRand(2894,4925,3425) << '\n';
    return 0;
}
```
output:
```
4199046835170
462494432314221199
14601681548741031733
```

#### constants

A namespace full of mathematical constants.

`constexpr double pi = 3.1415926535897932;`
`constexpr double e = 2.7182818284590451;`
`constexpr double phi = 1.6180339887498948;`
`constexpr double tau = 6.2831853071795862;`
`constexpr double sqrt2 = 1.4142135623730950;`
`constexpr double natLog2 = 0.6931471805599453;`
`constexpr double eulersConst = 0.5772156649015329;`
`constexpr double plankConst = 6.62607015e-34;`
`constexpr double avogardosConst = 6.02214076e+23;`
`constexpr double magicAngle = 0.9553166181245092;`
`constexpr double primeConst = 0.4146825098511116;`

#
### HF_misc.hpp

This file holds miscellaneous things that don't really fit elsewhere. 

##
#### readTypeId
`std::string readTypeid (const std::type_info& type, const bool& extraInfo = false)`

converts `std::type_info` to a more readable `std::string`
usage: `readTypeid(typeid(...).name())`
`bool extraInfo:` if true, returns extra information about the type when present
*NOTE: ONLY FOR GCC AS OF RIGHT NOW*
*Clang support will come later. As for MSVC, std::type_info already returns relatively readable type information.*

##
#### TermColors

A namespace that holds ANSI values for different terminal colors. 

Resets the color to the default terminal color. 
`std::string reset   = "\u001b[0m";`
Classic colors. 
`std::string black   = "\u001b[30m";`
`std::string red     = "\u001b[31m";`
`std::string green   = "\u001b[32m";`
`std::string yellow  = "\u001b[33m";`
`std::string blue    = "\u001b[34m";`
`std::string magenta = "\u001b[35m";`
`std::string cyan    = "\u001b[36m";`
`std::string white   = "\u001b[37m";`
Brighter versions of the normal colors, doesn't work in some terminals. 
`std::string BRI_black   = "\u001b[30m;1m";`
`std::string BRI_red     = "\u001b[31m;1m";`
`std::string BRI_green   = "\u001b[32m;1m";`
`std::string BRI_yellow  = "\u001b[33m;1m";`
`std::string BRI_blue    = "\u001b[34m;1m";`
`std::string BRI_magenta = "\u001b[35m;1m";`
`std::string BRI_cyan    = "\u001b[36m;1m";`
`std::string BRI_white   = "\u001b[37m;1m";`
Background color for text. 
`std::string BACK_black   = "\u001b[40m";`
`std::string BACK_red     = "\u001b[41m";`
`std::string BACK_green   = "\u001b[42m";`
`std::string BACK_yellow  = "\u001b[43m";`
`std::string BACK_blue    = "\u001b[44m";`
`std::string BACK_magenta = "\u001b[45m";`
`std::string BACK_cyan    = "\u001b[46m";`
`std::string BACK_white   = "\u001b[47m";`
Brighter versions of the background colors, doesn't work in some terminals. 
`std::string BRI_BACK_black   = "\u001b[40m;1m";`
`std::string BRI_BACK_red     = "\u001b[41m;1m";`
`std::string BRI_BACK_green   = "\u001b[42m;1m";`
`std::string BRI_BACK_yellow  = "\u001b[43m;1m";`
`std::string BRI_BACK_blue    = "\u001b[44m;1m";`
`std::string BRI_BACK_magenta = "\u001b[45m;1m";`
`std::string BRI_BACK_cyan    = "\u001b[46m;1m";`
`std::string BRI_BACK_white   = "\u001b[47m;1m";`
Bold text. 
`std::string BOLD   = "\u001b[1m";`
Underlined text. 
`std::string UNDERL = "\u001b[4m";`
Reversed text. 
`std::string REVRSD = "\u001b[7m";`

##
#### periodicTable
`static const std::vector<std::vector<std::string>> periodicTable`

A vector that holds data for every element on the periodic table. 

Data is formatted as such:
`{"1.0079"  , "Hydrogen"      , "H" , "1"  },`
`[0]`: Atomic mass
`[1]`: Element name
`[2]`: Element symbol
`[3]`: Atomic number

#
### HF_types.hpp

This file holds different data types that can be used. 

##
#### inf_t

A class that acts as infinity when mathematical operations are applied. 

##### *operator overloads:*
###### The following operators are all overloaded for `int64_t`, `inf_t`, and `double`