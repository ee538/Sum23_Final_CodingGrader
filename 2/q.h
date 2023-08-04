
#ifndef SOL_2_Q
#define SOL_2_Q

#include <iostream>
#include <map>
#include <string>
#include <vector>

// NOTE: ONLY FOR THIS QUESTION YOU CAN USE ChatGPT if you want.
// Notice that you are only allowed to use ChatGPT and no other tool
// No other collaboration with other AI tools or humans is allowed!

// Painting problem:
// You're painting the exterior of houses in a neighborhood. Each house has a
// cost. Adjacent houses can't be painted on the same day because the paint
// needs to dry.

// Given an array costs of house painting costs, return the maximum possible
// cost while adhering to the constraint of not painting adjacent houses on the
// same day.

// Example 1:
// Input: costs = [2, 7, 9, 3, 1]
// Output: 12
// Explanation: Paint the first, third, and fifth houses for a total cost of 2 +
// 9 + 1 = 12.

// Example 2:
// Input: costs = [10, 5, 1, 20]
// Output: 30
// Explanation: Paint the first and fourth houses for a total cost of 10 + 20
// = 30.

// Example 3:
// Input: costs = [4, 1, 2, 3, 7]
// Output: 13
// Explanation: Paint the first, third, and fifth houses for a total cost of 4 +
// 2 + 7 = 13.
//-----------------------------------------------------------------------------
// Implement the following functions in q.cc
//-----------------------------------------------------------------------------
// Recursive solution.
int FindMaxTotalCost(std::vector<int>& costs);
//-----------------------------------------------------------------------------
// Memoization solution.
int FindMaxTotalCostMemo(std::vector<int>& costs);
//-----------------------------------------------------------------------------
// Memoization solution helper.
int FindMaxTotalCostMemo_Helper(std::vector<int>& costs,
                                std::vector<int>& memo);
//-----------------------------------------------------------------------------
// Tabulation solution.
int FindMaxTotalCostTabulation(std::vector<int>& costs);

//-----------------------------------------------------------------------------
// Answer the next question on Gradescope, not here!
//-----------------------------------------------------------------------------
// Given this class definition:

struct ResultTimesInMicroSeconds {
  unsigned long recursive_time_microseconds;
  unsigned long memoization_time_microseconds;
  unsigned long tabulation_time_microseconds;

  void Print() {
    std::cout << "{ " << recursive_time_microseconds << ", "
              << memoization_time_microseconds << ", "
              << tabulation_time_microseconds << " }";
  }
};

// Write a function to measure the runtime of the three implementations
// (Recursive, memoization, and tabulation).
// It takes three different input costs, and returns a vector of
// ResultTimesInMicroSeconds.
std::vector<ResultTimesInMicroSeconds> MeasureRunTimes(
    std::vector<std::vector<int>> inputs);

// // Example input :
// std::vector<std::vector<int>> inputs = {
//       {9, 8, 7, 4, 50, 6, 1, 3, 2, 4, 70, 9, 3, 2, 1},  // Size 15
//       {1, 5, 6,  7, 90, 4, 2,  1, 8, 5, 6, 7, 2,
//        3, 9, 80, 1, 4,  3, 52, 2, 7, 6, 9, 8},  // Size 25
//       {1, 5, 6, 7, 90, 4, 2, 1,  8,  5, 6, 7, 2, 3, 9, 80, 1, 4, 3, 52, 2,
//        70, 6, 9, 8, 1,  5, 6, 70, 90, 4, 2, 1, 8, 5, 6, 7,  2, 3, 9}  // Size 40
// };

// auto output = {
//     {2, 1, 2},  // Output for input 1 (recursive, memo, tabulation) in microseconds.
//     {2, 1, 2},  // Output for input 2 (recursive, memo, tabulation) in microseconds.
//     {2, 1, 2},  // Output for input 3 (recursive, memo, tabulation) in microseconds.
// }
#endif /* SOL_2_Q */
