CC      := cc
CFLAGS  := -Wall -Wextra -g -O2 $(shell pkg-config --cflags sdl3)
LDLIBS  := $(shell pkg-config --libs sdl3)

TARGET  := movebetter
SRC     := movebetter.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
