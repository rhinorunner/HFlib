#pragma once

// Helpful Functions library (HFlib)
// created by Zaine Rehman
// additional help by Bertie
// from 12-7-22 to 4-6-23

static constexpr char HFL_version[] = "1.1.2";

#ifdef __clang__
#define COMPILER clang
#elif __GNUC__
#define COMPILER gcc
#elif _MSC_VER
#define COMPILER msvc
// <UNS> not entirely sure if this is the correct macro for Apple C++ (xcode) 
#elif __APPLE__ 
#define COMPILER apple
#endif

// hflib includes
#include "HF_types.hpp"
#include "HF_math.hpp"
#include "HF_basics.hpp"
#include "HF_misc.hpp"

/************************************************************************
Version history:
1.0.0 
 	- first release of HFlib!
1.0.1
 	- docs are finished (probably not best to release the docs after the release...)
 	- polished some things
1.1.0
    - fixed/optimized a lot of the code
    - added the Audio class to HF_basics
1.1.2
	- added the sleep function to HF_basics
	- added the mciLookupError function to HF_basics
	- fixed a lot of issues with various functions
	- added better support for GCC
	- added methods to Audio
1.1.3
	- added sleep() and mciLookupError()
	- added <TAG> syntax to FORMATTING
	- added the COMPILER macro
************************************************************************/