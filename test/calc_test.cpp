#include "Calc.hpp"
#include "cute/cute_throws.h"

#include <cute/cute.h>
#include <cute/cute_equals.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <exception>
#include <system_error>

TEST(simplePlus) {
  double result = Calculator::test_interface("5+3");
  ASSERT_EQUAL(8, result);
  result = Calculator::test_interface("5+3.5");
  ASSERT_EQUAL(8.5, result);
  result = Calculator::test_interface("235+2423");
  ASSERT_EQUAL(2658, result);
  result = Calculator::test_interface("5+-10");
  ASSERT_EQUAL(-5, result);
}
TEST(simpleMinus) {
  double result = Calculator::test_interface("99-20");
  ASSERT_EQUAL(79, result);
  result = Calculator::test_interface("1-20");
  ASSERT_EQUAL(-19, result);
  result = Calculator::test_interface("2341-343");
  ASSERT_EQUAL(1998, result);
  result = Calculator::test_interface("-5--5");
  ASSERT_EQUAL(0, result);
}
TEST(simpleMultiply) {
  double result = Calculator::test_interface("7*4");
  ASSERT_EQUAL(28, result);
  result = Calculator::test_interface("2*3.3");
  ASSERT_EQUAL(6.6, result);
  result = Calculator::test_interface("200*231");
  ASSERT_EQUAL(46200, result);
  result = Calculator::test_interface("2 * -4");
  ASSERT_EQUAL(-8, result);
}
TEST(simpleDivision) {
  double result = Calculator::test_interface("44/4");
  ASSERT_EQUAL(11, result);
  result = Calculator::test_interface("5/2");
  ASSERT_EQUAL(2.5, result);
  result = Calculator::test_interface("5%2");
  ASSERT_EQUAL(1, result);
  result = Calculator::test_interface("5/99");
  result = result - 0.0505051;
  ASSERT_EQUAL(true, result < 0.0000);
  ASSERT_THROWS(Calculator::test_interface("1/0"), Calculator::ZeroDivisionException);
  ASSERT_THROWS(Calculator::test_interface("1%0"), Calculator::ZeroDivisionException);
}
TEST(longExpression) {
  double result = Calculator::test_interface("5 + 3 * 8 / 2 + ( 5 - 2 )");
  ASSERT_EQUAL(20, result);
  result = Calculator::test_interface("5 * (3 / 8) + 2 + ( 5 - 2 )");
  ASSERT_EQUAL(6.875, result);
  result = Calculator::test_interface("(5 + 3) * 8 / 2 + 5 - 2 ");
  ASSERT_EQUAL(35, result);
}

TEST(randomStrings) {
  ASSERT_THROWS(Calculator::test_interface("not a calculation") , Calculator::NotANumberException);
  ASSERT_THROWS(Calculator::test_interface("5 f 5"), Calculator::NotAnOperatorException);
  ASSERT_THROWS(Calculator::test_interface("( 5 + 5"), Calculator::BrackedException);
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

auto main(int argc, char const *argv[]) -> int {
  cute::ide_listener<> listener{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto calcSuite = createCalcSuite();

  bool suiteResult = runner(calcSuite, "Calc Suite");

  return suiteResult ? EXIT_SUCCESS : EXIT_FAILURE;
}
