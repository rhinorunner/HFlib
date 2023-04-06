#pragma once

#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
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
}
// taken from https://stackoverflow.com/questions/15580179/how-do-i-find-the-name-of-an-operating-system

#ifdef _WIN32
// sets the terminal cursor, doesnt seem to wrok
void WIN_setConsoleCursor(const bool& showFlag) {
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

// audio player
class Audio {
public:
	Audio(const std::string& file) : File(file) {}

	~Audio() {}

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

	bool pause() {
		#ifdef _WIN32
		std::string S1 = "pause " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

	bool resume() {
		#ifdef _WIN32
		std::string S1 = "resume " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

	bool stop() {
		#ifdef _WIN32
		std::string S1 = "stop " + File;
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

	bool playFrom(int64_t from) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from);
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

	bool play_wait() {
		#ifdef _WIN32
		std::string S1 = "play " + File + " wait";
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

	bool playFrom_wait(int64_t from) {
		#ifdef _WIN32
		std::string S1 = "play " + File + " from " + std::to_string(from) + " wait";
		mciSendString(TEXT(S1.c_str()), NULL, 0, NULL);
		#else
		// ...
		#endif

		return true;
	}

private:
	std::string File;
};

};