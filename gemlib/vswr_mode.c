/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** selects the writing mode for graphic operations
 *
 *  @param handle Device handle
 *  @param mode requested writing mode. The writing mode specifies the
 *		   operation performed between
 *		   the color indices of the current pixel (source)
 *		   and the existing pixel (destination), thus
 *		   affecting the way new pixels from lines,
 *		   markers, filled areas, and text are placed on
 *		   the display. Four modes exist:
 *         - MD_REPLACE (1)
 *         - MD_TRANS (2)
 *         - MD_XOR (3)
 *         - MD_ERASE (4)
 *         .
 *         If you try toselect a mode number which is out of range,
 *         mode 1 (MD_REPLACE) will be selected.
 *
 *  @return selected writing mode
 *
 *  @since all VDI versions
 *
 *
 */

short
vswr_mode (short handle, short mode)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &mode, 0L, vdi_intout, 0L );
#else
	vdi_intin[0] = mode;
#endif

	VDI_TRAP (vdi_params, handle, 32, 0,1);

	return vdi_intout[0];
}
