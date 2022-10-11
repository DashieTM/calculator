#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <sstream>
#include <fstream>
#include <iterator>

class Calculator{
  protected:
    std::vector<std::string> tokens;
    std::map<std::string , std::string> vars;
    std::string current;
    bool openBracket;
    const std::string homedir = getenv("HOME");
    const std::string vardir = homedir + "/.local/share/calc/vars.txt";

    enum ErrorCode{
      DIVBYZERO, NOTANOPERATOR, NOTANUMBER, BRACKEDERROR
    };
  private:

  public:
    Calculator();
    void next();
    bool hasNext();
    double handleExpression();
    double handleTerm();
    double handleFactor();
    void read_vars();
    void push_vars();
    void interface(bool fancy);
    void interface(bool fancy, std::istream& is);
    std::string calculate(std::vector<std::string>& input);
    std::string gui(std::string& str, bool var_edit);
    std::string handle_vars(std::vector<std::string>& str);
    std::string write_var(std::string &key, std::string &value);
    std::string delete_vars(std::string& delkey);
    std::vector<std::string> get_tokens();
    std::map<std::string, std::string> get_vars();
    
    static int testat_interface(std::string expr);
    static void greeting();
    static std::string testinterface(std::string str);
    static bool isOperator(char& op);
    static std::vector<std::string> splitString(std::string& input);
};

auto calc(int first, int second, char op) -> int;
auto calc(std::istream & stream) -> int;
