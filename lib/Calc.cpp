#include "Calc.hpp"
#include "Sevensegment.hpp"
#include <exception>
/*
 * standard grammar for calculator
 * exp := term | exp + term | exp - term
 * term := factor | factor * term | factor / term | factor % term
 * factor := number | ( exp )
 */

void Calculator::greeting() {
  std::cout << "A small calulator, various expressions allowed, operators + - "
               "/ * %.\n Or enter exit to exit\n";
}

std::string Calculator::handleVars(std::vector<std::string> &input) {
  if (input.front() == "add") {
    input.erase(input.begin());
    if (input.size() > 1) {
      return this->writeVar(input.at(0), input.at(1));
    } else {
      return "Please enter a variable and a number to assign.";
    }
  } else if (input.front() == "del") {
    input.erase(input.begin());
    if (input.size() > 0) {
      return this->deleteVars(input.at(0));
    }
  }
  return "";
}

void Calculator::interface(bool fancy, std::istream &is) {
  std::cout << "Enter an expression:\n";
  std::string line = "";
  if (std::getline(is, line) && !is.eof()) {
  } else {
    return;
  }
  if (line != "") {
    if (line == "exit") {
      return;
    } else if (line == "list") {
      std::cout << getResults();
    } else if (line == "vars") {
      std::cout << getVarList();
    } else {
      this->expressions.push_back(line);
      std::vector<std::string> input = Calculator::splitString(line);
      std::string varreturn = this->handleVars(input);
      if (varreturn != "") {
        std::cout << varreturn + "\n";
      } else {
        std::string result = this->calculate(input);
        if (result.front() == '-' || std::isdigit(result.front())) {
          if (fancy) {
            std::cout << "Result:\n";
            printDigit(result, std::cout);
          } else {
            std::cout << "Result: " << result << "\n";
          }
        } else {
          if (fancy) {
            this->expressions.pop_back();
            printErr(std::cout);
            std::cout << result << "\n";
          } else {
            this->expressions.pop_back();
            std::cout << result << "\n";
          }
        }
      }
    }
  }
  interface(fancy);
}

std::string Calculator::gui(std::string &str, bool var_edit) {
  this->expressions.push_back(str);
  std::vector<std::string> input = Calculator::splitString(str);
  if (var_edit) {
    this->expressions.pop_back();
    return this->handleVars(input);
  } else {
    std::string result = this->calculate(input);
    if (!std::isdigit(result.front()) && result.front() != '-') {
      this->expressions.pop_back();
    }
    return result;
  }
}

std::string Calculator::writeVar(std::string &key, std::string &value) {
  if (this->vars.find(key) != this->vars.end()) {
    return "Variable exists already!";
  }
  std::ofstream vars;
  vars.open(this->vardir, std::ios_base::app);
  if (vars.is_open()) {
    vars << key << std::endl;
    vars << value << std::endl;
    this->readVars();
    return "added " + key + " to variables with value " + value;
  } else
    return "Unable to open file";
}

std::string Calculator::deleteVars(std::string &delkey) {
  std::map<std::string, std::string>::iterator it;
  if (this->vars.find(delkey) != this->vars.end()) {
    this->vars.erase(delkey);
  } else {
    return "The variable " + delkey + " was not found in the list!";
  }

  std::ofstream vars(this->vardir);
  if (vars.is_open()) {
    for (auto e : this->vars) {
      if (e.first != "result") {
        vars << e.first << std::endl;
        vars << e.second << std::endl;
      }
    }
  } else {
    return "Unable to open file";
  }
  return "deleted the variable " + delkey;
}

void Calculator::readVars() {
  this->vars.clear();
  std::string key;
  std::string value;
  std::ifstream vars(this->vardir);
  if (vars.is_open()) {
    while (getline(vars, key)) {
      getline(vars, value);
      this->vars.insert(std::pair<std::string, std::string>(key, value));
    }
    vars.close();
    if (!this->results.empty()) {
      this->vars.insert(
          std::pair<std::string, std::string>("result", this->results.back()));
    }
  } else
    std::cout << "Unable to open file";
}

