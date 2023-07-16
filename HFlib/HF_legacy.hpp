#pragma once

#include <iostream>
#include <vector>

#ifdef _WIN32
	#include <Windows.h>
	#include <mmsystem.h>
	#pragma comment(lib, "winmm.lib")
#else
	#include <unistd.h>
#endif

namespace hfl_legacy {

/**
 * @brief Converts a string to a vector<char>.
 * 
 * @param str the string to convert
 * 
 * @return a vector<char> with the converted string
*/
std::vector<char> strToCVec(const std::string& str) {
	std::vector<char> converted;
	for (char x : str) {
		converted.push_back(x);
	}
	return converted;
}

/**
 * @brief Converts a vector<char> to a string.
 * 
 * @param cvec the vector<char> to convert
 * 
 * @return a string with the converted vector<char>
*/
std::string CVecToStr(const std::vector<char>& cvec) {
	std::string converted;
	for (char x : cvec) {
		converted += x;
	}
	return converted;
}

// basic audio player for small files
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
		//std::string err = hfl::mciErrorLookup(mciSendString(TEXT(S2.c_str()), buffer, 128, NULL));
		std::string err = "unknown";

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

}