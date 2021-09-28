# Houndsniff https://mcdim.xyz/projects/hs.html
# License: GNU GPL v3.0

CC=gcc
FILES=main.c select.c
BIN=houndsniff

all: main.c select.c
	$(CC) $(FILES) -o $(BIN)

install: main.c select.c $(BIN).1
	$(CC) $(FILES) -o $(BIN)
	sudo cp $(BIN) /usr/bin
	sudo cp $(BIN).1 /usr/share/man/man1
	sudo mandb

uninstall: /usr/bin/$(BIN) /usr/share/man/man1/$(BIN).1
	rm /usr/bin/$(BIN) /usr/share/man/man1/$(BIN).1
