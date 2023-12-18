# ---------------------------------------------	#
# Fachhochschule Wedel                          #
# Makefile SP-Uebung 03                         #
# aan, avh, mhe, mre, tti                       #
# ---------------------------------------------	#

# Source files
SOURCES	= base64.c error.c ueb03.c

# Object files
OBJECTS	= $(SOURCES:.c=.o)

# Target file
BINARY	= ueb03

# Compiler
CC			= gcc

# Doc generator
DOC			= doxygen

# Included directories
INCLUDES		=

# Linker flags
LDFLAGS			=

# Compiler flags
CFLAGS_BASE	= -g -std=c99 -pedantic -Wall -Wextra -Wvla
CFLAGS_VARS	= 
ifeq ($(FORCE),true)
CFLAGS			= $(CFLAGS_BASE) $(CFLAGS_VARS)
else
CFLAGS			= $(CFLAGS_BASE) -Werror $(CFLAGS_VARS)
endif

# Flag that states that warnings will not lead to compilation errors
FORCE	= false

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
	@echo "  Linking $@"
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)
	@echo "  ... done"

# Clean the project
clean:
	@echo "  Deleting all generated files"
	rm -f $(OBJECTS) $(BINARY) *~ doxygen.log
	rm -rf doc/
	@echo "  ... done"

# Create html documentation
doc:
	@echo "  Creating documentation"
	$(DOC)
	@echo "  ... done"

# Show help
help:
	@echo "Options:"
	@echo "make all      - create program"
	@echo "make clean    - clean up"
	@echo "make doc      - create documentation"
	@echo "make force    - compile without -Werror (just for 'comfier' development)"
