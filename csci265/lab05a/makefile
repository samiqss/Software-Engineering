C=g++ -Wall -Wextra
ASM=as --gstabs
SIMPLE=-fno-asynchronous-unwind-tables
EXPAND=-E
OBJ=-c
TOASM=-S

all: takehome9 takehome9e.cpp
	@echo “build all executable”

takehome9: sumAll.o takehome9.o
	@echo “building takehome9”
	${CC} takehome9.o sumAll.o -o takehome9

takehome9.o: takehome9.s 
	@echo “building takehome9.o”
	${ASM} takehome9.s -o takehome9.o

sumAll.o: takehome9.h sumAll.cpp
	@echo “building sumAll.o”
	${CC} ${OBJ} sumAll.cpp -o sumAll.o

takehome9.s: takehome9.cpp 
	@echo “building takehome9.s”
	${CC} ${TOASM} takehome9.cpp ${SIMPLE}

takehome9e.cpp: takehome9.cpp
	@echo “building takehome9e”
	${CC} ${EXPAND} takehome9.cpp -o takehome9e.cpp

clean:
	rm -f takehome9e.cpp takehome9.o sumAll.o takehome9.s 


