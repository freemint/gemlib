#
# 15/10/1999 Draco (draco@atari.org)
#

CPU= -m68020-60
CC= gcc
RM= rm -f
DEFS=
LIB= -lgemma -lslb
CFLAGS= -Wall -O2 $(CPU) -mshort -fomit-frame-pointer $(DEFS)
LFLAGS= -s $(CPU) -mshort -nostartfiles
OBJ= startup.o test.o
TARGET= test.app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) $(LIB) -o $@

startup.o: startup.S
	$(CC) $(CFLAGS) -c startup.S -o $@

clean:
	$(RM) *.o

veryclean:
	$(RM) *.o $(TARGET)
