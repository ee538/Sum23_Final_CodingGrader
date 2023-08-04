#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"
using ::testing::ElementsAre;

//-----------------------------------------------------------------------------
// Helper functions.
//-----------------------------------------------------------------------------
// Number of distinct strings with max size k can we create with n distinct
// characters? Strings can have duplicate characters. Write a formula
// n^1 + n^2 + n^3 + ... + n^k
// Sum = (n^(k+1) - 1) / (n - 1)-1
unsigned long GetNumberOfNodesInTree(int k, int n) {
  return (std::pow(n, (k + 1)) - 1) / (n - 1) - 1;
}

// A function to print PasswordFormat.
// This is used in grader test to print this struct.
// Sample usage:
// PasswordFormat format;
// std::cout << format;
std::ostream& operator<<(std::ostream& os,
                         const PasswordFormat& password_format) {
  os << "Allowed characters: " << password_format.allowed_characters
     << std::endl;
  os << "Max consecutive digits: " << password_format.max_consecutive_digits
     << std::endl;
  os << "Max consecutive same case: "
     << password_format.max_consecutive_same_case << std::endl;
  os << "Max length: " << password_format.max_length << std::endl;
  os << "Can start with a digit: "
     << (password_format.can_start_with_digit ? "Yes" : "No") << std::endl;
  return os;
}

//-----------------------------------------------------------------------------
TEST(PasswordFormatTest, FindValidPasswords_ReturnsValidPasswords) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ -1,
      /* max_consecutive_same_case */ 3,
      /* max_consecutive_duplicates */ -1,
      /* max_length */ 4,
      /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"123", "jho"};
  BlackBox black_box(valid_passwords);
  std::cout << "password_format: " << password_format << std::endl;

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("123", "jho"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 15'000'000);
}

TEST(PasswordFormatTest, FindValidPasswords_MaxConsecutiveDigits2) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ 2,
      /* max_consecutive_same_case */ 1,
      /* max_consecutive_duplicates */ -1,
      /* max_length */ 4,
      /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"222", "22a"};
  BlackBox black_box(valid_passwords);
  std::cout << "password_format: " << password_format << std::endl;

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("22a"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 7'000'000);
}

TEST(PasswordFormatTest, FindValidPasswords_MaxConsecutiveDuplicates) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ -1,
      /* max_consecutive_same_case */ -1,
      /* max_consecutive_duplicates */ 2,
      /* max_length */ 4,
      /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"222", "22a"};
  BlackBox black_box(valid_passwords);
  std::cout << "password_format: " << password_format << std::endl;

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("22a"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 15'015'882);
}

TEST(PasswordFormatTest, FindValidPasswords_MaxConsecutiveSameCase) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ 1,
      /* max_consecutive_same_case */ 1,
      /* max_consecutive_duplicates */ 1,
      /* max_length */ 4,
      /* can_start_with_digit */ false};

  std::set<std::string> valid_passwords = {"222", "123", "aabb", "zZyY"};
  BlackBox black_box(valid_passwords);
  std::cout << "password_format: " << password_format << std::endl;

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("zZyY"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 5'000'000);
}

TEST(PasswordFormatTest, FindValidPasswords_CanStartWithDigit) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ -1,
      /* max_consecutive_same_case */ -1,
      /* max_consecutive_duplicates */ -1,
      /* max_length */ 4,
      /* can_start_with_digit */ false};

  std::set<std::string> valid_passwords = {"222", "22a", "his", "hi2"};
  BlackBox black_box(valid_passwords);
  std::cout << "password_format: " << password_format << std::endl;

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("hi2", "his"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 13'000'000);
}

TEST(PasswordFormatTest, FindValidPasswords_MaxLength) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{
      /* allowed_characters */
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      /* max_consecutive_digits */ -1,
      /* max_consecutive_same_case */ -1,
      /* max_consecutive_duplicates */ -1,
      /* max_length */ 3,
      /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"12345", "pqz", "ffhis", "asdflkj"};
  BlackBox black_box(valid_passwords);

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("pqz"));
  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 245'000);
}

TEST(PasswordFormatTest, FindValidPasswords_MaxLength2) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{/* allowed_characters */
                                 "abc012ABC",
                                 /* max_consecutive_digits */ 1,
                                 /* max_consecutive_same_case */ -1,
                                 /* max_consecutive_duplicates */ -1,
                                 /* max_length */ 3,
                                 /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"12345", "aAC", "ffhis", "asdflkj"};
  BlackBox black_box(valid_passwords);

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("aAC"));

  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 750);
}

TEST(PasswordFormatTest, FindValidPasswords_SubsetPasswords) {
  // Use uniform initialization for PasswordFormat
  PasswordFormat password_format{/* allowed_characters */
                                 "abc012ABC",
                                 /* max_consecutive_digits */ 1,
                                 /* max_consecutive_same_case */ -1,
                                 /* max_consecutive_duplicates */ -1,
                                 /* max_length */ 4,
                                 /* can_start_with_digit */ true};

  std::set<std::string> valid_passwords = {"ab1", "aAC", "aAC1", "ab1A", "11d"};
  BlackBox black_box(valid_passwords);

  // Call the function
  std::set<std::string> result = FindValidPasswords(password_format, black_box);

  // Check the result contains the valid passwords
  EXPECT_THAT(result, ElementsAre("aAC", "aAC1", "ab1", "ab1A"));

  std::cout << "Your number of password tries " << black_box.number_of_tries_
            << std::endl;
  auto max_number_of_tries_upper_bound = GetNumberOfNodesInTree(
      password_format.max_length, password_format.allowed_characters.size());
  std::cout << "Max number of tries without backtracking: "
            << max_number_of_tries_upper_bound << std::endl;
  EXPECT_LE(black_box.number_of_tries_, 6'900);
}