
all: main
	
main: banco_gui.o 
	g++ -o main banco_gui.o 

banco_gui.o: banco_gui.cpp
	g++ -c banco_gui.cpp  

cliente.o: cliente.cpp
	g++ -c cliente.cpp

cliente: cliente.o
	g++ -o cliente cliente.o -lrt -lpthread

prueba.o: prueba.cpp
	g++ -c prueba.cpp

prueba: prueba.o
	g++ -o prueba prueba.o -lrt -lpthread
	
run: main
	./main

.PHONY: clean

clean:
	rm -f main *.o
