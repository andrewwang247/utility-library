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

template <typename Container>
void print_container(const Container &container);

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

template <typename Container>
void print_container(const Container &container) {
  for (const auto &item : container) {
    cout << item << ' ';
  }
  cout << '\n';
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
  print_container(vec);

  cout << "For-range loop, start at 7:\n\t";
  print_container(enumerate(vec, 7));

  cout << "Range of pairs, default start:\n\t";
  print_container(enumerate(vec));
}

void demo_io() {
  cout << "\n--- IO DEMO ---\n";
  const int argc = 5;
  const char* argv[5] = {"demo", "-42", "47", "-35", "12"};
  const auto args = argparse<int>(argc, argv);
  cout << "Command line args: ";
  print_container(args);

  unordered_map<string, size_t> counter{{"characters", wc<char>("io.h")},
                                        {"words", wc<string>("io.h")},
                                        {"lines", wc<line>("io.h")}};
  cout << "Stats for io.h:\n\t";
  print_container(counter);
}

void demo_product() {
  cout << "\n-- PRODUCT DEMO --\n";
  const string s1 = "abc";
  const string s2 = "123";

  cout << "Iterating over cartesian product: \"abc\" x \"123\".\n\t";
  print_container(product(s1, s2));

  cout << "Iterating over cartesian product: \"123\" x \"abc\".\n\t";
  print_container(product(s2, s1));
}

void demo_range() {
  cout << "\n--- RANGE DEMO ---\n";
  cout << "range(10): ";
  print_container(range(10));

  cout << "range(-7): ";
  print_container(range(-7));

  cout << "range(-5, 4): ";
  print_container(range(-5, 4));

  cout << "range(4, -5): ";
  print_container(range(4, -5));
}

void demo_sequence() {
  cout << "\n--- SEQUENCE DEMO ---\n";
  const vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  cout << "Slicing nums 0-9 inclusive.\n";

  const auto sl1 = slice(nums, -1, 2, -2);
  cout << "\tnums[-1:2:-2]: ";
  print_container(sl1);

  const auto sl2 = slice(nums, 3, 8, 2);
  cout << "\tnums[3:8:2]: ";
  print_container(sl2);

  const string wd = "watch_dogs_2";
  cout << "Original string: " << wd << '\n';
  const auto tokens = split(wd, '_');
  cout << "After splitting on underscore: ";
  print_container(tokens);

  auto restored = join(tokens.begin(), tokens.end(), "**");
  cout << "After rejoining with double star: " << restored << '\n';
  const string str_wd = "&*watch&*dogs&*2&*";
  const string delim = "&*";
  cout << "Splitting " << str_wd << " on &*: ";
  print_container(split(str_wd, delim));
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

  cout << "Numbers then letters:\n\t";
  print_container(zip(vec, str));

  cout << "Letters then numbers:\n\t";
  print_container(zip(str, vec));
}