void Calculator::pushVars() {
  std::map<std::string, std::string>::iterator it;
  for (auto &e : this->tokens) {
    it = this->vars.find(e);
    if (it != this->vars.end()) {
      e = it->second;
    } else if (e.front() == '-') {
      std::string buffer = e;
      buffer.erase(buffer.begin());
      it = this->vars.find(buffer);
      if (it != this->vars.end()) {
        e = '-' + it->second;
      }
    }
  }
}

std::vector<std::string> Calculator::splitString(std::string &input) {
  std::string buffer = "";
  std::vector<std::string> tokens;
  bool digitLock = false;
  bool charLock = false;
  bool dotLock = false;
  bool opLock = true;
  bool opCurrent = false;
  for (auto &e : input) {
    if (std::isdigit(e) || (e == '.' && !dotLock) || (e == '-' && opLock)) {
      if (charLock) {
        charLock = false;
        tokens.push_back(buffer);
        buffer.clear();
      }
      if (e == '.')
        dotLock = true;
      if (e == '-') {
        opCurrent = true;
      } else {
        opCurrent = false;
      }
      opLock = false;
      digitLock = true;
      buffer += e;
      continue;
    } else if (digitLock && !opCurrent) {
      digitLock = false;
      dotLock = false;
      tokens.push_back(buffer);
      buffer.clear();
    }
    if (Calculator::isOperator(e)) {
      if (charLock) {
        charLock = false;
        tokens.push_back(buffer);
        buffer.clear();
      }
      buffer += e;
      tokens.push_back(buffer);
      opLock = true;
      buffer.clear();
    } else if (e != ' ') {
      buffer += e;
      charLock = true;
    } else if (charLock) {
      charLock = false;
      tokens.push_back(buffer);
      buffer.clear();
    }
  }
  if (buffer != "") {
    tokens.push_back(buffer);
  }
  return tokens;
}

bool Calculator::isOperator(char &op) {
  switch (op) {
  case '%':
    return true;
  case '/':
    return true;
  case '+':
    return true;
  case '-':
    return true;
  case '*':
    return true;
  case '(':
    return true;
  case ')':
    return true;
  default:
    return false;
  }
}

std::string Calculator::calculate(std::vector<std::string> &input) {
  this->tokens = input;
  try {
    this->pushVars();
    this->next();
    std::string result = std::to_string(this->handleExpression());
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    result.erase(result.find_last_not_of('.') + 1, std::string::npos);
    this->results.push_back(result);
    this->vars["result"] = result;
    return result;
  } catch (NotANumberException e) {
    return "Expected a number at " + this->current;
  } catch (ZeroDivisionException e) {
    return "Division and Modulo by 0 is not allowed!";
  } catch (NotAnOperatorException e) {
    return "Expected an operator at " + this->current;
  } catch (BrackedException e) {
    return "Open bracket not closed!";
  } catch (std::exception e) {
    return "Something went wrong...";
  }
  return "Something went wrong...";
}

Calculator::Calculator() {}

bool Calculator::hasNext() {
  if (!this->tokens.empty()) {
    return true;
  }
  return false;
}

void Calculator::next() {
  if (this->hasNext()) {
    this->current = this->tokens.front();
    tokens.erase(tokens.begin());
  } else {
    this->current = "";
  }
}

double Calculator::handleExpression() {
  double result = this->handleTerm();
  if (!this->b_expect_number) {
    while (this->current != "" && this->current != ")") {
      switch (this->current.front()) {
      case '+':
        this->next();
        this->b_expect_number = true;
        result += this->handleTerm();
        break;
      case '-':
        this->next();
        this->b_expect_number = true;
        result -= this->handleTerm();
        break;
      default:
        throw(NotAnOperatorException());
        break;
      }
    }
  }
  return result;
}

