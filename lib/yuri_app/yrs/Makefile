LINKPATH  = ../../../ls
DST = ../../../dst
APP = ../../../application
YURIEXE = main.o

all: $(YURIEXE) Makefile
	@echo 'BUILD YURISCRIPT DIRECTORY'
	@ld -melf_i386 -o $(APP)/yrs.yx --script=$(LINKPATH)/app.lds main.o $(DST)/libyuri.a
	@mv *.o $(DST)

%.o: %.c
	@$(CC) $*.c $(BINOPT) -o $*.o

%.o: %.asm
	@nasm -f elf $*.asm -o $*.o

