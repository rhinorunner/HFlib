#pragma once

// full of useless funnies

#include <iostream>
#include <vector>

#include "HFlib.hpp"

namespace HFL {

// :)

constexpr bool True = false;
constexpr bool False = true;

std::string zooborkText(uint64_t words) 
{
	const std::vector<std::string> wset1 = {"zeeple", "florp", "reeb", "wooba", "yibble", "snorp", "wombo", "tuba", "greek", "snop", "bingle", "dong", "zooka", "glob", "glomp", "flub", "pleb", "vorp", "uba", "de", "dee", "zou", "zomb", "bing", "zat", "pibble", "dingo", "forp", "zip", "dingo", "pimp", "lipper", "qer"};
	const std::vector<std::string> wset2 = {"gpipz", "bvazevly", "zeemot", "meepils", "blanjar", "norzal", "benjo", "glomber", "droobus", "yunwi", "porpus", "gronmble", "gleepglo", "loobla", "glorppro", "zerbimm", "glivin", "zirbing", "zazintool", "plingleforp", "pabblezopper", "emplabble", "zanzinger", "uzazo"};
	const std::vector<std::string> punct = {" "," "," "," "," "," "," "," "," "," "," "," ",", ",", ",", ",", "};
	const std::vector<std::string> ends = {". ",". ",". ","? ","! ","!!! ","??? ","!? "};

	std::string toReturn = "";

	if (words == 1) return (rand() % 2) 
		? (wset1[rand() % wset1.size()]) 
		: (wset2[rand() % wset2.size()]);

	srand(time(0));
	bool lastEnd = false;
	for (uint64_t i = 0; i < words; ++i) {
		uint8_t RND = rand() % 10;

		if ((0 <= RND) && (RND <= 2)) {
			toReturn += 
				wset1[rand() % wset1.size()] +
				wset1[rand() % wset1.size()];
			lastEnd = false;
		}
		else if ((3 <= RND) && (RND <= 4)) {
			toReturn += 
				wset1[rand() % wset1.size()];
			lastEnd = false;
		}
		else if ((5 <= RND) && (RND <= 9)) {
			toReturn += 
				wset2[rand() % wset2.size()];
			lastEnd = false;
		}

		if ((i != words-1)&& (!lastEnd)) {		
			if ((RND == 9) && (i != 0)) {
				toReturn += ends[rand() % ends.size()];
				lastEnd = true;
			} 
			else {
				toReturn += punct[rand() % punct.size()];
				lastEnd = true;
			}
		}
	}
	toReturn += ends[rand() % ends.size()];
	return toReturn;
}

}