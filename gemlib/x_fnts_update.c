/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** font selector - update window
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param button_flags Flags for supported buttons:
 *         - FNTS_SNAME     0x01  Select checkbox for the names 
 *         - FNTS_SSTYLE    0x02  Select checkbox for the style 
 *         - FNTS_SSIZE     0x04  Select checkbox for the height
 *         - FNTS_SRATIO    0x08  Select checkbox for the width/height ratio 
 *         - FNTS_CHNAME   0x0100  Display checkbox for the names 
 *         - FNTS_CHSTYLE  0x0200  Display checkbox for the style 
 *         - FNTS_CHSIZE   0x0400  Display checkbox for the height
 *         - FNTS_CHRATIO  0x0800  Display checkbox for the width/height ratio
 *         - FNTS_RATIO    0x1000  Width/height ratio adjustable
 *         - FNTS_BSET     0x2000  Button "setting" selectable 
 *         - FNTS_BMARK    0x4000  Button "marking" selectable 
 *  @param id Font ID
 *  @param pt Height in 1/65536 point
 *  @param ratio Width/height ratio in 1/65536
 *  @param global_aes global AES array
 *
 *  @return one of the following value:
 *	        - -1: Function not present
 *	        -  0: Error (insufficient memory), the font selector must then be 
 *             closed with mt_fnts_close().
 *	        -  1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *  @note This function was not present in older versions of WDIALOG. 
 *        The binding ensures that in that case the function returns -1.
 *
 */

short 
mt_fnts_update(FNT_DIALOG *fnt_dialog, short button_flags, long id, long pt, long ratio, short *global_aes)
{
	unsigned short *i;
	
	AES_PARAMS(185,8,1,1,0);

	aes_intin[0] = 2;
	aes_intin[1] = button_flags;
	i = (unsigned short *)&id;
	aes_intin[2] = i[0];
	aes_intin[3] = i[1];
	i = (unsigned short *)&pt;
	aes_intin[4] = i[0];
	aes_intin[5] = i[1];
	i = (unsigned short *)&ratio;
	aes_intin[6] = i[0];
	aes_intin[7] = i[1];
	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
