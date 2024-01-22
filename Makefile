CXX := g++
CC := gcc
LD := g++
AR := ar

TARGET_EXEC_NAME := main
TARGET_LIB_NAME := graphics

SRC_DIR := src
TEST_DIR := test

LIB_DIR := lib
BIN_DIR := bin
BUILD_DIR := build

TARGET_EXEC := $(TARGET_EXEC_NAME)
TARGET_STATIC_LIB := lib$(TARGET_LIB_NAME).a
TARGET_DYNAMIC_LIB := lib$(TARGET_LIB_NAME).so

SRCS := $(shell find $(SRC_DIR) -name '*.cc' -or -name '*.c')
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cc' -or -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d) $(MAIN_OBJ:.o=.d)

CXX_FLAGS := -Wall -Wpedantic -Werror -g -fPIC -I$(SRC_DIR) -I/usr/include/freetype2 -MMD -MP
CC_FLAGS := -fPIC -I$(SRC_DIR) -MMD -MP
LD_FLAGS := -L$(LIB_DIR)
LIB_FLAGS :=  -lGL -lGLU -lglfw -lX11 -lpthread -ldl -lfreetype

$(BIN_DIR)/$(TARGET_EXEC): $(LIB_DIR)/$(TARGET_STATIC_LIB) $(TEST_OBJS)
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) -o $@ $(TEST_OBJS) -l:$(TARGET_STATIC_LIB) $(LIB_FLAGS)

$(LIB_DIR)/$(TARGET_STATIC_LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(LIB_DIR)/$(TARGET_DYNAMIC_LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^

$(BUILD_DIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CC_FLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)

-include $(DEPS)
