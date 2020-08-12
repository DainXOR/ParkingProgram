#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <ctime>

/// Returns time in Hours:Minutes
std::string getTimeStr();

/// Returns date in Days-Months-Years
std::string getDateStr();

/// Converts a std::string into a int
int StrToInt(std::string Str);

/// Converts a int into a std::string
std::string IntToStr(int Num);

/// Converts a std::string into a float
float StrToDec(std::string Str);

/// Converts a float into a std::string
std::string DecToStr(float Num);

#endif // FUNCTIONS_H
