#pragma once

// HFlib data types

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// Helpful Functions libary
namespace HFL {

// use 16 bit infinity symbol (∞) by default?
static bool HFL_TYPES_inft_use16bInf = false;

// infinity class
class inf_t {
public:
    inf_t() {}

    bool operator= (const inf_t&   val) {return true; }
    bool operator= (const int64_t& val) {return false;}
    bool operator= (const double&  val) {return false;}
    
    void operator+= (const inf_t&   val) {}
    void operator+= (const int64_t& val) {}
    void operator+= (const double&  val) {}

    void operator-= (const inf_t&   val) {}
    void operator-= (const int64_t& val) {}
    void operator-= (const double&  val) {}

    void operator*= (const inf_t&   val) {}
    void operator*= (const int64_t& val) {}
    void operator*= (const double&  val) {}

    void operator/= (const inf_t&   val) {}
    void operator/= (const int64_t& val) {}
    void operator/= (const double&  val) {}

    bool operator== (const inf_t&   val) {return true; }
    bool operator== (const int64_t& val) {return false;}
    bool operator== (const double&  val) {return false;}

    bool operator!= (const inf_t&   val) {return false;}
    bool operator!= (const int64_t& val) {return true; }
    bool operator!= (const double&  val) {return true; }

    bool operator>  (const inf_t&   val) {return false;}
    bool operator>  (const int64_t& val) {return true; }
    bool operator>  (const double&  val) {return true; }

    bool operator<  (const inf_t&   val) {return false;}
    bool operator<  (const int64_t& val) {return false;}
    bool operator<  (const double&  val) {return false;}

    bool operator>= (const inf_t&   val) {return true;}
    bool operator>= (const int64_t& val) {return true;}
    bool operator>= (const double&  val) {return true;}

    bool operator<= (const inf_t&   val) {return true; }
    bool operator<= (const int64_t& val) {return false;}
    bool operator<= (const double&  val) {return false;}

    inf_t operator+ (const inf_t&   val) {return inf_t();}
    inf_t operator+ (const int64_t& val) {return inf_t();}
    inf_t operator+ (const double&  val) {return inf_t();}

    inf_t operator- (const inf_t&   val) {return inf_t();}
    inf_t operator- (const int64_t& val) {return inf_t();}
    inf_t operator- (const double&  val) {return inf_t();}

    inf_t operator* (const inf_t&   val) {return inf_t();}
    inf_t operator* (const int64_t& val) {return inf_t();}
    inf_t operator* (const double&  val) {return inf_t();}

    inf_t operator/ (const inf_t&   val) {return inf_t();}
    inf_t operator/ (const int64_t& val) {return inf_t();}
    inf_t operator/ (const double&  val) {return inf_t();}

    friend std::ostream& operator<< (
        std::ostream& os, 
        const inf_t& val
    ) {
        os << (HFL_TYPES_inft_use16bInf ? "∞" : "inf");
        return os;
    }

    // casting turns the cast into max value
    template <typename T>
    explicit operator T() const {
        return std::numeric_limits<T>::max();
    }
};

// any amount of bits inteter
// note: stores with size of uint64_t
template <uint8_t bits_g>
class uintx_t {
private:
	uint64_t Val;
    uint8_t bits;

    // POV im lazy
    constexpr inline uint64_t _formatBits(
	    const uint64_t& val,
	    const uint16_t& _bits
    ) {return val & UINT64_MAX >> (64-_bits);}

public:
	uintx_t(const int64_t& val) {
        bits = bits_g;
		if      (bits > 64) bits = 64;
		else if (bits < 1 ) bits = 1;
		Val = _formatBits(val, bits);
	}
    
    void operator= (uintx_t& val) {
        Val = _formatBits(val.Val, bits);
    }
	void operator= (const int64_t& val) {
		Val = _formatBits(val, bits);
	}

	bool operator== (const int64_t& val) {
		return (Val == val);
	}
    bool operator!= (const int64_t& val) {
        return (Val != val);
    }
    bool operator> (const int64_t& val) {
        return (Val > val);
    }
    bool operator< (const int64_t& val) {
        return (Val < val);
    }
    bool operator>= (const int64_t& val) {
        return (Val >= val);
    }
    bool operator<= (const int64_t& val) {
        return (Val <= val);
    }

	int64_t operator+ (const int64_t& val) {
		return (_formatBits(Val + val, bits));
	}
	int64_t operator- (const int64_t& val) {
		return (_formatBits(Val - val, bits));
	}
	int64_t operator* (const int64_t& val) {
		return (_formatBits(Val * val, bits));
	}
	int64_t operator/ (const int64_t& val) {
		return (_formatBits(Val / val, bits));
	}
	int64_t operator% (const int64_t& val) {
		return (_formatBits(Val % val, bits));
	}
	int64_t operator| (const int64_t& val) {
		return (_formatBits(Val | val, bits));
	}
	int64_t operator& (const int64_t& val) {
		return (_formatBits(Val & val, bits));
	}
	int64_t operator^ (const int64_t& val) {
		return (_formatBits(Val ^ val, bits));
	}
	int64_t operator<< (const int64_t& val) {
		return (_formatBits(Val << val, bits));
	}
	int64_t operator>> (const int64_t& val) {
		return (_formatBits(Val >> val, bits));
	}

