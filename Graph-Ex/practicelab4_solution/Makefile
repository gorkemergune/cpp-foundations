CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET   = lab4
TESTER   = lab4_tests

# Question to test: make test Q=1 (default: all)
Q ?= all

.PHONY: all run test clean

all: $(TARGET)

# Rebuilds only if a source file changed, then starts the menu
run: $(TARGET)
	@./$(TARGET)

# Rebuilds only if a source file changed, then runs the tests
test: $(TESTER)
	@./$(TESTER) $(Q) || true

$(TARGET): main.o Graph.o Student.o
	$(CXX) $(CXXFLAGS) -o $@ main.o Graph.o Student.o

$(TESTER): tests.o Graph.o Student.o
	$(CXX) $(CXXFLAGS) -o $@ tests.o Graph.o Student.o

main.o: main.cpp Graph.h Student.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp main.cpp Graph.h Student.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

Graph.o: Graph.cpp Graph.h Student.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Student.o: Student.cpp Student.h
	$(CXX) $(CXXFLAGS) -c Student.cpp

clean:
	rm -f *.o $(TARGET) $(TESTER) $(TARGET).exe $(TESTER).exe
