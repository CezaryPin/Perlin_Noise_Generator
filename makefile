test.exe: map_gen.o utils.o
	gcc map_gen.o utils.o -o test.exe

map_gen.o: map_gen.c
	gcc -c map_gen.c -o map_gen.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f test.exe utils.o map_gen.o