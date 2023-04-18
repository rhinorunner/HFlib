#pragma once

// full of useless funnies

#include <iostream>
#include <vector>

#include "HFlib.hpp"

namespace HFL {

std::string zooborkText(const std::string& str) 
{
    const std::vector<std::string> wset1 = {"zeeple", "florp", "reeb", "wooba", "yibble", "snorp", "wombo", "tuba", "greek", "snop", "bingle", "dong", "zooka", "glob", "glomp", "flub", "pleb", "vorp", "uba", "de", "dee", "zou", "zomb", "bing", "zat", "pibble", "dingo", "forp"};
    const std::vector<std::string> wset2 = {"gpipz", "bvazevly", "zeemot", "meepils", "blanjar", "norzal", "benjo", "glomber", "droobus", "yunwi", "porpus", "gronmble", "gleepglo", "loobla", "glorppro", "zerbimm", "glivin", "zirbing", "zazintool", "plingleforp"};
    const std::vector<std::string> punct = {" "," "," "," "," "," "," "," "," "," "," "," ",", ",", ",", ",", "};
    const std::vector<std::string> ends = {". ",". ",". ","? ","! ","!!! ","??? ","!? "};

    uint64_t words = wordCount(str);
    std::string toReturn = "";

    if (words == 1) return (rand() % 2) 
        ? (wset1[rand() % wset1.size()]) 
        : (wset2[rand() % wset2.size()]);

    srand(time(0));
    bool lastPunc = false;
    for (uint64_t i = 0; i < words; ++i) {
        uint8_t RND = rand() % 10;
        if ((0 <= RND) && (RND <= 2)) {
            toReturn += 
                wset1[rand() % wset1.size()] +
                wset1[rand() % wset1.size()];
            lastPunc = false;
        }
        else if ((3 <= RND) && (RND <= 4)) {
            toReturn += 
                wset1[rand() % wset1.size()];
            lastPunc = false;
        }
        else if ((5 <= RND) && (RND <= 8)) {
            toReturn += 
                wset2[rand() % wset2.size()];
            lastPunc = false;
        }
        else if (RND == 9) {
            if ((i == 0) || (i == words-1) || lastPunc) continue;
            toReturn += ends[rand() % ends.size()];
            lastPunc = true;
        }
        if ((RND != 9) && (i != words-1)) {
            toReturn += punct[rand() % punct.size()];
            lastPunc = true;
        }
    }
    toReturn += ends[rand() % ends.size()];
    return toReturn;
}

}