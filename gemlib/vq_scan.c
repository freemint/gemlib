/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param g_slice  \n
 *         [option CHECK_NULLPTR] g_slice may be NULL
 *  @param g_page  \n
 *         [option CHECK_NULLPTR] g_page may be NULL
 *  @param a_slice  \n
 *         [option CHECK_NULLPTR] a_slice may be NULL
 *  @param a_page  \n
 *         [option CHECK_NULLPTR] a_page may be NULL
 *  @param div_fac  \n
 *         [option CHECK_NULLPTR] div_fac may be NULL
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vq_scan (short handle, short *g_slice, short *g_page,
         short *a_slice, short *a_page, short *div_fac)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[5]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,24, 0,0);
	
#if CHECK_NULLPTR
	if (g_slice)
#endif
	*g_slice = vdi_intout[0];
#if CHECK_NULLPTR
	if (g_page)
#endif
	*g_page  = vdi_intout[1];
#if CHECK_NULLPTR
	if (a_slice)
#endif
	*a_slice = vdi_intout[2];
#if CHECK_NULLPTR
	if (a_page)
#endif
	*a_page  = vdi_intout[3];
#if CHECK_NULLPTR
	if (div_fac)
#endif
	*div_fac = vdi_intout[4];
}
