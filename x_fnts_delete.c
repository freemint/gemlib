/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** releases the memory allocated for the font selector.
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param vdi_handle Handle of the Workstation or 0, if vst_unload_fonts() is not
 *         to be called
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *
 *
 */

short 
mt_fnts_delete(FNT_DIALOG *fnt_dialog, short vdi_handle, short *global_aes)
{
	AES_PARAMS(181,1,1,1,0);
                    
	aes_intin[0]  = vdi_handle;
	aes_addrin[0] = (long)fnt_dialog;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
