#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>

class calc{
  protected:
      std::vector<std::string> tokens;
      std::string current;
      bool openBracket;

      enum ErrorCode{
        DIVBYZERO, NOTANOPERATOR, NOTANUMBER, BRACKEDERROR
      };
  private:


  public:
      calc(std::vector<std::string>& input);
      void next();
      bool hasNext();
      double handleExpression();
      double handleTerm();
      double handleFactor();

      static std::string calculate(std::vector<std::string>& input);
      static void greeting();
      static std::string gui(std::string& str);
      static std::string testinterface(std::string str);
      static bool isOperator(char& op);
      static void interface();
      static std::vector<std::string> splitString(std::string& input);

};

