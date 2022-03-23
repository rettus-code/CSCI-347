DEPS = argparse.h builtin.h
myshell: myshell.o argparse.o builtin.o
	gcc -o myshell myshell.o argparse.o builtin.o
myshell.o: myshell.c
	gcc -c myshell.c	
argparse.o: argparse.c
	gcc -c argparse.c
builtin.o: builtin.c
	gcc -c builtin.c
clean:
	rm myshell myshell.o argparse.o builtin.o
