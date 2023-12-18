# ----------------------------------------------- #
# Fachhochschule Wedel                            #
# SP-Uebung 01 - printf/scanf                     #
# Malte Heins / Melanie Reißmann / Torben Tietgen #
#                                                 #
# Makefile                                        #
# ----------------------------------------------- #

# Flag that states that warnings will not lead to compilation errors
FORCE = false

# Compiler
CC		= gcc
# Doc generator
DOC		= doxygen

# Include directories
INCLUDES	 =
# Compiler flags
CFLAGS_FORCE = -c -g -std=c99 -pedantic -Wall -Wextra
CFLAGS		 = $(CFLAGS_FORCE) -Werror
# Linker flags
LDFLAGS		 =

# Source codes
SOURCE		= ueb01.c
OBJECTS		= $(SOURCE:.c=.o)

# Target name
BINARY		= ueb01

.PHONY: all help clean doc doc

default: all

force: 
	@make FORCE=true

all: $(BINARY)

# Compile a single file
%.o : %.c
	@echo "  - Building $@"
ifeq ($(FORCE),true)
	$(CC) $(CFLAGS_FORCE) $(INCLUDES) -o $@ $<
else
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
endif
	@echo "  ... done"

# Link files to an executable
$(BINARY): $(OBJECTS)
	@echo "  - linking $@"
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)
	@echo "  ... done"

# Clean the project
clean:
	@echo "  - delete object all files"
	rm -f $(OBJECTS) $(BINARY) *~ doxygen.log
	rm -rf doc/
	@echo "  ... done"

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
