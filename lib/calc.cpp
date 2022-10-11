#include "calc.hpp"
#include "digit.hpp"
/*
 * standard grammar for calculator
 * exp := term | exp + term | exp - term
 * term := factor | factor * term | factor / term | factor % term
 * factor := number | ( exp )
*/

void Calculator::greeting() {
  std::cout << "A small calulator, various expressions allowed, operators + - / * %.\n Or enter exit to exit\n";
}

std::string Calculator::handle_vars(std::vector<std::string>& input) {
  if(input.front() == "add") {
    input.erase(input.begin());
    if(input.size() > 1) {
      return this->write_var(input.at(0),input.at(1));
    } else {
      return "Please enter a variable and a number to assign.\n";
    }
  } else if(input.front() == "del") {
    input.erase(input.begin());
    if(input.size() > 0) {
      return this->delete_vars(input.at(0));
    }
  }
return "";
}

void Calculator::interface(bool fancy) {
  this->interface(fancy, std::cin);
}

void Calculator::interface(bool fancy, std::istream& is) {
  std::cout << "Enter an expression:\n";
  std::string line;
  std::getline(is, line);
  if(line != "") {
    if(line == "exit"){
      return;
    }
    std::vector<std::string> input = Calculator::splitString(line);
    std::string varreturn = this->handle_vars(input);
    if(varreturn != "") {
      std::cout << varreturn ;
    } else {
      std::string result = this->calculate(input);
      if(std::isdigit(result.front())) {
        if(fancy){
          std::cout << "Result:\n";
          printDigit(result,std::cout); 
        } else {
          std::cout << "Result: " << result << "\n";
        }
      } else {
        if(fancy) {
          printErr(std::cout);
          std::cout << result << "\n";
        } else {
          std::cout << result << "\n";
        }
      }
    }
  }
  interface(fancy);
}

std::string Calculator::gui(std::string& str, bool var_edit) {
  std::vector<std::string> input = Calculator::splitString(str);
  if(var_edit) {
    return this->handle_vars(input);
  } else {
    return this->calculate(input);
  }
}

std::string Calculator::testinterface(std::string str) {
  Calculator* calculator = new Calculator();
  std::vector<std::string> input = Calculator::splitString(str);
  return calculator->calculate(input);
}

std::string Calculator::write_var(std::string& key, std::string& value) {
  std::ofstream vars;
  vars.open(this->vardir, std::ios_base::app);
  if (vars.is_open()) {
    vars << key << std::endl;
    vars << value << std::endl;
    this->read_vars();
    return "added " + key + " to variables with value " + value + "\n";
  }
  else return "Unable to open file\n";
}

std::string Calculator::delete_vars(std::string& delkey) {
  std::map<std::string , std::string>::iterator it;
  if(this->vars.find(delkey) != this->vars.end()) {
      this->vars.erase(delkey);
  } else {
    return "The variable " + delkey + " was not found in the list!\n";
  }
  
  std::ofstream vars (this->vardir);
  if (vars.is_open()) {
    for(auto e : this->vars) {
    vars << e.first << std::endl;
    vars << e.second << std::endl;
    }
  }
  else {
    return "Unable to open file";
  }
  return "deleted the variable " + delkey + "\n";
}

void Calculator::read_vars() {
  this->vars.clear();
  std::string key;
  std::string value;
  std::ifstream vars (this->vardir);
  if (vars.is_open()) {
    while(getline(vars,key)) {
    getline(vars,value);
    this->vars.insert(std::pair<std::string,std::string>(key,value));
    }
    vars.close();
  }
  else std::cout << "Unable to open file";
}

void Calculator::push_vars() {
  std::map<std::string , std::string>::iterator it;
  for(auto &e : this->tokens) {
    it = this->vars.find(e);
    if(it != this->vars.end()) {
      e = it->second;
    }
  }

}

