#include "calc.hpp"
#include <cctype>
#include <string>
/*
 * standard grammar for calculator
 * exp := term | exp + term | exp - term
 * term := factor | factor * term | factor / term | factor % term
 * factor := number | ( exp )
*/

void calc::greeting() {
    std::cout << "A small calulator, various expressions allowed, operators + - / * %.\n Or enter exit to exit\n";
}

void calc::interface() {
    std::cout << "Enter an expression:\n";
    std::string line;
    std::getline(std::cin, line);
    if(line == "exit"){
        return;
    }
    std::vector<std::string> input = calc::splitString(line);
    std::cout << calc::calculate(input) << "\n";
    interface();
}

std::string calc::gui(std::string& str) {
    std::vector<std::string> input = calc::splitString(str);
    return calc::calculate(input);
}

std::string calc::testinterface(std::string str) {
    std::vector<std::string> input = calc::splitString(str);
    return calc::calculate(input);
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
        calc* calculator = new calc(input);
    try{
        std::string result = std::to_string(calculator->handleExpression());
        result.erase ( result.find_last_not_of('0') + 1, std::string::npos );
        result.erase ( result.find_last_not_of('.') + 1, std::string::npos );
        delete(calculator);
        return "Result: " + result;

    } catch(ErrorCode code){
        std::string problem = calculator->current;
        delete(calculator);
        switch(code){
            case DIVBYZERO:
                return "Division and Modulo by 0 is not allowed!";
            case NOTANOPERATOR:
                return "Expected an operator at " + problem;
            case NOTANUMBER:
                return "Expected a number at " + problem;
            case BRACKEDERROR:
                return "Open bracket not closed!";
        }
        return "Something went wrong...";
    }
  return "Something went wrong...";
}

calc::calc(std::vector<std::string>& input){
    this->tokens = input;
    this->next();
}

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
            div =  this->handleTerm();
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
