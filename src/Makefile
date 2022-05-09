CC=gcc
CFLAGS=-Wall
DEPS = commands.h

cshell: commands.o cshell.o
	gcc -Wall -g commands.c cshell.c -o cshell

commands: commands.o
	gcc -Wall -g commands.c -o commands
