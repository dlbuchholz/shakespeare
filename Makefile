##
## Makefile
##
## This Makefile contains all neccesary build routines.
##
##  Created on: 11.10.2022
##      Author: Dennis Lucas Buchholz
##

# Default programs used for building...

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
#CC 					:= clang -target i386-pc-windows-gnu -fuse-ld=lld
CC                  := gcc
LD                  := ld

DIR_BIN				:= bin
DIR_INCLUDE 	    := include
DIR_OBJ 			:= obj
DIR_LIB 			:= lib
DIR_SRC				:= src
DIR_SRCS			:= $(call rwildcard,src,*.c)

WARNINGS			:= -Wall -Wextra -Wshadow -Wpointer-arith \
					   -Wcast-align -Wwrite-strings -Wmissing-prototypes \
					   -Wmissing-declarations -Wredundant-decls \
					   -Wnested-externs -Winline -Wno-long-long \
	             	   -Wconversion -Wstrict-prototypes \
					   # -Werror marks all Warnings as errors
CFLAGS				:= -g -O2 -pedantic -I$(DIR_INCLUDE) $(WARNINGS)

OBJ 				 = $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o, $(DIR_SRCS))

.DEFAULT_GOAL := all

all: prepare shakespeare doc/documentation.pdf

debug: CFLAGS += -DDEBUG
debug: shakespeare

prepare:
	mkdir -p doc
	mkdir -p obj
	mkdir -p obj/bst
	mkdir -p obj/markov
	mkdir -p obj/test

shakespeare: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@  $(LIBS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

test: CFLAGS += -Itest
test: OBJ += obj/test/test_runner.o
test: $(filter-out obj/shakespeare.o,$(OBJ))
	$(CC) $(CFLAGS) test/test_runner.c $^ -o $@  $(LIBS)
	./test
	
doc/documentation.pdf: doc/documentation.tex
	texify --pdf --synctex=1 --clean doc/documentation.tex
	mv documentation.pdf doc/
	mv documentation.synctex.gz doc/

format:
	astyle --suffix=none --style=google --max-code-length=80 --recursive "src/*.c"
	astyle --suffix=none --style=google --max-code-length=80 --recursive "include/*.h"

.PHONY: all clean test

clean:
	rm -f $(DIR_OBJ)/*.o *~ core $(INCDIR)/*~
	rm -f $(DIR_OBJ)/bst/*.o *~ core $(INCDIR)/*~
	rm -f $(DIR_OBJ)/markov/*.o *~ core $(INCDIR)/*~
	rm doc/*.pdf
