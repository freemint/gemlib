/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** opens a modal dialog and only returns to the caller when 
 *  one of the exit buttons ("Cancel", "OK", "Set", "Mark" or "Options") 
 *  was activated.
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param button_flags 
 *  @param id_in 
 *  @param pt_in
 *  @param ratio_in 
 *  @param check_boxes will contain the Status of the checkboxes \n
 *             [option CHECK_NULLPTR] check_boxes may be NULL
 *  @param id will contain the ID of the selected font \n
 *             [option CHECK_NULLPTR] id may be NULL
 *  @param pt will contain the Height in 1/65536 point \n
 *             [option CHECK_NULLPTR] pt may be NULL
 *  @param ratio will contain the Width/height ratio \n
 *             [option CHECK_NULLPTR] ratio may be NULL
 *  @param global_aes global AES array
 *
 *  @return Selected button (or 0)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *
 *
 */

short 
mt_fnts_do(FNT_DIALOG *fnt_dialog, short button_flags, long id_in, long pt_in, 
		   long ratio_in, short *check_boxes, long *id, long *pt, long *ratio, short *global_aes)
{
	unsigned short *i;
	
	AES_PARAMS(187,7,8,1,0);

	aes_intin[0] = button_flags;
	i = (unsigned short *)&id_in;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	i = (unsigned short *)&pt_in;
	aes_intin[3] = i[0];
	aes_intin[4] = i[1];
	i = (unsigned short *)&ratio_in;
	aes_intin[5] = i[0];
	aes_intin[6] = i[1];
	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (check_boxes)
#endif
	*check_boxes = aes_intout[1];
#if CHECK_NULLPTR
	if (id)
#endif
	*id = ((long)aes_intout[2] << 16) | (aes_intout[3]);
#if CHECK_NULLPTR
	if (pt)
#endif
	*pt = ((long)aes_intout[4] << 16) | (aes_intout[5]);
#if CHECK_NULLPTR
	if (ratio)
#endif
	*ratio = ((long)aes_intout[6] << 16) | (aes_intout[7]);
	
	return aes_intout[0];
}
