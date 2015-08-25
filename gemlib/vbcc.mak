

# makefile for gemlib 
# vbcc version


CC     = vc
AS     = vasmm68k_mot
AR     = ar

CFLAGS = -O1 -c99 -no-trigraphs
SFLAGS = -Faout -quiet
CFLAGS += $(MORE_CFLAGS)
SFLAGS += $(MORE_SFLAGS)

include files.mak




.SUFFIXES:
.SUFFIXES: .c .S .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o .vbcc/$*.o

.S.o:
	$(AS) $(SFLAGS) $*.S -o .vbcc/$*.o

TARGET = $(LIB_VBCC)

all: $(TARGET)

$(TARGET): $(OBJ) $(VC_OBJ)
	$(RM) $@
	cd .vbcc; $(AR) -r ../$@ $^; $(RM) $^; cd ..
