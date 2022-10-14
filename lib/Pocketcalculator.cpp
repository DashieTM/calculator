#include "Pocketcalculator.hpp"

auto pocketcalculator(std::istream &in, std::ostream &out) -> void {
  Calculator *calculator = new Calculator();
  calculator->interface(true, in);
  delete calculator;
};
