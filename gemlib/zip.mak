#
# build the ZIP archive
#

# note:
# ZIP must point to your zip.ttp program

include files.mak

ZIP_SRC = gemlib-src.zip
ZIP_ALL = gemlib-all.zip

all : $(ZIP_SRC)

# $(ZIP_ALL)

.PHONY: $(ZIP_SRC) $(ZIP_ALL)

$(ZIP_SRC):
	$(ZIP) -u $@  $(FILES_SRC) $(FILES_INC) $(LIB_PATH)

$(ZIP_ALL):
	$(ZIP) -u $@ $(FILES_SRC) $(FILES_INC) $(FILES_BIN)
