/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function generates a bezier curve of the specified character, which can be 
 *  used to call v_bez() or v_bez_fill().
 *
 *  @param handle Device handle
 *  @param ch character index
 *  @param xyarray coordinate buffer
 *  @param bezarray point-type buffer (jump, bez)
 *  @param maxverts maximum number of points
 *  @param numverts number of points
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  If you want to use the outline returned by v_getoutline() as vector graphic 
 *  (e.g. as part of a Metafile), you should select a sufficient character height.
 *  Otherwise the quality of the outline will be very poor, because v_getoutline() 
 *  has to round the internal fixed-point coordinates and returns only integer 
 *  values. The character height should refer to the resolution of the font outline 
 *  (returned by vqt_fontheader() in FH_ORUPM, e.g. 2048).
 *  
 *
 */

void
v_getoutline (short handle, short ch, short *xyarray, char *bezarray,
              short maxverts, short *numverts)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	VDI_PARAMS(vdi_control, vdi_intin, 0L, numverts, vdi_dummy);
#endif
	
	vdi_intin    [0] = ch;
	vdi_intin    [1] = maxverts;
	vdi_intin_ptr(2) = xyarray;
	vdi_intin_ptr(4) = bezarray;
	
	VDI_TRAP (vdi_params, handle, 243, 0,6);
	
#if !(USE_LOCAL_VDIPB)
	*numverts = vdi_intout[0];
#endif
}
