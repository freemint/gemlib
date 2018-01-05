

# makefile for gemlib
# sozobon version

# note:
# CC_LAT must point to your lc.ttp program
# AR_LAT must point to your oml.ttp program
# AS_LAT must point to your asm.ttp program
# to compile you have to setenv INCLUDE in your mint.cnf to the include directory of the Lattice C

CC     = $(CC_LAT)
AS     = $(AS_LAT)
AR     = $(AR_LAT)


# PATH_BIN_LAT must point to the folder to your lattice binary program (like lc.ttp)
# the path format should be something like "/e/dev/lattice/BIN/" and not use ':'
PATH   +=:$(PATH_BIN_LAT)


CFLAGS =
SFLAGS =
CFLAGS += $(MORE_CFLAGS)
SFLAGS += $(MORE_SFLAGS)
include files.mak
count = 1



.SUFFIXES:
.SUFFIXES: .c .s .o

#lattice not compatible with long filename
.c.o:
	cp $*.c tmp`cat count.txt`.c
	$(CC) $(CFLAGS) -otmp`cat count.txt`.o tmp`cat count.txt`.c
	mv -f tmp`cat count.txt`.o .lattice/$*.o
	rm -f tmp`cat count.txt`.c;
	
	echo `cat count.txt` + 1 | bc >> count2.txt;
	rm -f count.txt;
	mv -f count2.txt count.txt;
#	cat count.txt;

.s.o:
	$(AS) $(SFLAGS) $*.s -o$*.o
	mv -f $*.o .lattice/$*.o

TARGET = $(LIB_LATTICE)

all: $(TARGET)

$(TARGET): $(OBJ) $(LA_OBJ)
	$(RM) $@
	cd .lattice; $(AR) ../$@ r $^; cd ..
