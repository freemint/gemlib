/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns the location of the current clipboard directory.
 *
 *  @param Scrappath is a pointer to a character buffer of at least 128
 *         bytes into which the clipboard path will be placed.
 *  @param global_aes global AES array
 *
 *  @return 0 if the clipboard path had not been
 *          set or non-zero if \a Scrappath was properly updated. \n
 *          since MagiC-PC 2.0, this function returns -1 if the clipboard
 *          path had not been set, or a value >= 0 which is a bitmap value
 *          with one bit per type of file found in the clipboard, defined as
 *          follow:
 *          - #SCRAP_CSV if clipboard has a scrap.csv file
 *          - #SCRAP_TXT if clipboard has a scrap.txt file
 *          - #SCRAP_GEM if clipboard has a scrap.gem file
 *          - #SCRAP_IMG if clipboard has a scrap.img file
 *          - #SCRAP_DCA if clipboard has a scrap.dca file
 *          - #SCRAP_DIF if clipboard has a scrap.dif file
 *          - #SCRAP_USR if clipboard has a scrap.usr file
 *
 *  @since All AES versions.
 *
 *  @sa mt_scrp_write()
 *
 *  The system scrap directory is a global resource. Some
 *  programs incorrectly call mt_scrp_write() with a path and
 *  filename when only a pathname should be used. The following
 *  is an example of a correctly formatted \a Scrappath argument: \n
 *  	 \c C:\\CLIPBRD\\ \n
 *  Unfortunately, not all programs adhere exactly to
 *  this standard. For this reason, programs reading this
 *  information from mt_scrp_read() should be especially careful
 *  that the information returned is parsed correctly. In
 *  addition, don't count on a trailing backslash or the
 *  existence of a drive specification.
 *
 *  If a value of 0 is returned and the application wishes to
 *  write a scrap to the clipboard you should follow these
 *  steps:
 *  - Create a folder \c '\\CLIPBRD\\' on the root directory of
 *    the user's boot drive ('C:' or 'A:').
 *  - Write your scrap to the directory as \c 'SCRAP.???' where
 *    \c '???' signifies the type of information contained in the
 *    file.
 *  - Allow other applications to access this information by
 *    calling mt_scrp_write() with the new clipboard path. For
 *    example \c "C:\\CLIPBRD\\". 
 */

short 
mt_scrp_read(char *Scrappath, short *global_aes)
{
	AES_PARAMS(80,0,1,1,0);
                    
	aes_addrin[0] = (long)Scrappath;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
