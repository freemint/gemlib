/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Open file selector window
 *
 *  @param title Window title of file selector, may be NULL
 *  @param x 
 *  @param y Screen coordinates of the upper
 *			 left corner of the window. \n
 *			 For x=y=-1 the window will be centred.
 *  @param handle Window handle after successful opening
 *  @param path Complete path, starts with drive and ends with '\'
 *  @param pathlen Length of path buffer, i.e. maximum
 *		   pathlength + 1 (for EOS)
 *  @param fname Buffer for the filename
 *  @param fnamelen Length of filename buffer, i.e. maximum
 *		   length of filename + 1 (for EOS)
 *  @param patterns Filemask, e.g. "*.TXT" or "*.PRG,*.APP". 
 *		   The alternatively selectable masks are
 *		   separated by EOS and terminated by
 *		   EOS,EOS.
 *  @param filter May be NULL. The filter function is
 *		   called before the mask comparison. If
 *		   it returns 0 then the file is invalid,
 *		   if 1 is returned then the filename will
 *		   be displayed.
 *  @param paths Path "history" e.g. "C:\\BIN\\" etc.
 *		   The alternatively selectable paths are
 *		   separated by EOS and terminated by
 *		   EOS,EOS.
 *  @param sort_mode Sort mode for the display. The modes are:
 *         - SORTBYNAME	 (0)
 *         - SORTBYDATE  (1)
 *         - SORTBYSIZE  (2)
 *         - SORTBYTYPE  (3)
 *         - SORTBYNONE  (4)
 *         .
 *         SORTBYNONE here means the physical order on the disk.
 *  @param flags Various settings:
 *         - DOSMODE	(1) \n
 *           DOSMODE is the compatibility mode that
 *			 is also used by fsel_(ex)input and
 *			 basically returns filenames in the
 *			 8+3 format. For this all directories
 *			 are called with Dopendir(DOPEN_COMPAT).
 *         - NFOLLOWSLKS (2)\n
 *			 If NFOLLOWSLKS is set, then symbolic
 *			 links will not be followed, i.e. date
 *			 and time etc., as well as the XATTR-
 *			 structure that is passed to \p filter,
 *			 belong to the link itself.
 *         - GETMULTI	 (8)\n
 *			 If GETMULTI is set, one can select and
 *			 pass several files at the same time.
 *			 For this fslx_getnxtfile() is used
 *			 if fslx_evnt() or fslx_do() in the
 *			 parameter \p nfiles signals that there
 *			 are still further files selected.
 *  @param global_aes global AES array
 *
 *  @return a descriptor for further actions
 *		    or NULL if an error has occurred (not
 *		    enough memory or no more window handles
 *		    free).
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *  The corresponding descriptor will be created and the file selector window
 *  opened.
 *
 */


void *
mt_fslx_open(char *title, short x, short y, short *handle, char *path, short pathlen,
			 char *fname, short fnamelen, char *patterns, XFSL_FILTER filter,
			 char *paths, short sort_mode, short flags, short *global_aes)
{
	AES_PARAMS(190,6,1,6,1);
                    
	aes_intin[0] = x;
	aes_intin[1] = y;
	aes_intin[2] = pathlen;
	aes_intin[3] = fnamelen;
	aes_intin[4] = sort_mode;
	aes_intin[5] = flags;
	
	aes_addrin[0] = (long)title;
	aes_addrin[1] = (long)path;
	aes_addrin[2] = (long)fname;
	aes_addrin[3] = (long)patterns;
	aes_addrin[4] = (long)filter;
	aes_addrin[5] = (long)paths;

	AES_TRAP(aes_params);

	*handle = aes_intout[0];
	
	return (void *)aes_addrout[0];
}
