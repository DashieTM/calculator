#include "Pocketcalculator.hpp"

auto pocketcalculator(std::istream &in, std::ostream &out) -> void {
  if (!in.fail()) {
    Calculator *calculator = new Calculator();
    calculator->testatInterface(in, out);
    delete calculator;
  } else {
    throw Calculator::StreamBadException();
  }
};
