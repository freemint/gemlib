/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This call reports back the cell width for the specified character. If you 
 *  have selected a vector font, the returned cell width is a rounded value. 
 *  You can use this advance width for determing a character position when you 
 *  use v_gtext() but you cannot use it for v_ftext() output.
 *
 *  @param handle Device handle
 *  @param chr character index
 *  @param cw character cell width
 *  @param ldelta left character alignment delta
 *  @param rdelta right character alignment delta
 *
 *  @return character index or -1 (error)
 *
 *  @since all VDI versions
 *
 *  Note:\n
 *  To determine the width of a string, you should always call vqt_extent(), 
 *  vqt_f_extent() or vqt_real_extent().
 *  If you try to check whether a font is monospaced or proportional, you should 
 *  test if vqt_name() returns extend information.
 *
 */

short
vqt_width (short handle, short chr, short *cw, short *ldelta, short *rdelta)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	short vdi_ptsout[6]; 
	VDI_PARAMS(vdi_control, &chr, 0L, vdi_intout, vdi_ptsout );
#else
	vdi_intin[0] = chr;
#endif
	
	VDI_TRAP (vdi_params, handle, 117, 0,1);

	*cw     = vdi_ptsout[0];
	*ldelta = vdi_ptsout[2];
	*rdelta = vdi_ptsout[4];
	
	return vdi_intout[0];
}
