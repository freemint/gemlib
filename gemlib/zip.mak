#
# build the ZIP archive
#

# note:
# ZIP must point to your zip.ttp program

include files.mak

.PHONY: purec sozobonx gcc281 gcc

default: purec sozobonx gcc281 gcc

purec:
	rm -rf $@
	mkdir $@ $@/lib $@/include
	cp $(FILES_INC) include/purec/compiler.h $@/include
	cp $(LIB_PUREC) $@/lib
	$(ZIP) -ur $@.zip $@
	rm -rf $@

sozobonx:
	rm -rf $@
	mkdir $@ $@/lib $@/include
	cp $(FILES_INC) include/sozobon/compiler.h $@/include
	cp $(LIB_SOZOBON) $@/lib
	$(ZIP) -ur $@.zip $@
	rm -rf $@

gcc281:
	rm -rf $@
	mkdir $@ $@/lib $@/include
	cp $(FILES_INC) include/gcc281/compiler.h $@/include
	cp $(LIB_GCC281_MSHORT) $(LIB_GCC281) $@/lib
	$(ZIP) -ur $@.zip $@
	rm -rf $@

gcc:
	rm -rf $@
	mkdir $@ $@/lib $@/include
	cp $(FILES_INC) $@/include
	cp $(LIB_GCC $(LIB_GCC_MSHORT) $@/lib
	$(ZIP) -ur $@.zip $@
	rm -rf $@