double Calculator::handleTerm() {
  double result = this->handleFactor();
  double div = 0;
  switch (this->current.front()) {
  case '*':
    this->next();
    this->b_expect_number = true;
    result *= this->handleTerm();
    break;
  case '/':
    this->next();
    this->b_expect_number = true;
    div = this->handleFactor();
    if (div == 0)
      throw(ZeroDivisionException());
    result /= div;
    if (isOperator(this->current.front())) {
      this->tokens.insert(tokens.begin(), this->current);
      this->current = std::to_string(result);
      result = this->handleTerm();
    }
    break;
  case '%':
    this->next();
    this->b_expect_number = true;
    div = this->handleFactor();
    if (div == 0)
      throw(ZeroDivisionException());
    result = (double)((int)result % (int)div);
    if (isOperator(this->current.front())) {
      this->tokens.insert(tokens.begin(), this->current);
      this->current = std::to_string(result);
      result = this->handleTerm();
    }
    break;
  default:
    break;
  }
  return result;
}

double Calculator::handleFactor() {
  double result = 0;
  if (this->current == "(") {
    this->next();
    result = this->handleExpression();
    if (this->current != ")") {
      throw(BrackedException());
    }
    this->next();
    this->b_expect_number = false;
  } else {
    if (!std::isdigit(this->current.front())) {
      if (this->current.length() < 2 || this->current.front() != '-') {
        throw(NotANumberException());
      }
    }
    result = std::stod(this->current);
    this->next();
    this->b_expect_number = false;
  }
  return result;
}

std::vector<std::string> Calculator::getTokens() { return this->tokens; }

std::string Calculator::getResults() {
  std::string buffer = "";
  for (int i = 0; i < this->expressions.size(); i++) {
    buffer += (this->expressions.at(i) + " = " + this->results.at(i)) + "\n";
  }
  return buffer;
}

std::vector<std::string> Calculator::getExpressions() {
  return this->expressions;
}

void Calculator::setTokens(std::vector<std::string> &tokens) {
  this->tokens = tokens;
}

void Calculator::clearResults() { this->results.clear(); }

void Calculator::clearExpressions() { this->expressions.clear(); }

std::map<std::string, std::string> Calculator::getVars() { return this->vars; }

std::string Calculator::getVarList() {
  std::string varList = "";
  for (auto e : this->vars) {
    varList += e.first + " = " + e.second + "\n";
  }
  return varList;
}

double Calculator::test_interface(std::string expr) {
  Calculator *calculator = new Calculator();
  std::vector<std::string> input = Calculator::splitString(expr);
  calculator->setTokens(input);
  calculator->pushVars();
  calculator->next();
  double result = calculator->handleExpression();
  delete calculator;
  return result;
}

void Calculator::testatInterface(std::istream &is, std::ostream &os) {
  std::string line = "";
  if (is.eof())
    return;
  if (std::getline(is, line) && !is.bad()) {
    if (line != "") {
      this->expressions.push_back(line);
      std::vector<std::string> input = Calculator::splitString(line);
      if (input.size() != 3) {
        printErr(os);
      } else {
        std::string result = this->calculate(input);
        if (result.front() == '-' || std::isdigit(result.front())) {
          printDigit(result, os);
        } else {
          printErr(os);
        }
      }
    }
  }
  testatInterface(is, os);
}

auto calc(int first, int second, char op) -> int {
  std::string expr = std::to_string(first) + op + std::to_string(second);
  return Calculator::test_interface(expr);
}

auto calc(std::istream &stream) -> int {
  if (!stream.fail()) {
    int opleft;
    int opright;
    char op;
    if (stream >> opleft) {
      if (stream >> op) {
        if (stream >> opright) {
          return calc(opleft, opright, op);
        }
        throw Calculator::NotAnOperatorException();
      }
      throw Calculator::NotANumberException();
    }
    throw Calculator::NotANumberException();
  } else {
    throw Calculator::StreamBadException();
  }
}
