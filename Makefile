CXX := g++
CC := gcc
LD := g++
AR := ar

TARGET_LIB_NAME := graphics

SRC_DIR := src

LIB_DIR := lib
BUILD_DIR := build

TARGET_STATIC_LIB := lib$(TARGET_LIB_NAME).a
TARGET_SHARED_LIB := lib$(TARGET_LIB_NAME).so

SRCS := $(shell find $(SRC_DIR) -name '*.cc' -or -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

CXX_FLAGS := -Wall -Wpedantic -Werror -g -O3 -fPIC -I$(SRC_DIR) -I/usr/include/freetype2 -MMD -MP
CC_FLAGS := -O3 -fPIC -I$(SRC_DIR) -MMD -MP
LD_FLAGS := -L$(LIB_DIR)
LIB_FLAGS :=  -lglfw -lGL -lX11 -lfreetype

all: static shared

static: $(LIB_DIR)/$(TARGET_STATIC_LIB)

shared: $(LIB_DIR)/$(TARGET_SHARED_LIB)

$(LIB_DIR)/$(TARGET_STATIC_LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(LIB_DIR)/$(TARGET_SHARED_LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^

$(BUILD_DIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CC_FLAGS) -o $@ $<

.PHONY: all static shared clean
clean:
	$(RM) -r $(BUILD_DIR) $(LIB_DIR)

-include $(DEPS)
