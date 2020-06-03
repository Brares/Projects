CXX=g++
CXXFLAGS= -std=c++0x -g -fprofile-arcs 

SRC_DIR = src


SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

PROGRAM_TEST = Test


.PHONY: all
all: $(PROGRAM_TEST) 

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_TEST) $(MEMCHECK_RESULTS) \
	$(COVERAGE_DIR) \
	html obj bin

$(PROGRAM_TEST): $(TEST_DIR) $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) \
	$(SRC_DIR)/*.cpp


test: $(PROGRAM_TEST)
	$(PROGRAM_TEST)


