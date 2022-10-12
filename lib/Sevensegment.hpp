#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

auto printLargeDigit(int i, std::ostream &out) -> void;
auto printLargeNumber(int i, std::ostream &out) -> void;
auto printLargeError(std::ostream &out) -> void;

void printDigit(std::string& str, std::ostream& stream);
void printDigit(int i, std::ostream& stream);
void writeChar(std::string* arr, char i);
void printErr(std::ostream& stream);


