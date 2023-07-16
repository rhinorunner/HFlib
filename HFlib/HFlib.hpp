#pragma once

// Helpful Functions library (HFlib)
// created by Zaine Rehman
// additional help by Bertie
// from 12-7-22 to 7-16-23

#define HFlib

#ifndef __cplusplus
// wtf are you doing...
#error "C++ is required for compile HFlib."
#endif

static constexpr char HFL_version[] = "2.0.0";

#ifdef __clang__
#define COMPILER clang
#elif __GNUC__
#define COMPILER gcc
#elif _MSC_VER
#define COMPILER msvc
// not entirely sure if this is the correct macro for Apple C++ (xcode) 
#elif __APPLE__ 
#define COMPILER apple
#endif

// not sure if this is the correct macro for C++23
#if   __cplusplus >= 202300L
	#define CPP_VERSION 23
#elif __cplusplus >= 202002L
	#define CPP_VERSION 20
#elif __cplusplus >= 201703L
	#define CPP_VERSION 17
#elif __cplusplus >= 201402L
	#define CPP_VERSION 14
#elif __cplusplus >= 201103L
	#define CPP_VERSION 11
#elif __cplusplus >= 199711L
	#define CPP_VERSION 98
#endif

// not sure if its a good idea to have such a short macro name
#ifdef _WIN64
	#define OS win64
#elif _WIN32
	#define OS win32
#elif __APPLE__
	#define OS apple
#elif __linux__
	#define OS linux
#elif __FreeBSD__
	#define OS freebsd
#elif __unix
	#define OS unix
#endif

#if CPP_VERSION < 20
#error "C++20 is required to compile HFlib. Try using the 'std=c++20' compile flag."
#endif

// hflib includes
#include "HF_types.hpp"
#include "HF_math.hpp"
#include "HF_basics.hpp"
#include "HF_misc.hpp"

/************************************************************************
Version history:

v1.0.0 
 	- first release of HFlib!
v1.0.1
 	- docs are finished (probably not best to release the docs after the release...)
 	- polished some things
v1.1.0
    - fixed/optimized a lot of the code
    - added the Audio class to HF_basics
v1.1.2
	- added the sleep function to HF_basics
	- added the mciLookupError function to HF_basics
	- fixed a lot of issues with various functions
	- added better support for GCC
	- added methods to Audio
v1.1.3
	- added sleep() and mciLookupError()
	- added <TAG> syntax to FORMATTING
	- added the COMPILER macro
	- small fixes
v1.1.4
	- added the CPP_VERSION macro
	- realized that mciSendString() is a meh way to play audio. Audio class only works for smaller files. 
	- added in docs to include HFlib.hpp always instead of individual files
	- added the OS macro
	- added multiple functions for getting user input
v1.1.5
	- added better support for non-windows systems
v1.1.7
	- added wordCount() and inRange() to HF_basics
	- added HF_joke :)
	- small tweaks
v1.1.8
	- added inline to most class operators
	- small tweaks
	- zooborkText now fully works
	- added the HFlib macro
v2.0.0
	- added Doxygen comment syntax to everything
	- fully reworked HF_math
	- changed the namespace name from HFL to hfl

	- added INT4_MAX, INT4_MIN, UINT4_MAX
	- added a matrix class
	- added MAX and MIN
	- added max(), min() and mean()
	- added subtractVec()
	- added 128 bit integer max and mins
	- added 128 bit integers (int128_t, uint128_t)
	- added getPrimes() and isPrime()
	- added rand64() and factorial()
	- added encrypt() and decrypt()
	- added Nibble2 struct
	- added EasyTypes namespace

	- removed Audio class because it was buggy
	- removed strToCVec and cVecToStr because theyre useless

	- removed the <TAG> comments things
	- renamed things with "WIN_" prefixes (removed the prefix)
	- made uintx_t work completely like any other integer type
	- fixed up the docs a little
************************************************************************/