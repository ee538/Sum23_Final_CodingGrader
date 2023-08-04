#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

/**
 * In this question you are implementing a function to crack passwords by
 * checking all possible combinations that conform to the given password format.
 * Note that you should use backtracking so that your implementation is better
 * than brute force.
 *
 * Notes:
 * 1. The grader test time outs after sometime if your program takes too long to
 * finish. Make sure you optimize your algorithm to finish within the given
 * time.
 * 2. The grader test limits the number of times that you can
 * check your password guess using the given blackbox. Make sure you optimize
 * your algorithm such that you don't exceed the given number.
 */
//-----------------------------------------------------------------------------
// DO NOT TOUCH OR THIS CLASS. YOU WILL ONLY USE IT IN YOUR IMPLEMENTATION.
// Note for grader: this class definition should remain untouched.
//-----------------------------------------------------------------------------
class BlackBox {
 public:
  BlackBox(const std::set<std::string>& valid_passwords)
      : number_of_tries_(0), valid_passwords_(valid_passwords) {}

  // Given an input password, check if it is correct.
  bool TryPassword(const std::string& password) {
    number_of_tries_++;

    if (std::find(valid_passwords_.begin(), valid_passwords_.end(), password) !=
        valid_passwords_.end()) {
      return true;
    } else {
      return false;
    }
  }

  // Counts how many times the TryPassword was called.
  unsigned long number_of_tries_;

 private:
  // Collection of valid passwords. The test file should initialize this using
  // the constructor.
  std::set<std::string> valid_passwords_;
};
//-----------------------------------------------------------------------------
// DO NOT TOUCH OR THIS CLASS. YOU WILL ONLY USE IT IN YOUR IMPLEMENTATION.
//-----------------------------------------------------------------------------
// A struct that stores the password format. Your implementation should use
// this.
struct PasswordFormat {
  // What characters can appear in the password? Example:
  // "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  std::string allowed_characters;
  // Maximum number of consecutive digits.
  // Set to -1 for no limit.
  int max_consecutive_digits;
  // Max number of characters that are next to each other and have the same
  // case. Example: 'aaBB111' has two consecutive characters 'aa' that are lower
  // case, 'BB' that are upper case, and '111' that are no lower or upper case.
  // Set to -1 for no limit.
  int max_consecutive_same_case;
  // Max number of characters that are next to each other and are equal.
  // Example: 'aad' has two such characters.
  // Set to -1 for no limit.
  int max_consecutive_duplicates;
  // Max length of the password.
  int max_length;
  // Whether the password can start with a digit.
  bool can_start_with_digit;
};
//-----------------------------------------------------------------------------
// TODO: Implement this function in q.cc.
//-----------------------------------------------------------------------------
// Implement this function using backtracking.
// Given a password format and a blackbox, returns all valid passwords that
// conform to password_format. It tries the `candidate_password` by calling
// `black_box.TryPassword(candidate_password)` function.
std::set<std::string> FindValidPasswords(PasswordFormat& password_format,
                                         BlackBox& black_box);

//-----------------------------------------------------------------------------
// Sample Grader Test:
//-----------------------------------------------------------------------------
// TEST(PasswordFormatTest, FindValidPasswords_SubsetPasswords) {
//   // Use uniform initialization for PasswordFormat
//   PasswordFormat password_format{/* allowed_characters */
//                                  "abc012ABC",
//                                  /* max_consecutive_digits */ 1,
//                                  /* max_consecutive_same_case */ -1,
//                                  /* max_consecutive_duplicates */ -1,
//                                  /* max_length */ 4,
//                                  /* can_start_with_digit */ true};

//   std::set<std::string> valid_passwords = {"ab1", "aAC", "aAC1", "ab1A", "11d"};
//   BlackBox black_box(valid_passwords);

//   // Call the function
//   std::set<std::string> result = FindValidPasswords(password_format, black_box);

//   // Check the result contains the valid passwords
//   EXPECT_THAT(result, ElementsAre("aAC", "aAC1", "ab1", "ab1A"));

//   std::cout << "Your number of password tries " << black_box.number_of_tries_
//             << std::endl;
//   EXPECT_LE(black_box.number_of_tries_, 6'900);
// }