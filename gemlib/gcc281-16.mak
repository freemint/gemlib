#
# $Id$
#

# makefile for gemlib 
# gcc 2.81 version (16 bits)

# note:
# CC_GCC281 must point to your gcc.ttp program
# AR_GCC281 must point to your  ar.ttp program

CC     = $(CC_GCC281)
AR     = $(AR_GCC281)

CFLAGS = -O2 -Wall -m68000 -mshort

include files.mak

.SUFFIXES:
.SUFFIXES: .c .S .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

.S.o:
	$(CC) $(CFLAGS) -c $*.S -o $*.o

TARGET = $(LIB_GCC281_MSHORT)

$(TARGET): $(OBJ) $(GC_OBJ)
	$(RM) $@
	$(AR) cs $@ $^
