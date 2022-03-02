# Edit variables here
TARGET := floodit
WARN := -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Wreturn-type -Wno-unused-result -Wformat=2 -pedantic
CFLAGS := $(WARN) -O2 -g
LDFLAGS := -lraylib
CPPFLAGS := $(INC_FLAGS) -MMD -MP
MAKEFLAGS +="-j $(shell nproc)"
BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(wildcard $(SRC_DIRS)/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(dir $(wildcard $(SRC_DIRS)/*/))
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@printf "$(clr_gry)[Linking] $(?F) -> $(TARGET)$(clr_non)\n"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(clr_gry)[Compiling] $(*F).c$(clr_non)\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@rm -r $(BUILD_DIR)

install:
	install -m 755 $(BUILD_DIR)/$(TARGET) /bin
	install -m 644 data/floodit.desktop /usr/share/applications
	install -m 644 data/floodit.png /usr/share/pixmaps/

uninstall:
	rm -f /bin/$(TARGET)
	rm -f /usr/share/applications/floodit.desktop
	rm -f /usr/share/pixmaps/floodit.png

.PHONY: clean install uninstall
-include $(DEPS)

clr_gry = \033[2;37m
clr_non = \033[0;m
