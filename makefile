CXXFLAGS=-Wall -std=c++11

test1: test1.o
	$(CXX) -o $@ $^
test2: test2.o
	$(CXX) -o $@ $^
test3: test3.o
	$(CXX) -o $@ $^
test4: test4.o
	$(CXX) -o $@ $^
testGoal: testGoal.o
	$(CXX) -o $@ $^
clear:
	rm *.o *.exe
