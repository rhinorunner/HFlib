#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifdef _WIN32
	#include <tchar.h>
	#include <windows.h>
	#include <mmsystem.h>
	#include <conio.h>
	#define UNICODE
#else
	#include <unistd.h>
#endif

#define  INT4_MAX  7
#define  INT4_MIN -8
#define UINT4_MAX  15

static const unsigned __int128 UINT128_MAX = __uint128_t(__int128_t(-1L));
static const          __int128  INT128_MAX = UINT128_MAX >> 1;
static const          __int128  INT128_MIN = -INT128_MAX - 1;

#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)

// Helpful Functions library
namespace hfl {

/**
 * @brief Clears the screen. 
 * 
 * @param type 0 = 72 newlines (can be changed), 1 = system() based clear screen, 2 = ANSI escape sequence, 3 = Windows API, 4 = ANSI code
 * @param newLineCharNum the number of newlines to print (only for type 0)
 * 
 * @note type 3 is only available on Windows and will default to type 2
*/
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
			#ifdef _WIN32
			system("cls");
			#else
			system("clear");
			#endif
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

/**
 * @brief Sleeps for a certain amount of milliseconds. 
 * 
 * @param ms the number of milliseconds to sleep for
*/
inline void sleep(uint64_t ms) {
	#ifdef _WIN32
	Sleep(ms);
	#else
	usleep(ms*1000);
	#endif
}

/**
 * @brief Returns the name of the current operating system. 
 * 
 * @return a string with the name of the current operating system
*/
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
} // taken from https://stackoverflow.com/questions/15580179/how-do-i-find-the-name-of-an-operating-system

/** 
 * @brief Returns the name of the current compiler.
 * 
 * @return a string with the name of the current compiler
*/
inline std::string getCompilerName() {
	#ifdef __clang__
	return "clang";
	#elif __GNUC__
	return "g++";
	#elif __MINGW32__
	return "minGW";
	#elif __MINGW64__
	return "minGW64";
	#elif _MSC_VER
	return "msvc";
	#else
	return "other";
	#endif
}

#ifdef _WIN32
// <FIX> sets the terminal cursor, doesnt seem to work

/** 
 * @brief Sets the console cursor visibility.
 * 
 * @param showFlag true = show cursor, false = hide cursor
 * 
 * @note Windows only
 * @warning DOES NOT WORK
*/
void setConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

/**
 * @brief Sets the console to UTF-16.
 * 
 * @note Windows only
*/
inline void utf16Console() {system("chcp 65001");}

#endif

/**
 * @brief Returns the mean of any container
 * 
 * @tparam T the type of the container
 * 
 * @param arr the container to find the mean of
*/
template <typename T>
inline double mean(const T& arr) {
	try { [[maybe_unused]] auto size = arr.size(); } 
	catch (...) {
		throw std::invalid_argument("Container must have a size() method");
	}
	if (arr.size() == 0) 
		throw std::invalid_argument("Container must have a size > 0");
	try { [[maybe_unused]] auto test = arr.begin(); }
	catch (...) {
		throw std::invalid_argument("Container must have a begin() method");
	}
	try { [[maybe_unused]] auto test = *arr.begin() + 1; } 
	catch (...) {
		throw std::invalid_argument("Container must be of an integer type");
	}

	double sum = 0;
	for (auto& i : arr) sum += i;
	return sum / arr.size();
}
/**
 * @brief Returns the mean of any array
 * 
 * @tparam T the type of the array
 * 
 * @param arr the container to find the mean of
 * @param size size of the array
 * 
 * @return the mean of the array
*/
template <typename T>
inline double mean(const T* arr, uint64_t size) {
	if (size == 0) throw std::invalid_argument("Array must have a size > 0");
	try { [[maybe_unused]] auto test = *arr[0] + 1; } 
	catch (...) {
		throw std::invalid_argument("Array must be of an integer type");
	}
	
	double sum = 0;
	for (uint64_t i = 0; i < size; ++i) sum += arr[i];
	return sum / size;
}

