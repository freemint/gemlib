#include "gem_vdiP.h"

/** This function returns the current line attributes
 *
 *  @param handle Device handle
 *  @param attrib contain the following informations:
 *         - attrib[0]           line type
 *         - attrib[1]           line color
 *         - attrib[2]           writing mode
 *         - attrib[3]           line width
 *         - attrib[4]           end style for first point
 *         - attrib[5]           end style for last point
 *
 *  @since all VDI versions
 *
 */

void
vql_attributes (short handle, short attrib[])
{
	short *ptr;
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[5]; 
	short vdi_ptsout[2]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_ptsout );
	
	VDI_TRAP_00 (vdi_params, handle, 35);
	
	ptr = vdi_intout;
	*(attrib ++) = *(ptr ++);	  /* attrib[0] = vdi_intout[0]; */
	*(attrib ++) = *(ptr ++);	  /* attrib[1] = vdi_intout[1]; */
	*(attrib ++) = *(ptr ++);	  /* attrib[2] = vdi_intout[2]; */
	*(attrib ++) = vdi_ptsout[0]; /* attrib[3] = vdi_ptsout[0]; */
	*(attrib ++) = *(ptr ++);	  /* attrib[4] = vdi_intout[3]; */
	*(attrib   ) = *(ptr   );	  /* attrib[5] = vdi_intout[4]; */
}
