#include "gem_vdiP.h"

/** outputs graphic text and lengthens or shortens 
 *  the string by modifying the interword or intercharacter spacing
 *
 *  @param handle Device handle
 *  @param x x-coordinate
 *  @param y y-coordinate
 *  @param wstr string
 *  @param num string len
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
v_justified16n (short handle, short x, short y,
              const short * wstr, short num, short len, short word_space, short char_space)
{
	short vdi_control[VDI_CNTRLMAX];  
	
	short vdi_ptsin[4];   

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	if(num<=VDI_INTINMAX-2) /* v_justified can be used */
	{	
		short vdi_intin[VDI_INTINMAX]; 
		short i,*dest=&vdi_intin[2];  
	
		VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy );
		for(i=0;i<num;i++) *dest++=*wstr++;
		vdi_intin[0] = word_space;
		vdi_intin[1] = char_space;
		
		vdi_ptsin[2] = len;
		vdi_ptsin[3] = 0;

		VDI_TRAP_ESC (vdi_params, handle, 11,10, 2,num+2);
	}
	else /* gemlib limitation use v_gtext in replacement */
	{
		VDI_PARAMS(vdi_control, wstr, vdi_ptsin, vdi_dummy, vdi_dummy );
		VDI_TRAP (vdi_params, handle, 8, 1,num);
	}
}
