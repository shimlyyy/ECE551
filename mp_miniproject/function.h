#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "nmrExp.h"

void split_test(std::string & line, std::map<std::string, Function *> & Myfunction);
void forNumint(std::string & line, std::map<std::string, Function *> & Myfunction);
void forMcint(std::string & line, std::map<std::string, Function *> & Myfunction);
void forGradient(std::string & line, std::map<std::string, Function *> & Myfunction, int choice);
#endif
