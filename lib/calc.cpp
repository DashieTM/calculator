#include "calc.hpp"
#include "digit.hpp"
/*
 * standard grammar for calculator
 * exp := term | exp + term | exp - term
 * term := factor | factor * term | factor / term | factor % term
 * factor := number | ( exp )
*/

void calc::greeting() {
    std::cout << "A small calulator, various expressions allowed, operators + - / * %.\n Or enter exit to exit\n";
}

void calc::interface(bool fancy) {
    std::cout << "Enter an expression:\n";
    std::string line;
    std::getline(std::cin, line);
    if(line == "exit"){
        return;
    } 
    if(line != "") {
    std::vector<std::string> input = calc::splitString(line);
      if(input.front() == "add") {
          input.erase(input.begin());
          if(input.size() > 1) {
              calc::write_var(input.at(0),input.at(1));
          } else {
              std::cout << "Please enter a variable and a number to assign.\n";
          }
      } else if(input.front() == "del") {
          input.erase(input.begin());
          if(input.size() > 0) {
              this->delete_vars(input.at(0));
          }
      }else {
        if(fancy){
          std::string result = this->calculate(input);
          std::cout << "Result:\n";
          printDigit(result,std::cout); 
        } else {
          std::cout << "Result: " << this->calculate(input) << "\n";
        }
      }
    }
    interface(fancy);
}

std::string calc::gui(std::string& str) {
    std::vector<std::string> input = calc::splitString(str);
    return this->calculate(input);
}

std::string calc::testinterface(std::string str) {
    calc* calculator = new calc();
    std::vector<std::string> input = calc::splitString(str);
    return calculator->calculate(input);
}

void calc::write_var(std::string& key, std::string& value) {
  std::ofstream vars;
  vars.open(this->vardir, std::ios_base::app);
  if (vars.is_open()) {
    vars << key << std::endl;
    vars << value << std::endl;
    std::cout << "added " << key << " to variables with value " << value << std::endl;
  }
  else std::cout << "Unable to open file";
  this->read_vars();
}

void calc::delete_vars(std::string& delkey) {
  std::map<std::string , std::string>::iterator it;
  if(this->vars.find(delkey) != this->vars.end()) {
      this->vars.erase(delkey);
  } else {
      std::cout << "The variable " << delkey << " was not found in the list!\n";
      return;
  }
  
  std::ofstream vars (this->vardir);
  if (vars.is_open()) {
    for(auto e : this->vars) {
    vars << e.first << std::endl;
    vars << e.second << std::endl;
    }
  }
  else {
      std::cout << "Unable to open file";
      return;
  }
  std::cout << "deleted the variable " << delkey << std::endl;
}

void calc::read_vars() {
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

void calc::push_vars() {
  std::map<std::string , std::string>::iterator it;
  for(auto &e : this->tokens) {
      it = this->vars.find(e);
      if(it != this->vars.end()) {
          e = it->second;
      }
  }

}

std::vector<std::string> calc::splitString(std::string &input) {
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
        if(calc::isOperator(e)){
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

bool calc::isOperator(char& op){
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

std::string calc::calculate(std::vector<std::string>& input) {
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

calc::calc(){}

bool calc::hasNext(){
    if(!this->tokens.empty()){
        return true;
    }
    return false;
}

void calc::next(){
    if(this->hasNext()){
        this->current = this->tokens.front();
        tokens.erase(tokens.begin());
    } else {
        this->current = "";
    }
}

double calc::handleExpression(){
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

double calc::handleTerm(){
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

double calc::handleFactor(){
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