/**
 * @brief Returns the smallest value inside a container. 
 * 
 * @tparam T the type of the container
 * 
 * @param arr the container to find the smallest value of
 * 
 * @return the smallest value inside the container
*/
template <typename T>
inline T min(const T& arr) {
	try { [[maybe_unused]] auto size = arr.size(); } 
	catch (...) {
		throw std::invalid_argument("Container must have a size() method");
	}
	if (arr.size() == 0) 
		throw std::invalid_argument("Container must have a size > 0");
	try { [[maybe_unused]] auto test = arr.begin(); }
	catch (...) {
		throw std::invalid_argument("Container must have a begin() method");
	}
	try { [[maybe_unused]] auto test = *arr.begin() + 1; } 
	catch (...) {
		throw std::invalid_argument("Container must be of an integer type");
	}

	T min = arr[0];
	for (auto& i : arr) if (i < min) min = i;
	return min;
}
/**
 * @brief Returns the smallest value inside an array. 
 * 
 * @tparam T the type of the array
 * 
 * @param arr the array to find the smallest value of
 * @param size size of the array
 * 
 * @return the smallest value inside the array
*/
template <typename T>
inline T min(const T* arr, uint64_t size) {
	if (size == 0) throw std::invalid_argument("Array must have a size > 0");
	try { [[maybe_unused]] auto test = *arr[0] + 1; } 
	catch (...) {
		throw std::invalid_argument("Array must be of an integer type");
	}
	
	T min = arr[0];
	for (uint64_t i = 0; i < size; ++i) if (arr[i] < min) min = arr[i];
	return min;
}

/**
 * @brief Returns the largest value inside a container. 
 * 
 * @tparam T the type of the container
 * 
 * @param arr the container to find the largest value of
 * 
 * @return the largest value inside the container
*/
template <typename T>
inline T max(const T& arr) {
	try { [[maybe_unused]] auto size = arr.size(); } 
	catch (...) {
		throw std::invalid_argument("Container must have a size() method");
	}
	if (arr.size() == 0) 
		throw std::invalid_argument("Container must have a size > 0");
	try { [[maybe_unused]] auto test = arr.begin(); }
	catch (...) {
		throw std::invalid_argument("Container must have a begin() method");
	}
	try { [[maybe_unused]] auto test = *arr.begin() + 1; } 
	catch (...) {
		throw std::invalid_argument("Container must be of an integer type");
	}

	T max = arr[0];
	for (auto& i : arr) if (i > max) max = i;
	return max;
}
/**
 * @brief Returns the largest value inside an array. 
 * 
 * @tparam T the type of the array
 * 
 * @param arr the array to find the largest value of
 * @param size size of the array
 * 
 * @return the largest value inside the array
*/
template <typename T>
inline T max(const T* arr, uint64_t size) {
	if (size == 0) throw std::invalid_argument("Array must have a size > 0");
	try { [[maybe_unused]] auto test = *arr[0] + 1; } 
	catch (...) {
		throw std::invalid_argument("Array must be of an integer type");
	}
	
	T max = arr[0];
	for (uint64_t i = 0; i < size; ++i) if (arr[i] > max) max = arr[i];
	return max;
}

/**
 * @brief Returns the index(es) of a value in a vector.
 * 
 * @tparam T the type of the vector
 * @param vector the vector to search
 * @param value the value to search for
 * 
 * @return a vector<uint64_t> with the index(es) of the value in the vector
*/
template <typename T>
std::vector<uint64_t> getIndexes(
	const std::vector<T>& vector,
	const T& value
) {
	std::vector<uint64_t> indexes;
	for (uint64_t i = 0; i < value.size(); i++) 
		if (vector[i] == value) indexes.push_back(i);
	return indexes;
}

#ifdef _WIN32
/**
 * @brief Gets keypress input.
 * 
 * @return the keypress input
*/
inline uint8_t getKey() {
	while (true) {
		uint8_t keyIn = (uint8_t) getch();
		if (keyIn == 3) {exit(0);}
		return keyIn;
	}
}
#else
/**
 * @brief Gets keypress input.
 * 
 * @return the keypress input
*/
inline uint8_t getKey() {
	while (true) {
		system("stty raw");
        uint8_t keyIn = (uint8_t) getchar(); 
        system("stty cooked");
		if (keyIn == 3) {exit(0);}
		return keyIn;
	}
}
#endif

/**
 * @brief vec2 from vec1
 * 
 * @tparam T the type of the vectors
 * 
 * @param vec1 the vector to subtract from
 * @param vec2 the vector to subtract
 * 
 * @return vec1 - vec2
 */
template <typename T>
std::vector<T> subtractVec(
	std::vector<T> vec1,
	const std::vector<T>& vec2
) {
	// find items in vec2 and if they are in vec1, remove them
	// then return vec1
	for (auto i : vec2) {
		for (uint16_t c = 0; c < vec1.size(); ++c) {
			if (vec1[c] == i) {
				vec1.erase(vec1.begin()+c);
				break;
			}
		}
	}
	return vec1;
}

