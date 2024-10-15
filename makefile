CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -I/usr/include/gtest
LDFLAGS = -lgtest -lgtest_main -pthread
SRC_DIR = src
OBJ_DIR = obj

# Object files
OBJS = $(OBJ_DIR)/Book.o $(OBJ_DIR)/Books.o $(OBJ_DIR)/ThreadPool.o $(OBJ_DIR)/main.o

# Targets
all: book_benchmark unit_tests

book_benchmark: $(OBJS)
	$(CXX) $(OBJS) -o $@

unit_tests: $(OBJS) $(OBJ_DIR)/test.o
	$(CXX) $(OBJS) $(OBJ_DIR)/test.o $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o $@

clean:
	rm -rf $(OBJ_DIR) book_benchmark unit_tests