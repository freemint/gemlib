#include "gem_aesP.h"
#include "mt_gemx.h"

/** evaluates the passed  EVNT structure and internally calls mt_wdlg_evnt()
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param events Pointer to EVNT structure
 *  @param button will contain the Selected button (or 0) \n
 *             [option CHECK_NULLPTR] button may be NULL
 *  @param check_boxes will contain the Status of the checkboxes:
 *         - FNTS_SNAME 	0x01   Checkbox for the names selected 
 *         - FNTS_SSTYLE	0x02   Checkbox for the style selected 
 *         - FNTS_SSIZE 	0x04   Checkbox for the height selected
 *         - FNTS_SRATIO	0x08   Checkbox for the width/height ratio selected 
 *         .
 *             [option CHECK_NULLPTR] check_boxes may be NULL
 *  @param id will contain the ID of the selected font \n
 *             [option CHECK_NULLPTR] id may be NULL
 *  @param pt will contain the Height in 1/65536 point \n
 *             [option CHECK_NULLPTR] pt may be NULL
 *  @param ratio will contain the Width/height ratio \n
 *             [option CHECK_NULLPTR] ratio may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 (Exit button selected) or 1 (Nothing happened)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *  If one of the exit buttons ("Cancel", "OK", "Set", "Mark" 
 *  or "Options") was activated  the function returns 0 and the button that 
 *  the user has selected is returned in button.
 *
 */

short 
mt_fnts_evnt(FNT_DIALOG *fnt_dialog, EVNT *events, short *button, short *check_boxes,
             long *id, long *pt, long *ratio, short *global_aes)
{
	AES_PARAMS(186,0,9,2,0);
                    
	aes_addrin[0] = (long)fnt_dialog;
	aes_addrin[1] = (long)events;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (button)
#endif
	*button = aes_intout[1];
#if CHECK_NULLPTR
	if (check_boxes)
#endif
	*check_boxes = aes_intout[2];
#if CHECK_NULLPTR
	if (id)
#endif
	*id = aes_intout_long(3);
#if CHECK_NULLPTR
	if (pt)
#endif
	*pt = aes_intout_long(5);
#if CHECK_NULLPTR
	if (ratio)
#endif
	*ratio = aes_intout_long(7);
	
	return aes_intout[0];
}