/**
 * @brief Gets user input in a safe way.
 * 
 * @param prompt the prompt to display
 * 
 * @return the user input
*/
std::string getInput(
	const std::string& prompt = ""
) {
	std::string input;
	std::cout << prompt;
	std::getline(std::cin, input);
	return input;
}

// fast in range function
/**
 * @brief Checks if a value is in a range, quickly. 
 * 
 * @param val the value to check
 * @param min the minimum value of the range
 * @param max the maximum value of the range
 * 
 * @return true if the value is in the range, false otherwise
*/
constexpr inline bool inRange(
    uint64_t val, uint64_t min, uint64_t max
) {
    return ((val-min) | (max-val)) >= 0;
}

/**
 * @brief Counts the amount of words in a string. 
 * 
 * @param str the string to count the words in
 * @param delimiters the delimiters to use (default are common delimiters)
 * 
 * @return the amount of words in the string
*/
uint64_t wordCount(
    const std::string& str,
    const std::vector<char>& delimiters 
        = {' ',',','.','!','?','\'','\"','\n','\t'}
) {
    uint64_t count = 0;
    bool inWord = false;
    for (const char& c : str) {
        if (inWord) {
            if (
                std::find(
                    delimiters.begin(), 
                    delimiters.end(), c
                ) != delimiters.end()
            ) inWord = false;
        } 
        else {
            if (
                std::find(
                    delimiters.begin(), 
                    delimiters.end(), c
                ) == delimiters.end()
            ) {inWord = true; count++;}
        }
    }
    return count;
}

/**
  * Runs the argument function and returns how long it took. 
  * 
  * @param toRun function to be run and timed
  * 
  * @return time it took to run the function
  * 
  * @note the tested function must have no parameters
  */
template <typename T>
double timeToRun(T (*toRun)()) {
	auto start = std::chrono::high_resolution_clock::now();
	toRun();
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<
		std::chrono::duration<double>
	> (end-start).count();
}

/**
 * @brief Choose an item from a vector in a fancy way. 
 * 
 * @tparam T the type of the items in vector
 * 
 * @param items the vector of items to choose from
 * @param prompt the prompt to display before choosing
 * @param illegalItems the items that are illegal to choose
 * @param illegalMessage the message to display if an illegal item is chosen
 * 
 * @return the chosen item
*/
template <typename T>
T chooseItem (
	const std::vector<T>& items,
	const std::string& prompt = "",
	const std::vector<T>& illegalItems = {},
	const std::string& illegalMessage = "illegal item"
) {
	uint16_t currentSelected = 0;
	// make sure T can be casted to string
	if (!items.size()) throw std::runtime_error("chooseItem(): 'items' cannot be emtpy.");
	try {[[maybe_unused]] std::string _ = std::to_string(items[0]);}
	catch (std::exception& e) {
		throw std::runtime_error("chooseItem(): type must be castable to string.");
	}
	if (items.empty())
	while (1) {
		clear();
		std::cout << prompt << '\n';

		for (uint16_t i = 0; i < items.size(); ++i) {
			if (i == currentSelected) [[unlikely]] {
				#ifdef _WIN32
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << std::to_string(items[i]) << '\n';
					SetConsoleTextAttribute(hConsole, 7);
				#else
					std::cout 
						<< "\u001b[32m" 
						<< std::to_string(items[i]) 
						<< "\u001b[0m\n";
				#endif
			} else [[likely]] {
				std::cout << std::to_string(items[i]) << '\n';
			}
		}

		uint8_t key = getKey();
		if (key == 224) {
			uint8_t key2 = getKey(); // second number
			switch (key2) {
				case 72: // up
					if (currentSelected == 0) [[unlikely]] 
						currentSelected = items.size()-1;
					else [[likely]]
						currentSelected--;
					break;
				case 80: // down
					if (currentSelected == items.size()-1) [[unlikely]] 
						currentSelected = 0;
					else [[likely]]
						currentSelected++;
					break;
			}
		}
		// spacebar or enter
		else if ((key == 32) || (key == 13)) {
			T selected = items[currentSelected];
			bool illegal = false;
			for (auto x : illegalItems) 
				if (x == selected) [[unlikely]] {
					std::cout << illegalMessage << '\n';
					illegal = true;
					hfl::sleep(1000);
					//getchar();
					break;
				}
			if (!illegal) return selected;
		}
	}
}

