TARGET   := tree-traversal

SRCDIR   := src
OBJDIR   := obj

CC       := gcc
CFLAGS   := -Wall -Wextra -O2 -I./$(SRCDIR)

LINKER   := gcc
LFLAGS   := -Wall -Wextra -std=c99 -Wno-missing-braces

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*
