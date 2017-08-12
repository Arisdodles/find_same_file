main: main.o list_dir.o cmp_file.o
	gcc -o main main.o list_dir.o cmp_file.o
	
main.o: main.c
	gcc -c main.c
	
list_dir.o: list_dir.c
	gcc -c list_dir.c
	
cmp_file.o: cmp_file.c
	gcc -c cmp_file.c
