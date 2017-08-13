main: main.o list_dir.o cmp_file.o
	gcc -o main main.o list_dir.o cmp_file.o -Wall
	
main.o: main.c
	gcc -c main.c -Wall
	
list_dir.o: list_dir.c
	gcc -c list_dir.c -Wall
	
cmp_file.o: cmp_file.c
	gcc -c cmp_file.c -Wall
