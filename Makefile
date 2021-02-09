#  This is a modified version of Job Vranish's Makefile
#  (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC ?= breakout
TARGET_TEST ?= test_breakout

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
TEST_DIRS ?= ./test
MAINS ?= $(SRC_DIRS)/main.cpp
EXT ?= cpp

# Find all the C++ files we want to compile
SRCS := $(wildcard $(SRC_DIRS)/*.$(EXT))
TESTS := $(filter-out $(MAINS),$(SRCS)) $(wildcard $(TEST_DIRS)/*.$(EXT))

# String substitution for every C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
TOBJS := $(TESTS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d) $(TOBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_FLAGS := $(wildcard */)

# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
LDFLAGS  ?= -lX11 -lGL -lpthread -lpng -lstdc++fs
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CXXFLAGS ?= -std=c++17
WARNINGS ?= -g -Wall -Wextra -Werror -pedantic-errors \
			-Wwrite-strings -Wno-parentheses -Warray-bounds

all: $(BUILD_DIR)/$(TARGET_EXEC)

test: $(BUILD_DIR)/$(TARGET_TEST)

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(WARNINGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Compile tests
$(BUILD_DIR)/$(TARGET_TEST): $(TOBJS)
	$(CXX) $(TOBJS) -o $@ $(LDFLAGS)

$TOBJS: TESTS
	$(MKDIR_P) $(dir $@)
	$(CXX) $(WARNINGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all test clean

clean:
	$(RM) -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)

MKDIR_P ?= mkdir -p
