#include "gem_aesP.h"
#include "mt_gemx.h"

/** initialises the print dialog
 *
 *  @param dialog_flags Only 3D-flag at present:
 *         - PDLG_3D     (1)    Display selection in 3D-look
 *  @param global_aes global AES array
 *
 *  @return Pointer to management structure
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  On calling the function a 
 *  scan will be made for the printer drivers present and memory will be 
 *  allocated for the resource.
 *
 */

PRN_DIALOG *
mt_pdlg_create(short dialog_flags, short *global_aes)
{
	AES_PARAMS(200,1,0,0,1);

	aes_intin[0] = dialog_flags;
	aes_addrout[0] = 0;

	AES_TRAP(aes_params);

	return (void *)aes_addrout[0];
}
