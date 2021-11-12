SRC := src
INCLUDE := include
CXXFLAGS := -std=gnu++20 -O3 -Wall -Wpedantic -Wno-narrowing
CXX = g++

all:
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) ${SRC}/*.cc -o build/a.out
