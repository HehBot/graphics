CXX := g++
LD := g++
AR := ar

TARGET_EXEC_NAME := main

SRC_DIR := src

BIN_DIR := bin
BUILD_DIR := build

TARGET_EXEC := $(BIN_DIR)/$(TARGET_EXEC_NAME)

SRCS := $(shell find $(SRC_DIR) -name '*.cc' -or -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

CXX_FLAGS := -Wall -Wpedantic -Werror -g -O3 -fPIC -I$(SRC_DIR) -I../src -I/usr/include/freetype2 -MMD -MP
LD_FLAGS := -L../lib
LIB_FLAGS :=  -l:libgraphics.a -lglfw -lGL -lX11 -lfreetype

$(TARGET_EXEC): $(OBJS)
	@$(MAKE) -C .. static
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) -o $@ $(OBJS) $(LIB_FLAGS)

$(BUILD_DIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)
