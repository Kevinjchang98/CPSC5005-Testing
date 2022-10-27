CXX = g++

INCLUDE_DIR = include/

CXXFLAGS = -std=c++11 -I$(INCLUDE_DIR)

testlab3:
	$(CXX) lab3/test.cpp $(CXXFLAGS) -o lab3/test
	@echo Build complete
	@echo Running tests
	./lab3/test
