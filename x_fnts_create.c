/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function initialises the font selector
 *
 *  @param vdi_handle Handle of the workstation to be used
 *  @param no_fonts Number of available fonts or 0. If \p no_fonts is 0, 
 *         vst_load_fonts() is called with \p vdi_handle. Otherwise an assumption is 
 *         made that \p no_fonts is the number of all fonts available via \p vdi_handle, 
 *         i.e. the number of all system fonts (work_out[10] for v_opnvwk()/vq_extnd())
 *         plus the number of fonts loaded in later (return value of vst_load_fonts()).
 *  @param font_flags Type of fonts to be displayed. It's a bitmap variable which
 *         have the following signification:
 *         - FNTS_BTMP   (1)   Display bitmap fonts 
 *         - FNTS_OUTL   (2)   Display vector fonts 
 *         - FNTS_MONO   (4)   Display mono-spaced fonts 
 *         - FNTS_PROP   (8)   Display proportional fonts 
 *  @param dialog_flags Appearance of the dialog as following:
 *         - FNTS_3D     (1)   Display selector in 3D-look
 *  @param sample Pointer to string for the sample text
 *  @param opt_button Pointer to string for optional button or 0L
 *  @param global_aes global AES array
 *
 *  @return a Pointer to management structure
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *  @note  Depending on system configuration, this function may well take 
 *         1 second (possibly even more), so it should be called at program start and 
 *         not just immediately before displaying the font selector.
 *
 *  Please note: The font selector alters the attributes of the workstation 
 *  described by \p vdi_handle. If one wants to use the workstation passed with 
 *  mt_fnts_create() also for other purposes, the attributes have to be set first 
 *  each time, as they may have been altered meantime by the font selector.
 *
 */
 
FNT_DIALOG *
mt_fnts_create(short vdi_handle, short no_fonts, short font_flags, short dialog_flags,
               char *sample, char *opt_button, short *global_aes)
{
	AES_PARAMS(180,4,0,2,1);
                    
	aes_intin[0] = vdi_handle;
	aes_intin[1] = no_fonts;
	aes_intin[2] = font_flags;
	aes_intin[3] = dialog_flags;
	
	aes_addrin[0] = (long)sample;
	aes_addrin[1] = (long)opt_button;

	AES_TRAP(aes_params);

	return (FNT_DIALOG*)aes_addrout[0];
}
