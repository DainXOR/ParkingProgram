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

/// Return quantity of 0 and 1, but only the bigger count
int Count01(std::string Num);

/// Separates a long binary string into a key size binary strings
void BinRedimension(const std::string &Var1, std::string Str2[], const int &Key);

/// Gets a single character and returns it as its binary form
int TextToBin(int Num);

/// Gets a binary string and retruns it as a normal characters string
std::string BinToText(std::string &BinStr);

/// Returns the digits count of a given number
int NumDigits(int Num);

#endif // FUNCTIONS_H