std::vector<std::string> Calculator::splitString(std::string &input) {
  std::string buffer = "";
  std::vector<std::string> tokens;
  bool digitLock = false;
  bool charLock = false;
  bool dotLock = false;
  for(auto &e : input){
    if(std::isdigit(e) ||( e == '.' && !dotLock)){
      if(charLock) {
        charLock = false;
        tokens.push_back(buffer);
        buffer.clear();
      }
      if(e == '.') dotLock = true;
      digitLock = true;
      buffer += e;
      continue;
    } else if(digitLock){
      digitLock = false;
      tokens.push_back(buffer);
      buffer.clear();
    }
    if(Calculator::isOperator(e)){
      if(charLock) {
        charLock = false;
        tokens.push_back(buffer);
        buffer.clear();
      }
      buffer += e;
      tokens.push_back(buffer);
      buffer.clear();
    } else if(e != ' ') {
      buffer += e;
      charLock = true;
    } else if(charLock) {
      charLock = false;
      tokens.push_back(buffer);
      buffer.clear();
    }
  }
  if(buffer != ""){
    tokens.push_back(buffer);
  }
  return tokens;
}

bool Calculator::isOperator(char& op){
  switch(op){
    case '%': return true;
    case '/': return true;
    case '+': return true;
    case '-': return true;
    case '*': return true;
    case '(': return true;
    case ')': return true;
    default: return false;
  }
}

std::string Calculator::calculate(std::vector<std::string>& input) {
  this->tokens = input;
  try{
    this->push_vars();
    this->next();
    std::string result = std::to_string(this->handleExpression());
    result.erase ( result.find_last_not_of('0') + 1, std::string::npos );
    result.erase ( result.find_last_not_of('.') + 1, std::string::npos );
    return result;
  } catch(ErrorCode code){
    switch(code){
      case DIVBYZERO:
        return "Division and Modulo by 0 is not allowed!";
      case NOTANOPERATOR:
        return "Expected an operator at " + this->current;
      case NOTANUMBER:
        return "Expected a number at " + this->current;
      case BRACKEDERROR:
        return "Open bracket not closed!";
    }
    return "Something went wrong...";
  }
  return "Something went wrong...";
}

Calculator::Calculator(){}

bool Calculator::hasNext(){
  if(!this->tokens.empty()){
    return true;
  }
  return false;
}

void Calculator::next(){
  if(this->hasNext()){
    this->current = this->tokens.front();
    tokens.erase(tokens.begin());
  } else {
    this->current = "";
  }
}

double Calculator::handleExpression(){
  double result = this->handleTerm();
  if(!std::isdigit(this->current.front())){
    while(this->current != "" && this->current != ")"){
      switch(this->current.front()){
        case '+':
          this->next();
          result += this->handleTerm();
          break;
        case '-':
          this->next();
          result -= this->handleTerm();
          break;
        default:
          throw(NOTANOPERATOR);
          break;
      }
    }
  }
  return result;
}

double Calculator::handleTerm(){
  double result = this->handleFactor();
  double div = 0;
  switch(this->current.front()){
    case '*':
      this->next();
      result *= this->handleTerm();
      break;
    case '/':
      this->next();
      div =  this->handleFactor();
      if(div == 0)throw(DIVBYZERO);
      result /= div;
      if(isOperator(this->current.front())){
        this->tokens.insert(tokens.begin() , this->current);
        this->current = std::to_string(result);
        result = this->handleTerm();
      }
      break;
    case '%':
      this->next();
      div =  this->handleFactor();
      if(div == 0)throw(DIVBYZERO);
      result = (double)((int)result % (int)div);
      if(isOperator(this->current.front())){
        this->tokens.insert(tokens.begin() , this->current);
        this->current = std::to_string(result);
        result = this->handleTerm();
      }
      break;
    default:
      break;
  }
  return result;
}

double Calculator::handleFactor(){
  double result = 0;
  if(this->current == "("){
    this->next();
    result = this->handleExpression();
    if(this->current != ")"){
      throw(BRACKEDERROR);
    }
    this->next();
  } else {
    if(!std::isdigit(this->current.front())){
      throw(NOTANUMBER);
    }
    result = std::stod(this->current);
    this->next();
  }
  return result;
}

std::vector<std::string> Calculator::get_tokens() {
  return this->tokens;
}

std::map<std::string, std::string> Calculator::get_vars() {
  return this->vars;
}

int testat_interface(std::string expr) {
  Calculator* calculator = new Calculator();
  std::vector<std::string> input = Calculator::splitString(expr);
  int result = std::stoi(calculator->calculate(input));
  delete calculator;
  return result;
}

auto calc(int first, int second,char  op) -> int {
  std::string expr = std::to_string(first) + op + std::to_string(second);
  return testat_interface(expr);
}

auto calc(std::istream & stream) -> int {
  std::string expr(std::istreambuf_iterator<char>(stream), {});
  return testat_interface(expr);
}


