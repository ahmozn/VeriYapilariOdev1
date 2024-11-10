all: derle calistir

derle: lib/Program.o lib/DLList.o lib/KromozomNode.o lib/GenNode.o
	g++ -I ./include/ -o ./bin/Program lib/Program.o lib/DLList.o lib/KromozomNode.o lib/GenNode.o

lib/Program.o: ./src/Program.cpp
	g++ -I ./include/ -c ./src/Program.cpp -o lib/Program.o

lib/DLList.o: ./src/DLList.cpp
	g++ -I ./include/ -c ./src/DLList.cpp -o lib/DLList.o

lib/KromozomNode.o: ./src/KromozomNode.cpp
	g++ -I ./include/ -c ./src/KromozomNode.cpp -o lib/KromozomNode.o

lib/GenNode.o: ./src/GenNode.cpp
	g++ -I ./include/ -c ./src/GenNode.cpp -o lib/GenNode.o

calistir:
	./bin/Program

clean:
	rm -f lib/*.o