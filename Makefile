CC = clang
CFLAGS = -Wall -Wextra -std=c2x -O2
TARGET = test/test_slugify
SOURCES = cslugify.c test/test_slugify.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
