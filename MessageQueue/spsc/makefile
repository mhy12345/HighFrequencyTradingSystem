DIR_INC = ../../SharedApplication
CC = g++
CXXFLAGS = -std=c++11 -g -I $(DIR_INC)

HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,%,$(SOURCES))

all : target
	@echo "SOURCES = " $(SOURCES)
	@echo "TARGETS = " $(TARGETS)
	@echo "HEADERS = " $(HEADERS)

target : $(TARGETS)

%.o : $(HEADERS)

clean : 
	rm *.o $(TARGETS)
