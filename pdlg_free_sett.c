/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Releases the memory allocated with mt_pdlg_new_settings().
 *
 *  @param settings Printer settings
 *  @param global_aes global AES array
 *
 *  @return unknown ???
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short
mt_pdlg_free_settings(PRN_SETTINGS *settings, short *global_aes)
{
	AES_PARAMS(205,1,1,1,0);

	aes_intin[0] = 6;

	aes_addrin[0] = (long)settings;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