	uintx_t& operator++ () {
		Val = _formatBits(++Val, bits);
		return *this;
	}
	uintx_t& operator-- () {
		Val = _formatBits(--Val, bits);
		return *this;
	}
	uintx_t operator++ (int) {
		Val = _formatBits(++Val, bits);
		return *this;
	}
	uintx_t operator-- (int) {
		Val = _formatBits(--Val, bits);
		return *this;
	}

	void operator+= (const int64_t& val) {
		Val = _formatBits(Val+val, bits);
	}
	void operator-= (const int64_t& val) {
		Val = _formatBits(Val-val, bits);
	}
	void operator*= (const int64_t& val) {
		Val = _formatBits(Val*val, bits);
	}
	void operator/= (const int64_t& val) {
		Val = _formatBits(Val/val, bits);
	}
	void operator%= (const int64_t& val) {
		Val = _formatBits(Val%val, bits);
	}
	void operator|= (const int64_t& val) {
		Val = _formatBits(Val|val, bits);
	}
	void operator&= (const int64_t& val) {
		Val = _formatBits(Val&val, bits);
	}
	void operator^= (const int64_t& val) {
		Val = _formatBits(Val^val, bits);
	}
	void operator<<= (const int64_t& val) {
		Val = _formatBits(Val<<val, bits);
	}
	void operator>>= (const int64_t& val) {
		Val = _formatBits(Val>>val, bits);
	}

	friend std::ostream& operator<< (
		std::ostream& os,
		uintx_t& UX
	) {
		os << std::to_string(UX.Val);
		return os;
	}

	template <typename T>
	explicit operator T() const {
		return (T)Val;
	}
};

static bool HFL_TYPES_VecWrapper_logByDefault = true;

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
		std::string strToPush = 
			"[call "
			+ std::to_string(callNum) 
			+ "] ["
			+ function
			+ "] : "
			+ message;
		vecLog.push_back(strToPush);
		callNum++;
	}

public:
	bool logBool = HFL_TYPES_VecWrapper_logByDefault;
	std::string printSep = ", ";
	
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
		// ah yes i love useless code
		log("destructor", "destructed wrapper");
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

	// returns the vector but with removed duplicates
	std::vector<T> rmDuplicates() {
		std::vector<T> toReturn {};
		bool kill;
		for (auto& i : internalVec) {
			kill = false;
			for (auto& x : toReturn) 
				if (x == i) kill = true;
			if (!kill) toReturn.push_back(i);
		}
		log ("rmDuplicates","returned a duplicate-free vector");
		return toReturn;
	}

	// sorts, if possible
	bool sort(bool reverse = false) {
		try {auto test = (short)internalVec[0];}
		catch (...) {
			if (!internalVec.size()) 
				log("sort","!failed to sort vector (size = 0)!");
			else 
				log("sort","!failed to sort vector (type cannot cast to int)!");
			return false;
		}
		if (!internalVec.size()) {
			log("sort","!failed to sort vector (size = 0)!");
			return false;
		}
		if (reverse) 
			std::sort(internalVec.begin(),internalVec.end(), std::greater<int>());
		else 
			std::sort(internalVec.begin(),internalVec.end());
		// im lazy
		if (reverse) log("sort","sorted internalVec, reversed");
		else log("sort","sorted internalVec");
		return true;
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
	std::string logToStr(std::string tSep = "\n") {
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

	// append VecWrapper vector to vector
	void addVecW(const VecWrapper& vec) {
		internalVec.insert(
			internalVec.end(), 
			vec.internalVec.begin(), 
			vec.internalVec.end()
		);
		log("addVecW", "added VecWrapper vector values");
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
		log("r_begin", "returned reverse begin iterator");
		return internalVec.rbegin();
	}
	// reverse iterator end
	typename std::vector<T>::reverse_iterator r_end() {
		log("r_end", "returned reverse end iterator");
		return internalVec.rend();
	}

	// compare vector to another vector of the same type
	T operator== (const std::vector<T>& comparison) {
		log("operator==", "compared vector");
		return (internalVec == comparison);
	}
	// compare vector to another VecWrapper
	T operator== (const VecWrapper& comparison) {
		log("operator==", "compared VecWrapper");
		return (internalVec == comparison.internalVec);
	}

	// get value
	T operator[] (const uint64_t& index) {
		if (index >= internalVec.size()) {
			log("operator[]", "!accessed index " + std::to_string(index) + " (out of bounds)!");
			// fuck, what the hell is the user doing
			return 1;
		}
		log("operator[]", "accessed index " + std::to_string(index));
		return internalVec[index];
	}

	// return indexes where the value is present
	std::vector<uint64_t> operator() (const T& value) {
		std::vector<uint64_t> indexes {};
		for (uint64_t i = 0; i < internalVec.size(); i++) 
			if (internalVec[i] == value) 
				indexes.push_back(i);
		log("operator()", "returned indexe(s) of a value");
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
	// assign internal vector to nothing
	void operator= (void* _) {
		internalVec = {};
		log("operator=", "assigned new vector to {}");
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

};