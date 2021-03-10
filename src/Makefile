output: main.c select.c
        gcc main.c select.c -o hound

install: houndsniff.1
        sudo cp houndsniff.1 /usr/share/man/man1
        sudo mandb

