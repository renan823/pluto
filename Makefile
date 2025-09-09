CC = gcc
CFLAGS = -Wall -Iinclude -std=c2x
OBJDIR = build
SRCDIR = src
TESTDIR = tests

TARGET = pluto

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

TEST_SOURCES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJS := $(patsubst $(TESTDIR)/%.c, test_%, $(TEST_SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET) *.dat

run:
	./$(TARGET)

.PHONY: all clean


# Tests logic (compile all and exeute)
tests.o: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(SRCDIR)/tests.c -c $@

test: tests.o $(TEST_OBJS) 
	@echo ""
	@for bin in $(TEST_OBJS); do \
		./$$bin; \
		echo ""; \
	done

test_%: $(TESTDIR)/%.c tests.o $(OBJECTS)
	$(CC) $(FLAGS) $< tests.o $(OBJECTS) -o $@