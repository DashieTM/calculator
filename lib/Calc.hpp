#pragma once
#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Calculator {
protected:
  std::vector<std::string> tokens;
  std::map<std::string, std::string> vars;
  std::string current;
  bool b_open_bracket;
  const std::string homedir = getenv("HOME");
  const std::string vardir = homedir + "/.local/share/calc/vars.txt";

  class ZeroDivisionException : public std::exception {};
  class NotAnOperatorException : public std::exception {};
  class NotANumberException : public std::exception {};
  class BrackedException : public std::exception {};

private:
public:
  Calculator();
  void next();
  bool hasNext();
  double handleExpression();
  double handleTerm();
  double handleFactor();
  void readVars();
  void pushVars();
  void interface(bool fancy);
  void interface(bool fancy, std::istream &is);
  void setTokens(std::vector<std::string> &tokens);
  std::string calculate(std::vector<std::string> &input);
  std::string gui(std::string &str, bool var_edit);
  std::string handleVars(std::vector<std::string> &str);
  std::string writeVar(std::string &key, std::string &value);
  std::string deleteVars(std::string &delkey);
  std::vector<std::string> getTokens();
  std::map<std::string, std::string> getVars();

  static int testatInterface(std::string expr);
  static void greeting();
  static std::string testinterface(std::string str);
  static bool isOperator(char &op);
  static std::vector<std::string> splitString(std::string &input);
};

auto calc(int, int, char) -> int;
auto calc(std::istream &) -> int;
