#include <gtest/gtest.h>
#include "Calculator.h"

// zmienne protected

struct CalculatorTestPair
{
	std::string expression;
	double solution;

	CalculatorTestPair(const std::string& str, double x): expression(str), solution(x) {}
};

struct CalculatorTest : public testing::TestWithParam<CalculatorTestPair>
{
	Calculator calc;

};

INSTANTIATE_TEST_SUITE_P(CalculatorParamTest, CalculatorTest, testing::Values(
	CalculatorTestPair{ "3+4*2/(1-5)^2", 3.5 },
	CalculatorTestPair{ "7+1*(2*3+4/5)" , 13.8},
	CalculatorTestPair{ "(1+2)*4+5-3" , 14},
	CalculatorTestPair{	"12+2*(3*4+10/5)", 40}
));

TEST_P(CalculatorTest, given_Expression_when_Evaluating_then_solutionIsCorrect)
{
	auto& param = GetParam();
	
	EXPECT_EQ(calc.solution(param.expression), param.solution);
}