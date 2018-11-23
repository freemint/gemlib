# makefile for gemlib 
# purec version

# note:
# CC_PUREC must point to your pcc.ttp program
# AR_PUREC must point to your plink.ttp program
# AS_PUREC must point to your pasm.ttp program
# PURECINC must point to your purec/include directory

CC     = $(CC_PUREC)
AS     = $(AS_PUREC)
AR     = $(AR_PUREC) -J

CFLAGS = -I$(PURECINC) -P

include files.mak

.SUFFIXES:
.SUFFIXES: .c .s .o

# PCC.TTP crashes with long filename, so...
.c.o:
	cp $*.c tmppc.c
	$(CC) $(CFLAGS) -Otmppc.o tmppc.c
	mv -f tmppc.o $*.o

# PASM.TTP generates filename in UPPERCASE, so...
.s.o:
	$(AS) -OTMPPC.O $*.s
	mv TMPPC.O  $*.o

TARGET = $(LIB_PUREC)

all: $(TARGET)

$(TARGET): $(OBJ) $(PC_OBJ)
	rm -f $@
	$(AR) $^
	mv -f Linker.Out $@
