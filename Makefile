# Makefile for the Fishing Flotilla Application

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS = -lsqlite3 -lcunit

# Coverage flags
COVERAGE_CXXFLAGS = -fprofile-arcs -ftest-coverage
COVERAGE_LDFLAGS = -lgcov

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests
DB_DIR = database
COVERAGE_DIR = coverage

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Test source files and object files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.test.o, $(TEST_SRCS))

# Executables
APP_TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/test_runner

# Database file
DB_FILE = flotilla.db

.PHONY: all clean test coverage db run

all: $(APP_TARGET)

# Main application target
$(APP_TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(COVERAGE_LDFLAGS)
	@echo "Application built successfully: $@"

# Test runner target
$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(COVERAGE_CXXFLAGS) -o $@ $^ $(LDFLAGS) $(COVERAGE_LDFLAGS)
	@echo "Test runner built successfully: $@"

# Rule for building main objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(COVERAGE_CXXFLAGS) -c $< -o $@

# Rule for building test objects
$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(COVERAGE_CXXFLAGS) -c $< -o $@

# Run the application
run: all
	./$(APP_TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Generate coverage report
coverage: test
	@mkdir -p $(COVERAGE_DIR)
	@echo "Generating coverage report..."
	@lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info --rc lcov_branch_coverage=1
	@lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '*/tests/*' --output-file $(COVERAGE_DIR)/coverage.filtered.info --rc lcov_branch_coverage=1
	@genhtml $(COVERAGE_DIR)/coverage.filtered.info --output-directory $(COVERAGE_DIR) --rc genhtml_branch_coverage=1
	@echo "Coverage report generated in $(COVERAGE_DIR)/index.html"

# Recreate the database
db:
	@echo "Recreating database..."
	@rm -f $(DB_FILE)
	@sqlite3 $(DB_FILE) < $(DB_DIR)/schema.sql
	@sqlite3 $(DB_FILE) < $(DB_DIR)/seed.sql
	@echo "Database '$(DB_FILE)' created and seeded."

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(COVERAGE_DIR) *.gcda *.gcno $(DB_FILE)
	@echo "Cleanup complete."
