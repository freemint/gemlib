

# makefile for gemlib 
# vbcc version


CC     = vc
AS     = vasmm68k_mot
AR     = ar

CFLAGS = -O2 -c99 -no-trigraphs
SFLAGS = -Faout -quiet

include files.mak

.SUFFIXES:
.SUFFIXES: .c .S .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o .vbcc/$*.o

.S.o:
	$(AS) $(SFLAGS) $*.S -o .vbcc/$*.o

TARGET = $(LIB_VBCC68K)

all: $(TARGET)

$(TARGET): $(OBJ) $(VC_OBJ)
	$(RM) $@
	cd .vbcc; $(AR) -r ../$@ $^; $(RM) $^; cd ..
