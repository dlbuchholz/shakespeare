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

CC 					:= gcc
LD 					:= ld

DIR_BIN				:= bin
DIR_INCLUDE 		:= include
DIR_OBJ 			:= obj
DIR_LIB 			:= lib
DIR_SRC				:= src
DIR_SRCS			:= $(call rwildcard,src,*.c)

WARNINGS			:= -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
					   -Wcast-align -Wwrite-strings -Wmissing-prototypes \
					   -Wmissing-declarations -Wredundant-decls \
					   -Wnested-externs -Winline -Wno-long-long \
	             	   -Wconversion -Wstrict-prototypes
# - address sanitizer requires libasan (-fsanitize=address)
# - sanitizer for undefined behaviour requires libubsan (-fsanitize=undefined)
# (this causes issues with gcc on mingw, maybe use clang on windows instead) 
CFLAGS				:= -g -O2 -DDEBUG -I$(DIR_INCLUDE) $(WARNINGS)
#					   -fsanitize=leak -fsanitize=address\
#					   -fsanitize=null -fsanitize=undefined

OBJ 				 = $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o, $(DIR_SRCS))

shakespeare: $(OBJ)
	mkdir -p obj
	mkdir -p obj/bst
	$(CC) $(LDFLAGS) $^ -o $@  $(LIBS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

run-windows: shakespeare
	shakespeare.exe

.PHONY: clean

clean:
	rm -f $(DIR_OBJ)/*.o *~ core $(INCDIR)/*~
	rm -f $(DIR_OBJ)/bst/*.o *~ core $(INCDIR)/*~