#include "digit.hpp"
#include <iostream>
int main() {
  std::string num;
  std::cin >> num;
  printDigit(num, std::cout);
}

void printDigit(std::string& str, std::ostream& stream) {
  std::string* arr = new std::string[5];
  int i;
  for(auto e : str) {
    if(std::isdigit(e)) {
      i = std::atoi(&e);
      writeChar(arr, i); 
    }
  }
  stream << arr[0] << "\n" << arr[1] << "\n" << arr[2] << "\n" << arr[3] << "\n" << arr[4] << "\n";
}

void printDigit(int i, std::ostream& stream) {
  std::string* arr = new std::string[5];
  writeChar(arr, i);
  stream << arr[0] << "\n" << arr[1] << "\n" << arr[2] << "\n" << arr[3] << "\n" << arr[4] << "\n";
delete[](arr);
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
