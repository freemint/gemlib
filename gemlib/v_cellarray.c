/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** With the Cell Array function, the device draws a
 *	rectangular array defined by the input
 *	parameter (x,y) coordinates and the color index
 *	array. The lower left and upper right
 *	coordinates define the extent of the rectangle.
 *	GEM VDI divides the rectangle into cells based
 *	on the number of rows and columns specified as
 *	input parameters. The color index array
 *	specifies the color for each cell.
 *
 *  @param handle Device handle
 *  @param pxy
 *  @param row_length Length of each row in color
 *		   index array(size as declared
 *		   in a high-level language).
 *  @param elements Number of elements used in each
 *		   row of color index array
 *  @param nrows Number of rows in color index
 *		   array.
 *  @param write_mode Pixel operation to be performed
 *  @param colarray Color index array, stored by row.
 *
 *  @since all VDI versions
 *
 *  Each cell of the rectangle is mapped to pixels
 *  on the display surface. The pixel takes the
 *  color of the cell that covers its center.
 *
 *  If the device does not support cell arrays, the
 *  device outlines the area with a solid line in
 *  the current line color and line width.
 *
 *  Note: This function is not required and may
 *  not be available on all devices.
 *
 */

void
v_cellarray (short handle, short pxy[], short row_length, short elements,
             short nrows, short write_mode, short colarray[])
{
	register short n = row_length * nrows;
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, colarray, pxy, vdi_dummy, vdi_dummy );
#endif
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = colarray;
	vdi_params.ptsin = pxy;
#endif
	
	vdi_control[7]  = row_length;
	vdi_control[8]  = elements;
	vdi_control[9]  = nrows;
	vdi_control[10] = write_mode;
	VDI_TRAP (vdi_params, handle, 10, 2,n);
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
	vdi_params.ptsin = vdi_ptsin;
#endif
}
