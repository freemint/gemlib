#
# makefile for mgemlib 
# purec version
#

CC_PUREC = /d/pure_c/pcc.ttp
AS_PUREC = /d/pure_c/pasm.ttp
AR_PUREC = /d/pure_c/plink.ttp -J
PURECINC = /d/pure_c/include

# note:
# CC_PUREC must point to your pcc.ttp program
# AR_PUREC must point to your plink.ttp program
# AS_PUREC must point to your pasm.ttp program

CC     = $(CC_PUREC)
AS     = $(AS_PUREC)
AR     = $(AR_PUREC)
CFLAGS = -I$(PURECINC)

include files.mak

.SUFFIXES:
.SUFFIXES: .c .s .o

# PCC.TTP crash with long filename, so...
.c.o:
	cp $*.c tmppc.c
	$(CC) $(CFLAGS) -Otmppc.o tmppc.c
	mv -f tmppc.o $*.o

# PASM.TTP generate filename in UPPERCASE, so...
.s.o:
	$(AS) -OTMPPC.O $*.s
	mv TMPPC.O  $*.o

TARGET = $(LIB_PUREC)

all: $(TARGET)

$(TARGET): $(OBJ) $(PC_OBJ)
	rm -f $@
	$(AR) $^
	mv -f Linker.Out $@
