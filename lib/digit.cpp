#include "digit.hpp"
#include <iostream>
#include <string>

void printDigit(std::string& str, std::ostream& stream) {
  std::string* arr = new std::string[5];
  int i;
  for(auto e : str) {
    if(std::isdigit(e)) {
      i = std::atoi(&e);
      writeChar(arr, i); 
    } else {
      writeChar(arr,e);
    }
  }
  for(int i=0; i < 5 ; i++) {
    if(arr[i] != "") {
      stream << arr[i] << "\n";
    }
  }
}

void printDigit(int i, std::ostream& stream) {
  std::string str = std::to_string(i);
  printDigit(str, stream);  
}

void writeChar(std::string* arr, char i){
  switch(i) {
    case '.':
      arr[0] += "    ";
      arr[1] += "    ";
      arr[2] += "    ";
      arr[3] += "    ";
      arr[4] += " .  ";
      return;
    case '-':
      arr[0] += "    ";
      arr[1] += "    ";
      arr[2] += " -  ";
      arr[3] += "    ";
      arr[4] += "    ";
      return;
    default: arr[0] += i;
  }
}

void writeChar(std::string* arr,int i) {
  switch(i) {
    case 1:
      arr[0] += "    ";
      arr[1] += "  | ";
      arr[2] += "    ";
      arr[3] += "  | ";
      arr[4] += "    ";
      return;
    case 2:
      arr[0] += " -  ";
      arr[1] += "  | ";
      arr[2] += " -  ";
      arr[3] += "|   ";
      arr[4] += " -  ";
      return;
    case 3:
      arr[0] += " -  ";
      arr[1] += "  | ";
      arr[2] += " -  ";
      arr[3] += "  | ";
      arr[4] += " -  ";
      return;
    case 4:
      arr[0] += "    ";
      arr[1] += "| | ";
      arr[2] += " -  ";
      arr[3] += "  | ";
      arr[4] += "    ";
      return;
    case 5:
      arr[0] += " -  ";
      arr[1] += "|   ";
      arr[2] += " -  ";
      arr[3] += "  | ";
      arr[4] += " -  ";
      return;
    case 6:
      arr[0] += " -  ";
      arr[1] += "|   ";
      arr[2] += " -  ";
      arr[3] += "| | ";
      arr[4] += " -  ";
      return;
    case 7:
      arr[0] += " -  ";
      arr[1] += "  | ";
      arr[2] += "    ";
      arr[3] += "  | ";
      arr[4] += "    ";
      return;
    case 8:
      arr[0] += " -  ";
      arr[1] += "| | ";
      arr[2] += " -  ";
      arr[3] += "| | ";
      arr[4] += " -  ";
      return;
    case 9:
      arr[0] += " -  ";
      arr[1] += "| | ";
      arr[2] += " -  ";
      arr[3] += "  | ";
      arr[4] += " -  ";
      return;
    case 0:
      arr[0] += " -  ";
      arr[1] += "| | ";
      arr[2] += "    ";
      arr[3] += "| | ";
      arr[4] += " -  ";
      return;
    default: return;
  }

}
