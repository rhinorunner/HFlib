#pragma once

// HFlib data types

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <limits>
#include <bitset>

// Helpful Functions libary
namespace hfl {

typedef          __int128  int128_t;
typedef unsigned __int128 uint128_t;

/**
 * @brief use 16 bit infinity symbol (∞) by default?
*/
static bool HFL_TYPES_inft_use16bInf = false;

/**
 * @brief Infinity type. 
*/
class inf_t {
public:
	inf_t() {}

	inline bool operator= (const inf_t& val) {return true;}
	inline bool operator= (double val) {return false;}

	inline bool operator== (const inf_t& val) {return true;}
	inline bool operator== (double val) {return false;}

	inline bool operator!= (const inf_t& val) {return false;}
	inline bool operator!= (double val) {return true;}

	inline bool operator> (const inf_t& val) {return false;}
	inline bool operator> (double val) {return true;}

	inline bool operator< (const inf_t& val) {return false;}
	inline bool operator< (double val) {return false;}

	inline bool operator>= (const inf_t& val) {return true;}
	inline bool operator>= (double val) {return true;}

	inline bool operator<= (const inf_t& val) {return true;}
	inline bool operator<= (double val) {return false;}

	inline inf_t operator+ (const inf_t& val) {return inf_t();}
	inline inf_t operator+ (double val) {return inf_t();}

	inline inf_t operator- (const inf_t& val) {return inf_t();}
	inline inf_t operator- (double val) {return inf_t();}

	inline inf_t operator* (const inf_t&   val) {return inf_t();}
	inline inf_t operator* (double val) {return inf_t();}

	inline inf_t operator/ (const inf_t& val) {return inf_t();}
	inline inf_t operator/ (double  val) {return inf_t();}

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

/**
 * @brief Any amount of Bits integer.
 * @tparam Bits amount of Bits
 * 
 * @note stores with size of uint64_t
*/
template <uint8_t Bits>
requires((Bits >= 1) && (Bits <= 64))
class uintx_t {
protected:
	uint64_t Value;

	constexpr static inline uint64_t formatBits(
		uint64_t val,
		uint16_t Bits2
	) {return val & (UINT64_MAX >> (64-Bits2));}

public:
	uintx_t(int64_t val) {
		Value = formatBits(val, Bits);
	}
	template <uint8_t otherBits>
	uintx_t(const uintx_t<otherBits>& val) {
		Value = formatBits(val.getVal(), Bits);
	}

	constexpr inline uint64_t getVal() const {return Value;}

	std::string toBin() const {
		std::string bin = std::bitset<Bits>(Value).to_string();
		return bin;
	}

	uint8_t bits() const {
		return Bits;
	}
	
	inline void operator= (int64_t val) {
		Value = formatBits(val, Bits);
	}
	template <uint8_t otherBits>
	inline void operator= (uintx_t<otherBits> val) {
		Value = formatBits(val.getVal(), Bits);
	}
	inline bool operator== (int64_t val) {
		return (Value == val);
	}
	template <uint8_t otherBits>
	inline bool operator==(const uintx_t<otherBits>& val) {
		return (Value == val.getVal());
	}
	inline bool operator!= (int64_t val) {
		return (Value != val);
	}
	template <uint8_t otherBits>
	inline bool operator!=(const uintx_t<otherBits>& val) {
		return (Value != val.getVal());
	}
	inline bool operator> (int64_t val) {
		return (Value > val);
	}
	template <uint8_t otherBits>
	inline bool operator> (const uintx_t<otherBits>& val) {
		return (Value > val.getVal());
	}
	inline bool operator< (int64_t val) {
		return (Value < val);
	}
	template <uint8_t otherBits>
	inline bool operator< (const uintx_t<otherBits>& val) {
		return (Value < val.getVal());
	}
	inline bool operator>= (int64_t val) {
		return (Value >= val);
	}
	template <uint8_t otherBits>
	inline bool operator>= (const uintx_t<otherBits>& val) {
		return (Value >= val.getVal());
	}
	inline bool operator<= (int64_t val) {
		return (Value <= val);
	}
	template <uint8_t otherBits>
	inline bool operator<= (const uintx_t<otherBits>& val) {
		return (Value <= val.getVal());
	}

