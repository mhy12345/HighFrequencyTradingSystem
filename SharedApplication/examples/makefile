DIR_INC = ../
CC = g++
CXXFLAGS = -std=c++11 -g -I $(DIR_INC)


target : main

main : a.o b.o
	g++ a.o b.o -o main

a : a.o

b : b.o

clean : 
	rm *.o main
