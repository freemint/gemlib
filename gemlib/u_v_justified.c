

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
udef_v_justified (short handle, short x, short y,
             const char *str, short len, short word_space, short char_space)
{
	short n = 2 + vdi_str2array_n (str, _VDIParBlk.vdi_intin + 2, VDI_INTINMAX-2);

	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;

	if(n<VDI_INTINMAX) /* v_justified can be used */
	{
		VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy );

		_VDIParBlk.vdi_intin[0] = word_space;
		_VDIParBlk.vdi_intin[1] = char_space;
		_VDIParBlk.vdi_ptsin[2] = len;
		_VDIParBlk.vdi_ptsin[3] = 0;

		VDI_TRAP_ESC (vdi_params, handle, 11,10, 2,n);
	}
	else /* gemlib limitation use v_gtext in replacement */
	{
		VDI_PARAMS(_VDIParBlk.vdi_control, &_VDIParBlk.vdi_intin[2], _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy );
		VDI_TRAP (vdi_params, handle, 8, 1,n);
	}
}

