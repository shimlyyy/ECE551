#ifndef __COMMON_H__
#define __COMMON_H__
#include "nmrExp.h"
bool is_AllLetter(std::string & str);
void skipSpace(std::string::iterator & it);
std::string find_str(std::string::iterator & it);
bool isValidRop(std::string & op);
bool isValidBop(std::string & op);
bool isValidFname(std::string & op, std::map<std::string, Function *> MyFunction);
bool is_ValidNumber(std::string & str);
void bracket_macth(std::string & side);
#endif