/**
 * @brief A basic audio player for small files.
*/
/*
class Audio {
public:
	Audio(const std::string& file) : File(file) {openFile(file);}

	~Audio() {
		// close file
		#ifdef _WIN32
		std::string S1 = "close " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif
	}

	// play the audio file (WORKS FOR NON-WIN)
	bool play(bool loop = false) {
		#ifdef _WIN32
		std::string S1 = "play " + File + (loop?" repeat":"");
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		std::string command = "play " + File;
		system(command.c_str());
		#endif

		return true;
	}

	// pause the audio file
	bool pause() {
		#ifdef _WIN32
		std::string S1 = "pause " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// resume the audio file
	bool resume() {
		#ifdef _WIN32
		std::string S1 = "resume " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// stop the audio file
	bool stop() {
		#ifdef _WIN32
		std::string S1 = "stop " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// play the audio file from a certain time
	bool playFrom(int64_t from) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// play the audio file from a certain time to a certain time
	bool playFromTo(int64_t from, int64_t to) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from) + " to " + std::to_string(to);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// play the audio file and wait for it to finish
	bool play_wait() {
		#ifdef _WIN32
		std::string S1 = "play " + File + " wait";
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// play the audio file from a certain time and wait for it to finish
	bool playFrom_wait(int64_t from) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from) + " wait";
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// play the audio file from a certain time to a certain time and wait for it to finish
	bool playFromTo_wait(int64_t from, int64_t to) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from) + " to " + std::to_string(to) + " wait";
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// change the audio file
	void changeFile(const std::string& file) {
		File = file;
	}

	// get the length of the audio file
	int64_t getLength() {
		#ifdef _WIN32
		std::string S1 = "status " + File + " length";
		char buffer[128];
		mciSendString(TEXT(S1.c_str()), buffer, 128, NULL);
		return std::stoi(buffer);
		#else
		// <OSS>
		return 0;
		#endif
	}

	// get the current position of the audio file
	int64_t getPosition() {
		#ifdef _WIN32
		std::string S1 = "status " + File + " position";
		char buffer[128];
		mciSendString(TEXT(S1.c_str()), buffer, 128, NULL);
		return std::stoi(buffer);
		#else
		// <OSS>
		return 0;
		#endif
	}

	// get the name of the audio file
	std::string getFile() {return File;}

	// set the volume of the audio file
	bool setVolume(int64_t volume) {
		#ifdef _WIN32
		std::string S1 = "setaudio " + File + " volume to " + std::to_string(volume);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// get the volume of the audio file
	int64_t getVolume() {
		#ifdef _WIN32
		std::string S1 = "status " + File + " volume";
		char buffer[128];
		mciSendString(TEXT(S1.c_str()), buffer, 128, NULL);
		return std::stoi(buffer);
		#else
		// <OSS>
		return 0;
		#endif
	}

	// set the left channel audio
	bool setLeftChannel(int64_t volume) {
		#ifdef _WIN32
		std::string S1 = "setaudio " + File + " left volume to " + std::to_string(volume);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// set the right channel audio
	bool setRightChannel(int64_t volume) {
		#ifdef _WIN32
		std::string S1 = "setaudio " + File + " right volume to " + std::to_string(volume);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// <OSS>
		#endif

		return true;
	}

	// get the left channel audio
	int64_t getLeftChannel() {
		#ifdef _WIN32
		std::string S1 = "status " + File + " left volume";
		char buffer[128];
		mciSendString(TEXT(S1.c_str()), buffer, 128, NULL);
		return std::stoi(buffer);
		#else
		// <OSS>
		return 0;
		#endif
	}

	// get the right channel audio
	int64_t getRightChannel() {
		#ifdef _WIN32
		std::string S1 = "status " + File + " right volume";
		char buffer[128];
		mciSendString(TEXT(S1.c_str()), buffer, 128, NULL);
		return std::stoi(buffer);
		#else
		// <OSS>
		return 0;
		#endif
	}

private:
	std::string File;

	// return false if file cannot be opened
	// <ODD> not sure if this is the best way to do it
	void openFile(const std::string& file) {
		#ifndef _WIN32
			[[maybe_unused]]
		#endif
		bool opened = true;

		#ifdef _WIN32
		// check if file is empty
		std::string S2 = "status " + file + " length";
		char buffer[128];
		std::string err = hfl::mciErrorLookup(
			mciSendString(TEXT(S2.c_str()), buffer, 128, NULL)
		);

		try {
			[[maybe_unused]] auto _ = std::stoi(buffer);
		} catch (const std::invalid_argument& e) {
			// file size cannot be checked
			opened = false;
		}

		if (!opened) [[unlikely]]
			throw std::runtime_error("Failed to open audio file \"" + file + "\"\n" + err + ". This is most likely due to the file not existing or being too large.");
		
		#else
		// <OSS>
		#endif
	} 
};

*/

};