#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <sstream>
#include <fstream>

class calc{
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
      calc();
      void next();
      bool hasNext();
      double handleExpression();
      double handleTerm();
      double handleFactor();
      void write_var(std::string &key, std::string &value);
      void read_vars();
      void push_vars();
      void delete_vars(std::string& delkey);
      std::string calculate(std::vector<std::string>& input);
      std::string gui(std::string& str);
      void interface();
      
      static void greeting();
      static std::string testinterface(std::string str);
      static bool isOperator(char& op);
      static std::vector<std::string> splitString(std::string& input);

};

