#include <iostream>
#include <stdexcept>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"

template <class T>
std::string CollectionToString(T input) {
  std::string result = "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    result += std::to_string(n);
    if (count < input.size()) {
      result += ", ";
    }
  }
  result += " }";
  return result;
}
//-----------------------------------------------------------------------------
void PrintCollection(std::vector<ResultTimesInMicroSeconds> &input) {
  std::cout << "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    n.Print();
    if (count < input.size()) {
      std::cout << ", ";
    }
  }
  std::cout << " }" << std::endl;
}

// Stores the input, which consists of values, weights, capacity and the
// expected value.
struct MyInputType {
  std::vector<int> costs;

  int expected;

  // This function will be called by testing::PrintToString.
  friend void PrintTo(const MyInputType &myInput, std::ostream *os) {
    *os << myInput.DebugString();
  }

  // This function will be used by google test to print objects of this class in
  // the test output.
  std::string DebugString() const {
    std::string result;
    return result + "\ncosts: " + CollectionToString(costs) +
           ", expected: " + std::to_string(expected) + "\n";
  }
};
//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
// The input to the test. Each test case has a different value of MyInputType
std::vector<std::pair<std::string, MyInputType>> input_map = {

    {"Empty",  // Test name
     MyInputType{{}, 0}},
    {"OneHouse",  //
     MyInputType{{5}, 5}},
    {"TwoHouses",  //
     MyInputType{{5, 10}, 10}},
    {"ThreeHouses",  //
     MyInputType{{5, 10, 15}, 20}},
    {"FourHouses",  //
     MyInputType{{5, 10, 15, 20}, 30}},
    {"FiveHouses",  //
     MyInputType{{5, 10, 15, 20, 25}, 45}},
    {"FiveHouses2",  //
     MyInputType{{2, 7, 9, 3, 1}, 12}},
    {"FiveHouses3",  //
     MyInputType{{100, 7, 9, 200, 1}, 300}}

};

// The function that is passed to the tests
using MyFunctionType = std::function<int(std::vector<int> &)>;

std::vector<std::pair<std::string, MyFunctionType>> function_map = {
    //
    {"FindMaxTotalCost", FindMaxTotalCost},
    {"FindMaxTotalCostMemo", FindMaxTotalCostMemo},
    {"FindMaxTotalCostTabulation", FindMaxTotalCostTabulation}
    //
};

// This function is called by google test to print the parameter of each test
// which consists of the function and the input.
void PrintTo(const std::tuple<std::pair<std::string, MyFunctionType>,
                              std::pair<std::string, MyInputType>> &input,
             std::ostream *os) {
  *os << "Function: " << std::get<0>(input).first << "\n"
      << "Input: " << std::get<1>(input).first << ": "
      << std::get<1>(input).second.DebugString();
}

// Creating the test suite.
class FindMaxTotalCostTest
    : public testing::TestWithParam<
          std::tuple<std::pair<std::string, MyFunctionType>,
                     std::pair<std::string, MyInputType>>> {};

// Instantiating the test.
INSTANTIATE_TEST_SUITE_P(
    GraderTest, FindMaxTotalCostTest,
    // Cartesian product of various functions and inputs will be fed to the
    // test.
    testing::Combine(testing::ValuesIn(function_map),
                     testing::ValuesIn(input_map)),
    // A function that is used to print each generated test.
    [](const testing::TestParamInfo<FindMaxTotalCostTest::ParamType> &info) {
      return std::get<0>(info.param).first + "_" +
             std::get<1>(info.param).first;
    });

TEST_P(FindMaxTotalCostTest, EmptyVector) {
  auto parameter = GetParam();

  // Get the function.
  auto FindMaxTotalCostFunction = std::get<0>(parameter).second;

  // Get the input.
  auto [costs, expected] = std::get<1>(parameter).second;

  EXPECT_EQ(FindMaxTotalCostFunction(costs), expected);
}

TEST(FindMaxTotalCostRuntimeTest, test1) {
  std::vector<std::vector<int>> inputs = {

      {9, 8, 7, 4, 50, 6, 1, 3, 2, 4, 70, 9, 3, 2, 1},  // Size 15
      {1, 5, 6,  7, 90, 4, 2,  1, 8, 5, 6, 7, 2,
       3, 9, 80, 1, 4,  3, 52, 2, 7, 6, 9, 8},  // Size 25
      {1,  5, 6, 7, 90, 4, 2, 1,  8,  5, 6, 7, 2, 3, 9, 80, 1, 4, 3, 52, 2,
       70, 6, 9, 8, 1,  5, 6, 70, 90, 4, 2, 1, 8, 5, 6, 7,  2, 3, 9}  // Size 40
  };
  auto output = MeasureRunTimes(inputs);
  PrintCollection(output);
}