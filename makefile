all: derle calistir

derle: 
	g++ -I ./include/ -o ./bin/Program ./src/Program.cpp ./src/DLList.cpp ./src/KromozomNode.cpp ./src/GenNode.cpp

calistir: 
	./bin/Program