#
# $Id$
#

# makefile for gemlib 
# gcc >= 2.95.3 (sparemint) version
CROSS = yes
ifeq ($(CROSS),yes)
CC     = m68k-atari-mint-gcc
AR     = m68k-atari-mint-ar
else
CC     = gcc
AR     = ar
endif

CFLAGS = -O2 -Wall -fomit-frame-pointer

include files.mak

.SUFFIXES:
.SUFFIXES: .c .S .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

.S.o:
	$(CC) $(CFLAGS) -c $*.S -o $*.o

TARGET = $(LIB_GCC)

$(TARGET): $(OBJ) $(GC_OBJ)
	$(RM) $@
	$(AR) cru $@ $^
