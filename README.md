# Utility Template Library

A templated C++17 utility library emulating Python/Bash functionality. To get started, simply include any combination of the 4 headers: `containment.h`, `io.h`, `range.h`, and `zip.h`. We showcase elegant examples of each utility in `demo.cpp`.

## Containment

While flexible, the C++ syntax for checking containment in STL containers is a bit awkward. For set and map containers, you call the member function `find`. Otherwise, you need to use `std::find` with a range. Then you need to compare the returned iterator to the container's end iterator. In Python, this is accomplished through the `in` keyword, which works for all container types.

The `contains` and `contains_key` functions take a templated STL container and target element. Depending on the container type, they will perform the correct find procedure. There is also a `contains` overload for C-style arrays that takes the size as a template argument.

```c++
// EXAMPLE 1
std::vector<int> sequence;
std::find(sequence.begin(), sequence.end(), target) != sequence.end();
// becomes
contains(sequence, target);

// EXAMPLE 2
std::unordered_set<int> objects;
objects.find(target) != objects.end();
// becomes
contains(objects, target);

// EXAMPLE 3
std::unordered_map<int, int> relation;
relation.find(target) != relation.end();
// becomes
contains_key(relation, target);

// EXAMPLE 4
int arr[5];
std::find(arr, arr + 5, target) != arr + 5;
// becomes
contains<5>(arr, target);
```

## IO

As nice as streams are, input output in C++ seems quite archaic compared to Python. With libraries such as Click, command line arguments to a Python script are incredibly easy to parse. We provide some argument parsing capability in `argparse`, which returns a vector of templated type. The function performs the appropriate conversions from `argc` and `argv`.

The header also defines a stream insertion operator for `std::pair` types. This feeds directly into the incredibly useful `print_range` function, which takes an iterator range. The `split` and `end` parameters can be used to change the string used *between* entries as well as the string used *after* every entry. Together, they can easily print out ranges for both non-associative and associative data structures since iterators for the latter dereference into `std::pair`.

```c++
std::unordered_map<int, int> square {
    {1, 1}, {2, 4}, {3, 9}, {4, 16}
};
print_range(square.begin(), square.end());
// (1, 1) (2, 4) (3, 9) (4, 16)
std::vector<int> jenny {8, 6, 7, 5, 3, 0, 9};
print_range(jenny.begin(), jenny.end(), " - ", " :)\n");
// 8 - 6 - 7 - 5 - 3 - 0 - 9 :)
```

Last but not least, we are often interested in the character, word, and line count for a file. At the command line, this is achieved using `wc file.txt`. The library provides the following functionality.

```c++
auto character_count = wc<char>("file.txt");
auto word_count = wc<std::string>("file.txt");
auto line_count = wc<line>("file.txt");
```

Here, `line` is an empty struct used to specialize the template. More exotic template parameters can also be provided.

## Range

Three extremely useful features in Python are splitting, joining, and slicing. The first two are generally performed on strings while slicing is done on lists. The following split and join operation has a sister function in the utility library.

```python
# IN PYTHON
game = 'watch&*dogs&*2'
words = game.split(sep='&*')
# ['watch', 'dogs', '2']
new_game = '**'.join(words)
# 'watch**dogs**2'
```

```c++
// IN C++
const std::string game = "watch&*dogs&*2";
const std::string delim = "&*";
auto words = split(game, delim);
// ["watch", "dogs", "2"]
auto new_game = join(words.begin(), words.end(), "**");
// "watch**dogs**2"
```

The library provides a C++ container slicer that mirrors Python list slicing. Just as in Python, optional arguments are allowed. Furthermore, these optional arguments depend on the other arguments. Leaving the parameter blank will, by default, pass `std::nullopt`. The following programs are equivalent.

```python
# IN PYTHON
nums = range(50)
# Suppose start, stop, and step are random integers.
nums[::]                # or nums[:]
nums[start::]           # or nums[start:]
nums[:stop:]            # or nums[:stop]
nums[::step]
nums[start:stop:]       # or nums[start:stop]
nums[start::step]
nums[:stop:step]
nums[start:stop:step]
```

```c++
// IN C++
std::vector<int> nums (50);
std::iota(nums.begin(), nums.end(), 0);
// Suppose start, stop, and step are random integers.
slice(nums);
slice(nums, start);
slice(nums, std::nullopt, stop);
slice(nums, std::nullopt, std::nullopt, step);
slice(nums, std::nullopt, stop);
slice(nums, start, std::nullopt, step);
slice(nums, std::nullopt, std::nullopt, step);
slice(nums, start, stop, step);
```

## Zip

Parallel iteration in C++ requires one to:

- Take into account relative sizes of the containers.
- If iterating by index, use the smaller one's size and call `container[i]` for both.
- If iterating by iterator, keep a separate iterator for the larger container.

We lose the nice syntax of the for-range loop. In Python, this is solved by using `zip` which take several iterable objects. This library provides a templated `zip` class that solves the problems listed above. Unlike Python, it can only take a pair of containers (by reference). However, it hides the boiler-plate of getting the relative size and doing parallel iteration. The custom `zip::iterator` and  `begin` and `end` functions yields a clean for-range syntax.

```c++
std::vector<int> jenny {8, 6, 7, 5, 3, 0, 9};
std::string zippy = "zippy";
for (auto pr : zip(jenny, zippy)) {
    // pr is of type std::pair<int, char>
    std::cout << pr << ' ';
}
// (8, z) (6, i) (7, p) (5, p) (3, y)
auto parallel = zip(zippy, jenny);
print_range(parallel.begin(), parallel.end());
// (z, 8) (i, 6) (p, 7) (p, 5) (y, 3)
```
