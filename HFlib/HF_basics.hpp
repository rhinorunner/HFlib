#pragma once

#include <iostream>
#include <vector>
#include <string>

// <BAD> probably not the best thing to have in here
// needed for Audio
#include "HF_misc.hpp"

#ifdef _WIN32
	#include <tchar.h>
	#include <windows.h>
		//#pragma COMPILER diagnostic push
		//#pragma COMPILER diagnostic ignored "-Wunknown-pragmas"
		#pragma comment(lib, "Winmm.lib")
		#pragma comment(lib, "user32.lib")
		//#pragma COMPILER diagnostic pop
	#define UNICODE
#else
	#include <unistd.h>
#endif

// Helpful Functions library
namespace HFL {

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

// sleep function
inline void sleep(uint64_t ms) {
	#ifdef _WIN32
	Sleep(ms);
	#else
	usleep(ms*1000);
	#endif
}

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
} // taken from https://stackoverflow.com/questions/15580179/how-do-i-find-the-name-of-an-operating-system

// returns the name of the compiler
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
void WIN_setConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// sets the console to utf-16
inline void WIN_utf16Console() {system("chcp 65001");}

#endif

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

// returns the index(es) of a value in a vector
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

// basic audio player
class Audio {
public:
	Audio(const std::string& file) : File(file) {openFile(file);}

	~Audio() {}

	// play the audio file (WORKS FOR NON-WIN)
	bool play(bool loop = false) {
		#ifdef _WIN32
		std::string S1 = "play " + File + (loop?" repeat":"");
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		std::string command = "play " + audioFile;
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
		#endif
	}

private:
	std::string File;

	// return false if file cannot be opened
	void openFile(const std::string& file) {
		bool opened = true;

		#ifdef _WIN32
		// check if file is empty
		std::string S2 = "status " + file + " length";
		char buffer[128];
		std::string err = HFL::mciErrorLookup(
			mciSendString(TEXT(S2.c_str()), buffer, 128, NULL)
		);

		try {
			[[maybe_unused]] auto _ = std::stoi(buffer);
		} catch (const std::invalid_argument& e) {
			// file size cannot be checked
			opened = false;
		}
		
		#else
		// <OSS>
		#endif

		if (!opened) [[unlikely]]
			throw std::runtime_error("Failed to open audio file \"" + file + "\"\n" + err);
	}
};

};