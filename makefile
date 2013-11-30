all: *.flex *.y *.h
	bison --debug --verbose -d gram.y
	bison -d -o gram.cpp gram.y
	flex  -o lex.yy.cpp lex.flex
	g++ -o algebra.o -c algebra.cpp
	g++ -o data_represent.o -c data_represent.cpp
	g++ -o excutor.o -c excutor.cpp
	g++ -o gram.o -c gram.cpp
	g++ -o lex.yy.o -c lex.yy.cpp
	g++ -o lex_defines.o -c lex_defines.cpp
	g++ -o main.o -c main.cpp
	g++ -o storage.o -c storage.cpp
	g++ -o index.o -c index.cpp
	g++ -o simple_log.o -c simple_log.cpp
	g++ -o test *.o
	
