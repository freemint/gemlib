/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** outputs graphic text and lengthens or shortens 
 *  the string by modifying the interword or intercharacter spacing
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param str string
 *  @param len length in pixels
 *  @param word_space <> 0: Wortzwischenr„ume dehnen
 *  @param char_space <> 0: Zeichenzwischenr„ume dehnen
 *
 *  @since all VDI versions
 *
 *  If you 
 *  use a vector font, the requested width of the string refers to the sum 
 *  of the character widths - characters extending beyond the left or right 
 *  edge of the em square are ot taken into account.
 *
 */

void
v_justified (short handle, short x, short y,
             const char *str, short len, short word_space, short char_space)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_ptsin[4];   
#endif
	register short n = 2 + vdi_str2array (str, vdi_intin + 2);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy );
#endif

	vdi_intin[0] = word_space;
	vdi_intin[1] = char_space;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = len;
	vdi_ptsin[3] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 11,10, 2,n);
}
