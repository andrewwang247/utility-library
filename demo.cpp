/*
Copyright 2020. Siwei Wang.

Demo functionality.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "containment.h"
#include "enumerate.h"
#include "io.h"
#include "product.h"
#include "range.h"
#include "sequence.h"
#include "zip.h"

using std::cout;
using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

void demo_contains();
void demo_enumerate();
void demo_io();
void demo_product();
void demo_range();
void demo_sequence();
void demo_zip();

int main() {
  demo_contains();
  demo_enumerate();
  demo_io();
  demo_product();
  demo_range();
  demo_sequence();
  demo_zip();
}

void demo_contains() {
  cout << "--- CONTAINMENT DEMO ---\n";
  const vector<int> squares{1, 4, 9, 16};
  if (contains(squares, 16)) {
    cout << "16 is a perfect square.\n";
  }

  const int primes[6] = {2, 3, 5, 7, 11, 13};
  if (contains<6>(primes, 11)) {
    cout << "11 is a prime number.\n";
  }

  const unordered_map<string, int> age{{"siwei", 21}, {"grace", 16}};
  if (contains_key(age, string("siwei"))) {
    cout << "siwei is a registered name.\n";
  }

  const unordered_set<string> names{"siwei", "grace"};
  if (!contains(names, string("yolanda"))) {
    cout << "yolanda is not contained.\n";
  }
}

void demo_enumerate() {
  cout << "\n--- ENUMERATE DEMO ---\n";
  const vector<string> vec{"iterate", "over", "this", "with", "the", "index"};
  cout << "Original list:\n\t";
  for (const auto &s : vec) {
    cout << s << ' ';
  }
  cout << '\n';

  cout << "For-range loop, start at 7:\n\t";
  for (auto pr : enumerate(vec, 7)) {
    cout << pr << ' ';
  }

  cout << "\nRange of pairs, default start:\n\t";
  for (auto pr : enumerate(vec)) {
    cout << pr << ' ';
  }
  cout << '\n';
}

void demo_io() {
  cout << "\n--- IO DEMO ---\n";
  const int argc = 5;
  const char* argv[5] = {"demo", "-42", "47", "-35", "12"};
  const auto args = argparse<int>(argc, argv);
  cout << "Command line args: ";
  for (auto arg : args) cout << arg << ' ';
  cout << '\n';

  unordered_map<string, size_t> counter{{"characters", wc<char>("io.h")},
                                        {"words", wc<string>("io.h")},
                                        {"lines", wc<line>("io.h")}};
  cout << "Stats for io.h:\n";
  for (const auto& pair : counter) {
    cout << '\t' << pair << '\n';
  }
}

void demo_product() {
  cout << "\n-- PRODUCT DEMO --\n";
  const string s1 = "abc";
  const string s2 = "123";

  cout << "Iterating over cartesian product: \"abc\" x \"123\".\n\t";

  for (auto pr : product(s1, s2)) {
    cout << pr << ' ';
  }
  cout << '\n';

  cout << "Iterating over cartesian product: \"123\" x \"abc\".\n\t";
  for (auto pr : product(s2, s1)) {
    cout << pr << ' ';
  }
  cout << '\n';
}

void demo_range() {
  cout << "\n--- RANGE DEMO ---\n";
  cout << "range(10): ";
  for (auto i : range(10)) {
    cout << i << ' ';
  }
  cout << "\nrange(-7): ";
  for (auto i : range(-7)) {
    cout << i << ' ';
  }
  cout << "\nrange(-5, 4): ";
  for (auto i : range(-5, 4)) {
    cout << i << ' ';
  }
  cout << "\nrange(4, -5): ";
  for (auto i : range(4, -5)) {
    cout << i << ' ';
  }
  cout << '\n';
}

void demo_sequence() {
  cout << "\n--- SEQUENCE DEMO ---\n";
  const vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  cout << "Slicing nums 0-9 inclusive.\n";

  const auto sl1 = slice(nums, -1, 2, -2);
  cout << "\tnums[-1:2:-2]: ";
  for (auto i : sl1) {
    cout << i << ' ';
  }
  cout << '\n';

  const auto sl2 = slice(nums, 3, 8, 2);
  cout << "\tnums[3:8:2]: ";
  for (auto i : sl2) {
    cout << i << ' ';
  }
  cout << '\n';

  const string wd = "watch_dogs_2";
  cout << "Original string: " << wd << '\n';
  const auto tokens = split(wd, '_');
  cout << "After splitting on underscore: ";
  for (auto token : tokens) {
    cout << token << ' ';
  }
  auto restored = join(tokens.begin(), tokens.end(), "**");
  cout << "\nAfter rejoining with double star: " << restored << '\n';
  const string str_wd = "&*watch&*dogs&*2&*";
  const string delim = "&*";
  cout << "Splitting " << str_wd << " on &*: ";
  auto str_toks = split(str_wd, delim);
  for (auto token : str_toks) {
    cout << token << ' ';
  }
  cout << '\n';
}

void demo_zip() {
  cout << "\n--- ZIP DEMO ---\n";
  const vector<int> vec{8, 6, 7, 5, 3, 0, 9};
  const string str("yay zippers");

  cout << "Original objects:\n\t";
  for (auto obj : vec) {
    cout << obj << ' ';
  }
  cout << '\n';
  cout << '\t' << str << '\n';

  cout << "Numbers then letters:\n";
  for (auto pr : zip(vec, str)) {
    cout << '\t' << pr << ' ';
  }

  cout << "\nLetters then numbers:\n";
  const auto join = zip(str, vec);
  for (auto pr : join) {
    cout << '\t' << pr << ' ';
  }
  cout << '\n';
}