	inline uintx_t operator+ (int64_t val) {
		return uintx_t(formatBits(Value + val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator+ (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value + val.getVal(), Bits));
	}
	inline uintx_t operator- (int64_t val) {
		return uintx_t(formatBits(Value - val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator- (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value - val.getVal(), Bits));
	}
	inline uintx_t operator* (int64_t val) {
		return uintx_t(formatBits(Value * val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator* (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value * val.getVal(), Bits));
	}
	inline uintx_t operator/ (int64_t val) {
		return uintx_t(formatBits(Value / val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator/ (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value / val.getVal(), Bits));
	}
	inline uintx_t operator% (int64_t val) {
		return uintx_t(formatBits(Value % val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator% (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value % val.getVal(), Bits));
	}
	inline uintx_t operator| (int64_t val) {
		return uintx_t(formatBits(Value | val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator| (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value | val.getVal(), Bits));
	}
	inline uintx_t operator& (int64_t val) {
		return uintx_t(formatBits(Value & val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator& (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value & val.getVal(), Bits));
	}
	inline uintx_t operator^ (int64_t val) {
		return uintx_t(formatBits(Value ^ val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator^ (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value ^ val.getVal(), Bits));
	}
	inline uintx_t operator<< (int64_t val) {
		return uintx_t(formatBits(Value << val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator<< (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value << val.getVal(), Bits));
	}
	inline uintx_t operator>> (int64_t val) {
		return uintx_t(formatBits(Value >> val, Bits));
	}
	template <uint8_t otherBits>
	inline uintx_t operator>> (const uintx_t<otherBits>& val) {
		return uintx_t(formatBits(Value >> val.getVal(), Bits));
	}

	inline uintx_t& operator++ () {
		Value = formatBits(++Value, Bits);
		return *this;
	}
	inline uintx_t& operator-- () {
		Value = formatBits(--Value, Bits);
		return *this;
	}
	inline uintx_t operator++ (int) {
		Value = formatBits(++Value, Bits);
		return *this;
	}
	inline uintx_t operator-- (int) {
		Value = formatBits(--Value, Bits);
		return *this;
	}

	inline uintx_t operator+= (int64_t val) {
		Value = formatBits(Value+val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator+= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value+val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator-= (int64_t val) {
		Value = formatBits(Value-val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator-= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value-val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator*= (int64_t val) {
		Value = formatBits(Value*val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator*= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value*val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator/= (int64_t val) {
		Value = formatBits(Value/val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator/= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value/val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator%= (int64_t val) {
		Value = formatBits(Value%val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator%= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value%val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator|= (int64_t val) {
		Value = formatBits(Value|val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator|= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value|val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator&= (int64_t val) {
		Value = formatBits(Value&val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator&= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value&val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator^= (int64_t val) {
		Value = formatBits(Value^val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator^= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value^val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator<<= (int64_t val) {
		Value = formatBits(Value<<val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator<<= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value<<val.getVal(), Bits);
		return *this;
	}
	inline uintx_t operator>>= (int64_t val) {
		Value = formatBits(Value>>val, Bits);
		return *this;
	}
	template <uint8_t otherBits>
	inline uintx_t operator>>= (const uintx_t<otherBits>& val) {
		Value = formatBits(Value>>val.getVal(), Bits);
		return *this;
	}

	friend std::ostream& operator<< (
		std::ostream& os,
		const uintx_t& UX
	) {
		os << std::to_string(UX.getVal());
		return os;
	}

	template <typename T>
	explicit operator T() const {
		return (T)Value;
	}
};

template <uint8_t bits>
static constexpr uint64_t operator+ (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs + rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator- (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs - rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator* (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs * rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator/ (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs / rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator% (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs % rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator| (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs | rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator& (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs & rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator^ (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs ^ rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator<< (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs << rhs.getVal();
}
template <uint8_t bits>
static constexpr uint64_t operator>> (uint64_t lhs, uintx_t<bits> rhs) {
	return lhs >> rhs.getVal();
}

/**
 * @brief Stores 2 nibbles in 1 byte. 
*/
struct Nibble2 {
public:
	Nibble2(uint8_t val1, uint8_t val2) {
		Bits = (val1 << 4) | val2;
	}

	inline uint8_t val1() const {
		return Bits & 0b11110000;
	}
	inline uint8_t val2() const {
		return Bits & 0b00001111;
	}

private:
	uint8_t Bits;
};

static bool HFL_TYPES_VecWrapper_logByDefault = true;

/**
 * @brief Wrapper for std::vector. 
*/
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
	
	/**
	 * @brief Returns the amount of elements in the vector.
	*/
	uint64_t size() {
		log("size", "returned size");
		return internalVec.size();
	}

	/**
	 * @brief Pushes a value to the back of the vector.
	*/
	bool push_back(const T& value) {
		internalVec.push_back(value);
		log("push_back", "pushed back value");
		return true;
	}
	/**
	 * @brief Pops a value from the back of the vector.
	*/
	bool pop_back() {
		if (internalVec.empty()) {
			log("pop_back", "!attempted to pop empty vec!");
			return false;
		}
		internalVec.pop_back();
		log("pop_back", "popped back value");
		return true;
	}
	/**
	 * @brief Pushes a value to the front of the vector.
	*/
	bool push_front(const T& value) {
		internalVec.insert(internalVec.begin(), value);
		log("push_front", "pushed front value");
		return true;
	}
	/**
	 * @brief Pops a value from the front of the vector.
	*/
	bool pop_front() {
		if (internalVec.empty()) [[unlikely]] {
			log("pop_front", "!attempted to pop empty vec!");
			return false;
		}
		internalVec.erase(internalVec.begin());
		log("pop_front", "popped front value");
		return true;
	}

	/**
	 * @brief Removes a value at a specific index. 
	*/
	bool del(uint64_t index) {
		if (index >= internalVec.size()) [[unlikely]] {
			log("del", "!attempted to delete value at index " + std::to_string(index) + " (out of bounds)!");
			return false;
		}
		internalVec.erase(internalVec.begin() + index);
		log("del", "deleted value at index " + std::to_string(index));
		return true;
	}

	/**
	 * @brief Resizes the vector to a specific size.
	*/
	bool resize(uint64_t newSize) {
		internalVec.resize(newSize);
		log("resize", "resized vector to size " + std::to_string(newSize));
		return true;
	}

	/**
	 * @brief Reverses the vector. 
	*/
	bool reverse() {
		std::reverse(internalVec.begin(), internalVec.end());
		log("reverse", "reversed vector");
		return true;
	}

	/**
	 * @brief Returns the vector but with removed duplicates.
	*/
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

	/**
	 * @brief Sorts the vector, if possible.
	*/
	bool sort(bool reverse = false) {
		try {[[maybe_unused]] auto _ = (short)internalVec[0];}
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
		if (reverse) [[unlikely]]
			std::sort(internalVec.begin(),internalVec.end(), std::greater<int>());
		else [[likely]]
			std::sort(internalVec.begin(),internalVec.end());
		// im lazy
		if (reverse) log("sort","sorted internalVec, reversed");
		else log("sort","sorted internalVec");
		return true;
	}

	/**
	 * @brief Returns the vector.
	*/
	std::vector<T> getVec() {
		log("getVec", "returned internal vector value");
		return &internalVec;
	}

	/**
	 * @brief Returns the vector as a string.
	*/
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

	/**
	 * @brief Returns the log.
	*/
	std::vector<std::string> getLog() {
		log("getLog", "returned log");
		return vecLog;
	}
	/**
	 *  @brief Returns the log as a string.
	*/
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

	/**
	 * @brief Appends a VecWrapper vector to the vector.
	*/
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
	inline T operator== (const std::vector<T>& comparison) {
		log("operator==", "compared vector");
		return (internalVec == comparison);
	}
	// compare vector to another VecWrapper
	inline T operator== (const VecWrapper& comparison) {
		log("operator==", "compared VecWrapper");
		return (internalVec == comparison.internalVec);
	}

	// get value
	T operator[] (uint64_t index) {
		if (index >= internalVec.size()) [[unlikely]] {
			log("operator[]", "!accessed index " + std::to_string(index) + " (out of bounds)!");
			// fuck, what the hell is the user doing
			return -1;
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
	inline void operator-- () {
		internalVec.pop_back();
		log("operator--", "popped back");
	}
	inline void operator-- (int) {
		internalVec.pop_back();
		log("operator--", "popped back");
	}

	// append value to vector
	inline void operator+= (const T& value) {
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
	inline void operator= (const std::vector<T>& newish) {
		internalVec = newish;
		log("operator=", "assigned new vector");
	}
	// assign internal vector to new vector from other VecWrapper
	inline void operator= (VecWrapper newish) {
		internalVec = newish.internalVec;
		log("operator=", "assigned new vector from VecWrapper");
	}
	// assign internal vector to nothing
	inline void operator= (void* _) {
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

/**
 * @brief Class for matrices. 
*/
template <uint16_t Rows, uint16_t Columns>
class Matrix {
public:
	std::array<std::array<float,Columns>,Rows> Array;

	Matrix(
		const std::initializer_list<std::initializer_list<float>>& array
	) {
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				Array[i][x] = array.begin()[i].begin()[x];
			}
		}
	}
	Matrix() {
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				Array[i][x] = 0;
			}
		}
	}

	/**
	 * @brief Returns the transpose of the matrix
	 * 
	 * @return the transposed matrix
	*/
	Matrix transpose() {
		Matrix<Columns,Rows> toReturn {};
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				toReturn.Array[x][i] = Array[i][x];
			}
		}
		return toReturn;
	}

	/**
	 * @brief Returns the determinant of the matrix
	 * 
	 * @return a double that is the determinant of the matrix
	*/
	double determinant() {
		if (Rows != Columns)
			throw std::invalid_argument("Matrix must be square");
		
		if (Rows == 1) [[unlikely]]
			return Array[0][0];
		
		else if (Rows == 2)
			return Array[0][0] * Array[1][1] 
				 - Array[0][1] * Array[1][0];
		
		else if (Rows == 3) 
			return Array[0][0] * Array[1][1] * Array[2][2] 
				 + Array[0][1] * Array[1][2] * Array[2][0] 
				 + Array[0][2] * Array[1][0] * Array[2][1] 
				 - Array[0][2] * Array[1][1] * Array[2][0] 
				 - Array[0][1] * Array[1][0] * Array[2][2] 
				 - Array[0][0] * Array[1][2] * Array[2][1];

		else if (Rows == 4)
			return Array[0][0] * Array[1][1] * Array[2][2] * Array[3][3] 
				 + Array[0][1] * Array[1][2] * Array[2][3] * Array[3][0] 
				 + Array[0][2] * Array[1][3] * Array[2][0] * Array[3][1] 
				 + Array[0][3] * Array[1][0] * Array[2][1] * Array[3][2] 
				 - Array[0][3] * Array[1][2] * Array[2][1] * Array[3][0] 
				 - Array[0][2] * Array[1][1] * Array[2][0] * Array[3][3] 
				 - Array[0][1] * Array[1][0] * Array[2][3] * Array[3][2] 
				 - Array[0][0] * Array[1][3] * Array[2][2] * Array[3][1];
		
		else throw std::invalid_argument("Determinant currently only works for 4x4 and below matricies.");
	}

	/* double determinant() {
		if (Rows != Columns) throw std::invalid_argument("Matrix is not square");

		if (Rows == 1) return Array[0][0];
		if (Rows == 2) return Array[0][0] * Array[1][1] - Array[0][1] * Array[1][0];

		double toReturn = 0;
		for (uint16_t i = 0; i < Rows; ++i) {
			Matrix<Rows-1,Columns-1> subMatrix {};
			for (uint16_t x = 1; x < Rows; ++x) {
				for (uint16_t y = 0; y < Columns; ++y) {
					if      (y < i) subMatrix.Array[x-1][y]   = Array[x][y];
					else if (y > i) subMatrix.Array[x-1][y-1] = Array[x][y];
				}
			}
			toReturn += Array[0][i] * subMatrix.determinant() * (i % 2 ? -1 : 1);
		}
		return toReturn;
	} */


	Matrix operator+ (const Matrix& other) {
		Matrix toReturn = *this;
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				toReturn.Array[i][x] += other.Array[i][x];
			}
		}
		return toReturn;
	}
	Matrix operator- (const Matrix& other) {
		Matrix toReturn = *this;
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				toReturn.Array[i][x] -= other.Array[i][x];
			}
		}
		return toReturn;
	}

	Matrix operator+= (const Matrix& other) {
		Array = Array + other.Array;
		return *this;
	}
	Matrix operator-= (const Matrix& other) {
		Array = Array - other.Array;
		return *this;
	}

	template <uint16_t otherRows, uint16_t otherColumns>
	requires(otherRows == Columns)
	Matrix<Rows,otherColumns> operator* (const Matrix<otherRows,otherColumns>& other) {
		Matrix<Rows,otherColumns> toReturn {};

		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < otherColumns; ++x) {
				for (uint16_t y = 0; y < Columns; ++y) {
					toReturn.Array[i][x] += Array[i][y] * other.Array[y][x];
				}
			}
		}
		return toReturn;
	}
	template <typename T>
	Matrix<Rows,1> operator* (const std::vector<T>& vec) {
		if (Columns != vec.size()) {
			throw std::invalid_argument("Matrix dimensions do not match");
		}
		Matrix<Rows,1> toReturn {};

		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				toReturn.Array[i][0] += Array[i][x] * vec[x];
			}
		}
		return toReturn;
	}
	Matrix operator* (double scalar) {
		Matrix toReturn = *this;
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				toReturn.Array[i][x] *= scalar;
			}
		}
		return toReturn;
	}

	template <uint16_t otherRows, uint16_t otherColumns>
	Matrix<Rows,otherColumns> operator*= (const Matrix<otherRows,otherColumns>& other) {
		Array = Array * other.Array;
		return *this;
	}
	template <typename T>
	Matrix<Rows,1> operator*= (const std::vector<T>& vec) {
		Array = Array * vec;
		return *this;
	}
	Matrix operator*= (double scalar) {
		Array = Array * scalar;
		return *this;
	}

	friend std::ostream& operator<< (
		std::ostream& os, const Matrix& other
	) {
		for (uint16_t i = 0; i < Rows; ++i) {
			for (uint16_t x = 0; x < Columns; ++x) {
				os << other.Array[i][x] << " ";
			}
			os << "\n";
		}
		return os;
	}
};

namespace EasyTypes {
	typedef unsigned char  byte;
	
	typedef unsigned char       u8;
	typedef unsigned short      u16;
	typedef unsigned int        u32;
	typedef unsigned long long  u64;
	typedef unsigned __int128   u128;
	
	typedef char       i8;
	typedef short      i16;
	typedef int        i32;
	typedef long long  i64;
	typedef __int128   i128;

	typedef float   f32;
	typedef double  f64;

	typedef std::string  string;
	typedef const char*  cstring;
};

};