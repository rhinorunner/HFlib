
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
##### `inline void clear(uint8_t type = 3, uint16_t newLineCharNum = 72)`
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
##### `inline std::string getOsName()`
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
output (on Windows machine):
```
Windows
```
