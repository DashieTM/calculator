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
  std::vector<std::string> expressions;
  std::vector<std::string> results;
  std::map<std::string, std::string> vars;
  std::string current;
  bool b_open_bracket;
  bool b_expect_number;
  const std::string homedir = getenv("HOME");
  const std::string vardir = homedir + "/.local/share/calc/vars.txt";

private:
public:
  
  class ZeroDivisionException : public std::exception {};
  class NotAnOperatorException : public std::exception {};
  class NotANumberException : public std::exception {};
  class BrackedException : public std::exception {};
  class StreamBadException : public std::exception {};
  
  Calculator();
  void next();
  bool hasNext();
  double handleExpression();
  double handleTerm();
  double handleFactor();
  void readVars();
  void pushVars();
  void interface(bool fancy, std::istream &is = std::cin);
  void testatInterface(std::istream & is, std::ostream& os);
  void setTokens(std::vector<std::string> &tokens);
  void clearResults();
  void clearExpressions();
  std::string calculate(std::vector<std::string> &input);
  std::string gui(std::string &str, bool var_edit);
  std::string handleVars(std::vector<std::string> &str);
  std::string writeVar(std::string &key, std::string &value);
  std::string deleteVars(std::string &delkey);
  std::string getResults();
  std::string getVarList();
  std::vector<std::string> getTokens();
  std::vector<std::string> getExpressions();
  std::map<std::string, std::string> getVars();

  static double test_interface(std::string expr);
  static void greeting();
  static bool isOperator(char &op);
  static std::vector<std::string> splitString(std::string &input);
};

auto calc(int, int, char) -> int;
auto calc(std::istream &) -> int;
