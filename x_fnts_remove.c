/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** removes the fonts installed with mt_fnts_add() 
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *  @note If a program's user fonts have been installed, then 
 *        mt_fnts_remove() must be called before mt_fnts_delete().
 *
 */

void 
mt_fnts_remove(FNT_DIALOG *fnt_dialog, short *global_aes)
{
	AES_PARAMS(185,1,0,1,0);
                    
	aes_intin[0] = 1;

	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);
}
