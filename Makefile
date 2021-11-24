# Files
TARGET = floodit
SOURCEFILES = main.c game.c
SOURCEDIR = src
SOURCES = $(SOURCEFILES:%.c=$(SOURCEDIR)/%.c)
OBJECTS = $(SOURCES:%.c=%.o)
MAKEFLAGS +="-j $(shell nproc)"

# Compiler
COMPILER = cc
OPTIMIZATION = -O2
WARNINGS = -Wall -Wextra
CFLAGS = $(OPTIMIZATION) $(WARNINGS) -pipe -g

# Linker
LINKER = cc
LINKERFLAGS = -lraylib

# Targets
all: $(OBJECTS)
	@printf "$(clr_grn)Linking$(clr_gry) $(?F) -> $(TARGET)$(clr_non)\n"
	@$(LINKER) -o $(TARGET) $? $(LINKERFLAGS)

$(OBJECTS): $(SOURCES)
	@printf "$(clr_grn)Compiling$(clr_gry) $(*F).c$(clr_non)\n"
	@$(COMPILER) -c $*.c $(CFLAGS) -o $@

clean:
	@rm -f $(OBJECTS) $(TARGET)

fresh: clean
	@$(MAKE)

install:
	@echo TODO

uninstall:
	@echo TODO

.PHONY: all clean fresh install uninstall

# Colors
clr_grn = \033[0;32m
clr_gry = \033[2;37m
clr_non = \033[0;m
clr_grn_gry = \033[1;30;42m