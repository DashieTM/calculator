#include "Sevensegment.hpp"

auto printLargeDigit(int i, std::ostream &out) -> void { printDigit(i, out); }

auto printLargeNumber(int i, std::ostream &out) -> void { printDigit(i, out); }

auto printLargeError(std::ostream &out) -> void { printErr(out); }

void printDigit(std::string &str, std::ostream &stream) {
  std::string *arr = new std::string[5];
  for (auto e : str) {
    writeChar(arr, e);
  }
  for (int i = 0; i < 5; i++) {
    if (arr[i] != "") {
      stream << arr[i] << "\n";
    }
  }
  delete[] arr;
}

void printDigit(int i, std::ostream &stream) {
  std::string str = std::to_string(i);
  printDigit(str, stream);
}

void writeChar(std::string *arr, char i) {
  switch (i) {
  case '1':
    arr[0] += "    ";
    arr[1] += "  | ";
    arr[2] += "    ";
    arr[3] += "  | ";
    arr[4] += "    ";
    return;
  case '2':
    arr[0] += " -  ";
    arr[1] += "  | ";
    arr[2] += " -  ";
    arr[3] += "|   ";
    arr[4] += " -  ";
    return;
  case '3':
    arr[0] += " -  ";
    arr[1] += "  | ";
    arr[2] += " -  ";
    arr[3] += "  | ";
    arr[4] += " -  ";
    return;
  case '4':
    arr[0] += "    ";
    arr[1] += "| | ";
    arr[2] += " -  ";
    arr[3] += "  | ";
    arr[4] += "    ";
    return;
  case '5':
    arr[0] += " -  ";
    arr[1] += "|   ";
    arr[2] += " -  ";
    arr[3] += "  | ";
    arr[4] += " -  ";
    return;
  case '6':
    arr[0] += " -  ";
    arr[1] += "|   ";
    arr[2] += " -  ";
    arr[3] += "| | ";
    arr[4] += " -  ";
    return;
  case '7':
    arr[0] += " -  ";
    arr[1] += "  | ";
    arr[2] += "    ";
    arr[3] += "  | ";
    arr[4] += "    ";
    return;
  case '8':
    arr[0] += " -  ";
    arr[1] += "| | ";
    arr[2] += " -  ";
    arr[3] += "| | ";
    arr[4] += " -  ";
    return;
  case '9':
    arr[0] += " -  ";
    arr[1] += "| | ";
    arr[2] += " -  ";
    arr[3] += "  | ";
    arr[4] += " -  ";
    return;
  case '0':
    arr[0] += " -  ";
    arr[1] += "| | ";
    arr[2] += "    ";
    arr[3] += "| | ";
    arr[4] += " -  ";
    return;
  case '.':
    arr[0] += "    ";
    arr[1] += "    ";
    arr[2] += "    ";
    arr[3] += "    ";
    arr[4] += " .  ";
    return;
  case '-':
    arr[0] += "    ";
    arr[1] += " __ ";
    arr[2] += "    ";
    arr[3] += "    ";
    arr[4] += "    ";
    return;
  default:
    return;
  }
}

void printErr(std::ostream &stream) {
  std::string *arr = new std::string[5];
  arr[0] = " -             ";
  arr[1] = "|              ";
  arr[2] = " -  -  -  -   -";
  arr[3] = "|  |  |  | | | ";
  arr[4] = " -        -    ";
  for (int i = 0; i < 5; i++) {
    if (arr[i] != "") {
      stream << arr[i] << "\n";
    }
  }
  delete[] arr;
}
