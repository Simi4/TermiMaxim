all:
	gcc main.c common.c -o bin -Wall

san:
	gcc -fsanitize=address main.c common.c -o bin -Wall

checkstyle:
	perl /home/max/DEV/linux-4.14.22/scripts/checkpatch.pl -f *.h *.c