# Compiler and flags.
CXX := g++ -std=c++17
FLAGS := -Wall -Werror -Wextra -Wconversion -pedantic -Wfloat-equal -Wduplicated-branches -Wduplicated-cond -Wshadow
OPT := -Ofast -DNDEBUG

# Executable name.
EXE := demo

# Build optimized executable.
release : $(EXE).cpp
	$(CXX) $(FLAGS) $(OPT) -c $(EXE).cpp
	$(CXX) $(FLAGS) $(OPT) -o $(EXE) $(EXE).o

# Remove executable binary and generated objected files.
.PHONY : clean
clean : 
	rm -f $(EXE) $(EXE).o
