CC=g++

CFLAGS=-O3 -std=c++11 -c -Wall -pedantic -W 

LDFLAGS= 

RM=rm -f

EXEC=astar

CSRC=$(wildcard ./src/*.cpp)

HSRC=$(wildcard ./src/*.h)

OBJ=$(subst .cpp,.o,$(subst src,obj,$(CSRC)))



all: object $(EXEC)

$(EXEC):$(OBJ)
	@$(CC) $^ -o $@ $(LDFLAGS)

#gerar arquivos .o
./obj/%.o: ./src/%.cpp ./src/%.h
	@$(CC) $< $(CFLAGS) -o $@

./obj/main.o: ./src/main.cpp $(HSRC)
	@$(CC) $< $(CFLAGS) -o $@

object:
	@mkdir -p obj

clean:
	@rm -rf obj $(EXEC)

#alvo falso
.PHONY: all clean run