all: ./lib/fields.o derle calistir

derle: 
	g++ -I ./include/ -o ./bin/Program ./src/Program.cpp ./src/DLList.cpp ./src/KromozomNode.cpp ./src/GenNode.cpp ./src/fields.c

calistir: 
	./bin/Program

./lib/fields.o: ./src/fields.c include/fields.h
	g++ -O3 -Iinclude -c -o ./lib/fields.o ./src/fields.c