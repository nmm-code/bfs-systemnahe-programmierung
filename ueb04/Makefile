# ---------------------------------------------	#
# Fachhochschule Wedel                          #
# Makefile SP-Uebung 04                         #
# mhe, mre, tti                                 #
# ---------------------------------------------	#

# Source codes
SOURCES		= error.c word.c occlist.c wordlist.c indexer.c ueb04.c

# Object files
OBJECTS		= $(SOURCES:.c=.o)

# Target name
BINARY		= ueb04

# Compiler
CC			= gcc
# Doc generator
DOC			= doxygen

# Include directories
INCLUDES	=

# Linker flags
LDFLAGS		=

# Compiler flags
CFLAGS_BASE	= -g -std=c99 -pedantic -Wall -Wextra -Wvla
CFLAGS_VARS	=
ifeq ($(FORCE),true)
CFLAGS		= $(CFLAGS_BASE) $(CFLAGS_VARS)
else
CFLAGS		= $(CFLAGS_BASE) -Werror $(CFLAGS_VARS)
endif

# Flag that states that warnings will not lead to compilation errors
FORCE = false

.PHONY: default all force clean doc help

default: all

all: $(BINARY)

force:
	@make FORCE=true


# Compile a single file with header file
%.o : %.c %.h
	@echo "  Building $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	@echo "  ... done"

# Compile a single file without header file
%.o : %.c
	@echo "  Building $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	@echo "  ... done"

# Link files to an executable
$(BINARY): $(OBJECTS)
	@echo "  - linking $@"
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)
	@echo "  ... done"

# Clean the project
clean:
	@echo "  - deleting all generated files"
	rm -f $(OBJECTS) $(BINARY) *~ doxygen.log
	rm -rf doc/
	@echo "  ... done"

# Create html-documentation
doc:
	@echo "  - creating documentation"
	$(DOC)
	@echo "  ... done"

# Show help
help:
	@echo "Options:"
	@echo "make all      - create program"
	@echo "make clean    - clean up"
	@echo "make doc      - create documentation"
	@echo "make force    - compile without -Werror (just for 'comfier' development)"
