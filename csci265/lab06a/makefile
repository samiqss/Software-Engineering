# lab 6 makefile
CC=g++ -Wall -Wextra
ASM=as --gstabs
SIMPLE=-fno-asynchronous-unwind-tables
EXPAND=-E
OBJ=-c
TOASM=-S

all: lab6 lab6.cpp
	@echo “build the executable”

lab6: lab6.o
	@echo “building lab6”
	${CC} lab6.o -o lab6

lab6.o: lab6.s 
	@echo “building lab6.o”
	${ASM} lab6.s -o lab6.o

lab6.s: lab6.cpp 
	@echo “building lab6.s”
	${CC} ${TOASM} lab6.cpp

clean:
	rm -f lab6.o lab6.s 

submit:
	git add .
	git add -u
	git commit -m "lab6 submission"
	git push 
