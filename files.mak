# 
# hierarchy used:
#
# .             -- root contains sources, makefiles, CHANGELO...
# ./include     -- headers files
# ./lib/gcc     -- lib compiled for gcc 2.95.3 (SpareMiNT)
# ./lib/gcc281  -- lib compiled for gcc 2.81c
# ./lib/sozobon -- lib compiled for sozobonx
# ./lib/purec   -- lib compiled for pure c
#

# library filenames

LIB_GCC           = libgem.a
LIB_GCC_MSHORT    = libgem16.a
LIB_GCC281        = lib/gcc281/gem.olb
LIB_GCC281_MSHORT = lib/gcc281/gem16.olb
LIB_SOZOBON       = lib/sozobon/gem.a
LIB_PUREC         = lib/purec/gem.lib

# headers

FILES_INC = \
 gem.h gemx.h mt_gem.h mt_gemx.h

# objects files
include SRCFILES

OBJ = $(COBJS:.c=.o)

# object file specific to compiler

SX_OBJ = _sx_asm.o
GC_OBJ = 
PC_OBJ = _pc_asm.o
VC_OBJ = 
LA_OBJ = _lc_asm.o
