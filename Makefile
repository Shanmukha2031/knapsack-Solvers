# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++11 -Wall

# Targets and their source files
TARGETS = greedy dynpro bruteforce createkn01
SOURCES = greedy.cpp dynpro.cpp bruteforce.cpp createkn01.cpp

# Default target (build all programs)
all: $(TARGETS)

# Build individual programs
greedy: greedy.cpp
	$(CXX) $(CXXFLAGS) -o greedy greedy.cpp

dynpro: dynpro.cpp
	$(CXX) $(CXXFLAGS) -o dynpro dynpro.cpp

bruteforce: bruteforce.cpp
	$(CXX) $(CXXFLAGS) -o bruteforce bruteforce.cpp

createkn01: createkn01.cpp
	$(CXX) $(CXXFLAGS) -o createkn01 createkn01.cpp

# Clean up all compiled files
clean:
	rm -f $(TARGETS)

