#include "Calc.hpp"

#include <cute/cute.h>
#include <cute/cute_equals.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <exception>
#include <system_error>

TEST(simplePlus) {
  std::string result = Calculator::testinterface("5+3");
  ASSERT_EQUAL("Result: 8" , result);
  result = Calculator::testinterface("5+3.5");
  ASSERT_EQUAL("Result: 8.5" , result);
  result = Calculator::testinterface("235+2423");
  ASSERT_EQUAL("Result: 2658" , result);
}
TEST(simpleMinus) {
  std::string result = Calculator::testinterface("99-20");
  ASSERT_EQUAL("Result: 79" , result);
  result = Calculator::testinterface("1-20");
  ASSERT_EQUAL("Result: -19" , result);
  result = Calculator::testinterface("2341-343");
  ASSERT_EQUAL("Result: 1998" , result);
}
TEST(simpleMultiply) {
  std::string result = Calculator::testinterface("7*4");
  ASSERT_EQUAL("Result: 28" , result);
  result = Calculator::testinterface("2*3.3");
  ASSERT_EQUAL("Result: 6.6" , result);
  result = Calculator::testinterface("200*231");
  ASSERT_EQUAL("Result: 46200" , result);
}
TEST(simpleDivision) {
  std::string result = Calculator::testinterface("44/4");
  ASSERT_EQUAL("Result: 11" , result);
  result = Calculator::testinterface("5/2");
  ASSERT_EQUAL("Result: 2.5" , result);
  result = Calculator::testinterface("5/99");
  ASSERT_EQUAL("Result: 0.050505" , result);
}
TEST(longExpression) {
  std::string result = Calculator::testinterface("5 + 3 * 8 / 2 + ( 5 - 2 )");
  ASSERT_EQUAL("Result: 20" , result);
  result = Calculator::testinterface("5 * (3 / 8) + 2 + ( 5 - 2 )");
  ASSERT_EQUAL("Result: 6.875" , result);
  result = Calculator::testinterface("(5 + 3) * 8 / 2 + 5 - 2 ");
  ASSERT_EQUAL("Result: 35" , result);
}

TEST(randomStrings) {
  //std::string result = Calculator::testinterface("999999999999999999999999 + 1");
  //ASSERT_EQUAL("Result: 20" , result);
  //std::string result = Calculator::testinterface("not a calculation");
  //ASSERT_THROWS(Calculator::testinterface , NOTANOPERATOR);
  //result = Calculator::testinterface("5 g 5");
  //ASSERT_EQUAL("Result: 20" , result);
}


auto createCalcSuite() -> cute::suite {
  cute::suite calcSuite{};

  calcSuite += simplePlus;
  calcSuite += simpleMinus;
  calcSuite += simpleMultiply;
  calcSuite += simpleDivision;
  calcSuite += longExpression;
  calcSuite += randomStrings;

  return calcSuite;
}

auto main(int argc, char const* argv[]) -> int {
  cute::ide_listener<> listener{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto calcSuite = createCalcSuite();

  bool suiteResult = runner(calcSuite, "Calc Suite");

  return suiteResult ? EXIT_SUCCESS : EXIT_FAILURE;
}
