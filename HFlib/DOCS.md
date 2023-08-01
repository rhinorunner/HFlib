
# Helpful Functions Libary

###### created by Zaine Rehman
###### contributors: Bertie
##
###### *First release was v1.0.0, published 3-23-23*
###### *Latest release is v2.0.1, published 8-1-23*
# 
### What is Helpful Functions Library?
Helpful Functions Library (HFlib) is a collection of C++ implementation files that provide helpful functions, classes, and variables for various different purposes.

# 
### Usage
There are currently 5 different files:
- [`HF_basics.hpp`](#hf_basicshpp)
- [`HF_math.hpp`](#hf_mathhpp)
- [`HF_misc.hpp`](#hf_mischpp)
- [`HF_types.hpp`](#hf_typeshpp)
- [`HFlib.hpp`](#hflibhpp)

Each file holds different functions according to what they would be used for (for example, `HF_math` has math related things and `HF_types` has variable types.) 
`HFlib.hpp` includes all other HFlib files. 

To use, simply place the `HFlib` folder inside your project directory and include `HFlib.hpp`  from it. **Everything will be inside of the `hfl` namespace.**

*DO NOT INCLUDE INDIVIDUAL FILES. Include `HFlib.hpp`.*

#### Top features
- [`uintx_t`](#uintx_t)
- [`decToFrac`](#dectofrac)
- [`BetterRand`](#betterrand)
- [`Audio`](#audio)
- [`Matrix`](#matrix)

*Note: c++20 is required to use this library.*

# 
### HFlib.hpp
The main file. This is what you should include. 

##
#### HFL_version
`static constexpr char* HFL_version`

Holds the current version of hfl that is being used. 

##
#### HFL_version

Macro that holds the name of the compiler. Works for GCC, Clang, MSVC, and Apple C++. 

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
    hfl::clear();
    std::cout << "You will only see me\n";
    return 0;
}
```
output: 
```
You will only see me
```

##
#### sleep
`inline void sleep(uint64_t ms)`

Takes in an amount of milliseconds (`ms`) and sleeps for that long. 

## 
#### getOsName
`inline std::string getOsName()`

Returns a string that holds the name of the OS being used. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
    std::cout << hfl::getOsName() << '\n';
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
    hfl::WIN_utf16Console();
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
*please note that `Active code page: 65001` will be printed when the function is used, so using [`hfl::clear()`](#clear) afterward is recommended.*

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
    auto indexes = hfl::getIndexes<char>(vec,'a');

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

##
#### getKey
`inline uint8_t getKey()`

Gets keypress input. 

##
#### getInput
`std::string getInput(const std::string& prompt = "")`

Gets input and returns that input as a string. 

`prompt`: what is said before getting input. 

##
#### chooseItem
`template <typename T> T chooseItem (const std::vector<T>& items, const std::string& prompt = "", const std::vector<T>& illegalItems = {}, const std::string& illegalMessage = "illegal item")`

Gets the user to select an item from a list. 

`T`: type of the elements in the list

`items`: list of elements for the user to select

`prompt`: what is said before getting user input

`illegalItems`: items that it will not allow the user to select

`illegalMessage`: message stated if the user chooses an illegal item

##
#### inRange
`constexpr inline bool inRange(uint64_t val, uint64_t min, uint64_t max)`

Returns `true` if `val` is in between `min` and `max`.

##
#### wordCount
`uint64_t wordCount(const std::string& str, const std::vector<char>& delimiters = {' ',',','.','!','?','\'','\"','\n','\t'})`

Returns the amount of words in a string. 

##
#### max
`template <typename T> inline T max(const T* arr)`
`template <typename T> inline T max(const T* arr, uint64_t size)`

Returns the greatest value in a container.

##
#### min
`template <typename T> inline T min(const T* arr)`
`template <typename T> inline T min(const T* arr, uint64_t size)`

Returns the smallest value in a container.

##
#### mean
`template <typename T> inline T mean(const T* arr)`
`template <typename T> inline T mean(const T* arr, uint64_t size)`

Returns the mean of a container.

##
#### subtractVec
`template <typename T> std::vector<T> subtractVec(std::vector<T> vec1,const std::vector<T>& vec2)`

Subtracts `vec2` from `vec1`.

##
#### timeToRun
`template <typename T> double timeToRun(T (*toRun)())`

Returns the time taken to run `toRun` function.

##
#### INT4_MAX

4 bit integer maximum. 

##
#### INT4_MIN

4 bit integer minimum. 

##
#### UINT4_MAX

Unsigned 4 bit integer maximum. 

#
### HF_math.hpp
This file holds functions and classes related to math

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
#### rand64
`inline uint64_t rand64(uint64_t seed = rand())`

Returns a random 64 bit integer.

##
#### factorial
`constexpr inline double factorial(uint64_t num)`

Rudimentary factorial function.

##
#### getPrimes
`std::vector<uint64_t> getPrimes(uint64_t ceiling)`

Returns all of the prime numbers up to a ceiling value.

##
#### isPrime
`constexpr bool isPrime(uint64_t n)`

Returns `true` if `n` is a prime number.

##
#### Real
`Real`

A virtual class used that generalizes over mathematical object that can be converted a real number.

#### *constructors:*

No constructors exist for Real, though all other applicable classes will be able to be used as such.

#### *methods:*

##### method name
`eval`

virtual

Returns a double based on the internal state of the class. Virtual with no default implementation. 

is impossible then 0 will be returned

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
#### Rand
`class Rand`

A class that provides better random numbers than `random()` or `rand()`. 

##### *constructors:*

###### `Rand(int64_t)`
Constructs a random number generator using the provided seed.

###### `Rand(void)`
Constructs a random number generator using the system time.

##### *methods:*

##### private genRand
`int64_t genRand()`

Returns a random number. 

##### getSample
`double getSample()`

Returns a random number processed via a gaussian. 

##### getSampleCustom(int64_t, int64_t)
`double getSampleCustom(int64_t sigma, int64_t mu)`

Returns a random number through a gaussian with given standard deviation and mean. 

##### getInt
`int64_t getInt()`

Returns a random integer. 

##### genFloat
`double genRand()`

Returns a random floating point number. 


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

Brighter versions of the normal colors, doesn't work in some 
terminals. 

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

Brighter versions of the background colors, doesn't work in some 
terminals. 

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

##
#### mciLookupError
`std::string mciErrorLookup(int error)`

`error` is the value that `mciSendString()` (or any other function that returns an MCI error) will return. `mciLookupError()` returns a string that holds the name of that error. 

##
#### encrypt
`std::string encrypt(const std::string& data, uint32_t key, uint32_t key2 = 0)`

Encrypts a string. 

##
#### decrypt
`std::string decrypt(const std::string& data, uint32_t key, uint32_t key2 = 0)`

Decrypts a string. 

#
### HF_types.hpp

This file holds different data types that can be used. 

##
#### inf_t
`class inf_t`

A class that acts as infinity when mathematical operations are applied. 

#### *operators:*

Any operator that is useable on an integer type can be used on this class (including std::ostream overload). 

Assignment operators do not work. 

This class can also be casted into any integer type. 

##
#### HFL_TYPES_inft_use16bInf

`static bool HFL_TYPES_inft_use16bInf = false;`

If true, `inf_t` will print an infinity ascii symbol to the terminal when using the `std::ostream` operator. If false, it outputs `inf` instead. False by default.

##
#### Nibble2

`struct Nibble2`

Stores 2 nibbles in 1 byte

#### *constructors*

##### `Nibble2(uint8_t val1, uint8_t val2)`

#### *methods*

##### val1
`val1()`

Returns the 1st value.

##### val2
`val2()`

Returns the 2nd value.

##
#### uintx_t

`template <uint8_t bits_g> class uintx_t`

A class that acts as an unsigned integer with a variable amount of bits. You can treat it exactly like any other integer type. 

`<uint8_t bits_g>`: the amount of bits that the value will change according to. 

All values will be stored with 64 bits. Lowering the bits value will not make it take up less memory. 

#### *constructors:*

###### `uintx_t(const int64_t& val)`

`val`: the numerical value that will be stored. 

#### *operators:*

Any operator that is useable on an integer type can be used on this class (including std::ostream overload). 

##### Example:
```cpp
#include <iostream>
#include "HFlib.HFlib.hpp"

int main() {
	uintx_t<2> val = 3;
	std::cout << val << '\n';
	val++;
	std::cout << val << '\n';
	return 0;
}
```
output:
```cpp
3
0
```

##
#### VecWrapper
`template <typename T> class VecWrapper`

Wrapper class for `std::vector`. Provides all the functionality as a normal vector but with added things (this means you can use it exactly as a normal `std::vector`.) 

All interactions with the `VecWrapper` will be stored within a log (can be disabled). To access the log, use the `getLog()` method. 

Note: `rbegin()` and `rend()` from `std::vector` have been converted into `r_begin()` and `r_end()` respectively. 

#### *constructors:*

###### `VecWrapper()`

Creates the object with no values. 

##### `template <typename... Args> explicit VecWrapper(Args... args)`

`... args`: arguments that are stored inside the vector.

#### *variables:*

#### logBool
`bool logBool = HFL_TYPES_VecWrapper_logByDefault;`

If true, logs all interactions with the `VecWrapper`. 

Note: `HFL_TYPES_VecWrapper_logByDefault` is true by default. 

#### printSep
`std::string printSep = ", ";`

When the vector is turned into a string (`friend operator<<`, `vToStr()`), it will use `printSep` as a separator between values. 

#### *methods:*

All (or at least, almost all) `std::vector` methods can be used with `VecWrapper`. 

##### rmDuplicates
`std::vector<T> rmDuplicates()`

Returns a vector that is similar to the actual stored vector, except all duplicates are removed. 

##### sort
`bool sort(bool reverse = false)`

Sorts the vector. Returns `false` if the vector failed to sort. 

`bool reverse`: if true, sorts elements in a reversed order. 

##### getVec
`std::vector<T> getVec()`

Returns the internally stored `std::vector`. Not many use cases due to all of the operator overloads. 

##### getLog
`std::vector<std::string> getLog()`

Returns the log. 

##### logToStr
`std::string logToStr(std::string tSep = "\n")`

Returns the log as a string. 

`std::string tSep`: separator between each item in the log. 

##### vToStr
`std::string vToStr()`

Returns all the values of the vector as a string with `printSep` separating every item. 

##### addVecW
`void addVecW(const VecWrapper& vec)`

Inserts the values of a passed in `VecWrapper` to the end of the internal vector. 

#### *operators:*

All `std::vector` operator overloads have been passed over and can also be used with other `VecWrapper` objects.

##### operator()
`std::vector<uint64_t> operator() (const T& value)`

Returns the indexes that a passed in value occurs in. 

##### operator--
`void operator-- ()`

Removes the last item in the vector. 

`void operator-- (int)`

Removes the last item in the vector. 

##### operator+=
`void operator+= (const T& value)`

Adds a value to the back of the vector. 

`void operator+= (const std::vector<T>& vec)`

Adds the values of another `std::vector` (with the same type) to the back of the vector. 

##### friend operator<<
`friend std::ostream& operator<<`

Can be used with `std::cout` (or any other `std::ostream` `<<` operator use), and returns all the values inside the vector with `printSep` as the separator. 

###### Example:
```cpp
#include <iostream>
#include "HFlib/HFlib.hpp"

int main() {
	hfl::VecWrapper<int> vec {4,-234,0,0,3,4,5,6};

	std::cout << vec << '\n';

	for (int& i : vec.rmDuplicates()) {
		std::cout << i << ' ';
	}
	std::cout << '\n';

	std::cout << vec.logToStr() <<'\n';

	vec--;
	vec += 40;
	vec.sort();

	std::cout << vec.logToStr();

    return 0;
}
```
output:
```
4, -234, 0, 0, 3, 4, 5, 6
4 -234 0 3 5 6
{[call 0] [constructor] : constructed wrapper with packed args}
{[call 1] [vToStr] : returned vector as string}
{[call 2] [friend operator<<] : printed vector}
{[call 3] [rmDuplicates] : returned a duplicate-free vector}

{[call 0] [constructor] : constructed wrapper with packed args}
{[call 1] [vToStr] : returned vector as string}
{[call 2] [friend operator<<] : printed vector}
{[call 3] [rmDuplicates] : returned a duplicate-free vector}
{[call 4] [logToStr] : returned log as string}
{[call 5] [operator--] : popped back}
{[call 6] [operator+=] : added value}
{[call 7] [sort] : sorted internalVec}
```

##
#### HFL_TYPES_VecWrapper_logByDefault
`static bool HFL_TYPES_VecWrapper_logByDefault = true;`

If true, `VecWrapper` will log all interactions by default. True by default. 

##
#### Matrix
`template <uint16_t Rows, uint16_t Columns> class Matrix `

A matrix class for storing and performing operations on matrices. 

#### *constructors:*

##### `Matrix(const std::initializer_list<std::initializer_list<float>>& array)`

Sets up the matrix with the argument values. The list must be of the proper dimensions. 

##### `Matrix()`

Sets up the matrix with 0 as all values. 

#### *methods:*

##### transpose()
`Matrix transpose()`

Returns the matrix, but transposed. 

##### determinant()
`double determinant()`

Returns the determinant of the matrix. 

#### *operators:*

##### operator+
`Matrix operator+ (const Matrix& other)`

Returns the matrix with the values of the other matrix added. 

##### operator-
`Matrix operator- (const Matrix& other)`

Returns the matrix with the values of the other matrix subtracted.

##### operator+=
`Matrix operator+= (const Matrix& other)`

Adds the values of another matrix to the matrix. 

##### operator-=
`Matrix operator-= (const Matrix& other)`

Subtracts the values of another matrix to the matrix. 

##### operator*
`template <uint16_t otherRows, uint16_t otherColumns> Matrix<Rows,otherColumns> operator* (const Matrix<otherRows,otherColumns>& other)`

Returns the dot product of the matrix and the argument matrix. 

`template <typename T> Matrix<Rows,1> operator* (const std::vector<T>& vec)`

Returns the dot product of the matrix and the argument vector. 

`Matrix operator* (double scalar)`

Returns the matrix multiplied by a scalar value. 

##### operator*=
`template <uint16_t otherRows, uint16_t otherColumns> Matrix<Rows,otherColumns> operator*= (const Matrix<otherRows,otherColumns>& other)`

Sets the matrix value as the dot product of the matrix and the argument matrix. 

`template <typename T> Matrix<Rows,1> operator*= (const std::vector<T>& vec)`

Sets the matrix value as the dot product of the matrix and the vector. 

`Matrix operator*= (double scalar)`

Sets the matrix value as the matrix multiplied by a scalar value. 

##### friend operator<<
`friend std::ostream& operator<<`

Returns a string with the values of the matrix in a print-friendly way. 

###### Example:



##
#### EasyTypes

A namespace with shorter names for types. 

`typedef unsigned char byte;`

`typedef unsigned char u8;`

`typedef unsigned short u16;`

`typedef unsigned int u32;`

`typedef unsigned long long u64;`

`typedef char i8;`

`typedef short i16;`

`typedef int i32;`

`typedef long long i64;`

`typedef float f32;`

`typedef double f64;`

`typedef std::string string;`

`typedef const char* cstring;`

#
### Thank you for using HFlib