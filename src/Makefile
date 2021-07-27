# Houndsniff https://mcdim.xyz/projects/hs.html
# License: GNU GPL v3.0

CC=gcc
FILES=main.c select.c
BIN=houndsniff

all: main.c select.c
	$(CC) $(FILES) -o $(BIN)

install: main.c select.c houndsniff.1
	$(CC) $(FILES) -o $(BIN)
	sudo cp hound /usr/bin
	sudo cp houndsniff.1 /usr/share/man/man1
	sudo mandb

uninstall: /usr/bin/$(BIN) /usr/share/man/man1/houndsniff.1
	rm /usr/bin/$(BIN) /usr/share/man/man1/houndsniff.1
