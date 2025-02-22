#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

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

  std::set<string> wordset;
  std::string temp;
  rawWords = convToLower(rawWords);
   
  for(std::string::iterator it = rawWords.begin(); it!= rawWords.end(); it++){
    if(std::isalnum(*it)){ //if char is alphabet or number

        temp += *it;

    }else{ //punctuation or space
      if(temp.length()>=2){ //only process word >=2 characters

        wordset.insert(temp);
      }

      temp.clear();
      }

    }
    if(temp.length()>=2){ //process the last word

      wordset.insert(temp);
    }
  return wordset;



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
