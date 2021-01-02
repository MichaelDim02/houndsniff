output: main.o select.o
	gcc main.o select.o -o hound

main.o: main.c
	gcc -c main.c

select.o: select.c select.h
	gcc -c select.c

clean:
	rm *.o hound
