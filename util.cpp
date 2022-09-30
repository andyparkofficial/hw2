#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> keyWords;
  std::string tempWord = "";

  for (unsigned int i = 0; i < rawWords.length(); i++){
    if (ispunct(rawWords[i]) || isspace(rawWords[i]) || i == rawWords.length()-1) {
        if (tempWord.length()>1){
            if (i == rawWords.length()-1){
                tempWord += rawWords[i];
            }
            keyWords.insert(tempWord);
            tempWord = "";
        } else {
            tempWord = "";
        }
    } else {
        if(isupper(rawWords[i])){
            tempWord += tolower(rawWords[i]);
        } else{
            tempWord += rawWords[i];
        }
        
    }
  }

  return keyWords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
