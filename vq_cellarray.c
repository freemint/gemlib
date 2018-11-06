#include "gem_vdiP.h"

/** returns the cell array definition of the specified pixels
 *
 *  @param handle Device handle
 *  @param pxy 
 *  @param row_len Length of each row in color index array.
 *  @param nrows Number of rows in color index array
 *  @param el_used Number of elements used in each row of color index array \n
 *         [option CHECK_NULLPTR] el_used may be NULL
 *  @param rows_used Number of rows used in color index array \n
 *         [option CHECK_NULLPTR] rows_used may be NULL
 *  @param status Invalid value flag:
 *         - 0 if no errors
 *         - 1 if a color value could not be determined for some pixel
 *         .
 *         [option CHECK_NULLPTR] status may be NULL
 *  @param color Color index array, stored one row at time \n
 *         (-1)	indicates that a color index could not be determined for that
 *         particular pixel
 *
 *  @since all VDI versions
 *
 * Color indices are
 * returned one row at a time, starting from the
 * top of the rectangular area, proceeding
 * downward.
 *
 *
 */

void
vq_cellarray (short handle, short pxy[], short row_len, short nrows,
              short *el_used, short *rows_used, short *status, short color[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, pxy, color, vdi_dummy );
	
	vdi_control[7] = row_len;
	vdi_control[8] = nrows;

	VDI_TRAP (vdi_params, handle, 27, 2,0);

#if CHECK_NULLPTR
	if (el_used)
#endif
	*el_used   = vdi_control[9];
#if CHECK_NULLPTR
	if (rows_used)
#endif
	*rows_used = vdi_control[10];
#if CHECK_NULLPTR
	if (status)
#endif
	*status    = vdi_control[11];
}

