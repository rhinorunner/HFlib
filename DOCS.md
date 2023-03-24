
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
Main file. It includes all of the other files, so if you `include` it there is no reason to include any of the other files. 

# 
### HF_basics.hpp
This file holds basic functions, such as a clear screen function or a function that gets the OS name. 

## 
##### clear
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
##### getOsName
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
##### WIN_setConsoleCursor
`void WIN_setConsoleCursor(const bool& showFlag)`
###### *Windows only*
###### !!! DOES NOT WORK !!!
Sets the cursor visibility. 

##
##### WIN_utf16Console
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
##### strToCVec
`std::vector<char> strToCVec(const std::string& str)`

Converts `std::string` to `std::vector<char>`

##
##### cVecToStr
`std::string CVecToStr(const std::vector<char>& cvec)`

Converts `std::vector<char>` to `std::string`

##
##### getIndexes
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
##### radToDeg
`constexpr double radToDeg(const double& rad)`

Converts a radian value to degrees. 

##
##### degToRad
`constexpr double degToRad(const double& deg)`

Converts a degree value to radians. 

##
##### normalizeAngle
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
##### diffBetweenAngles
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
##### gcd
`int64_t gcd(const int64_t& a, const int64_t& b)`

Returns the greatest common denominator of 2 numbers. 

##
##### decToFrac
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
##### pyth
`double pyth(const char& side, const double& val1, const double& val2`

Solves for a missing triangle side using the pythagorean theorem. 
Input the side to solve for (`side`) and the 2 side values (`val1`,`val2`). 
If solving for A or B, use `val1` as side C. 

##
##### quadratic
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