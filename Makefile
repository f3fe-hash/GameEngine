CC  := gcc
CXX := g++

# C Standard
CCSTANDARD := -std=c11

# C++ Standard
CXXSTANDARD := -std=c++11

# Use all warnings to spot any compile-time issue
WARNFLAGS := -Wall -Wextra -Wpedantic

# Don't use -Ofast, since it sacrifices math accuracy
OPTFLAGS := -O3 -funroll-loops

# Flags
CCFLAGS := $(WARNFLAGS) $(OPTFLAGS) $(CCSTANDARD)
CXXFLAGS := $(WARNFLAGS) $(OPTFLAGS) $(CXXSTANDARD)

# Libraries
LIBS := -lGL -lGLU -lglut

# Source files
SRC_DIR := src

# Include directory
INCLUDE_DIR := include

# Build directory
BUILD_DIR := build

# Target
TARGET_DIR := target
TARGET     := main

# Sources
C_SRCS   := $(wildcard $(SRC_DIR)/*.c)
CXX_SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
C_OBJS   := $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)
CXX_OBJS := $(CXX_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.cpp.o)
OBJS     := $(C_OBJS) $(CXX_OBJS)

# Link objects into the target
$(TARGET_DIR)/$(TARGET): $(OBJS) $(TARGET_DIR)
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Compile C sources into C objects
$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(CCFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile C++ sources into C++ objects
$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run:
	cd $(TARGET_DIR); ./$(TARGET)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET_DIR)