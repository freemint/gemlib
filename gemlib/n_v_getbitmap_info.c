/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns a pointer to a character's bitmap and provides information 
 *  about the character placement and its size.
 *
 *  @param handle Device handle
 *  @param ch Zeichen-Index
 *  @param advancex x advance in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] advancex may be NULL
 *  @param advancey y advance in 1/65536 pixels\n
 *         The advance vector represents the offset for the placement of the next character. \n
 *         [option CHECK_NULLPTR] advancey may be NULL
 *  @param xoffset x offset in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] xoffset may be NULL
 *  @param yoffset y offset in 1/65536 pixels\n
 *         x_offset and y_offset are the offset of the bitmap relative to the position of 
 *         the character cell. This offset is necessary because most bitmaps are smaller than 
 *         the character cell. \n
 *         [option CHECK_NULLPTR] yoffset may be NULL
 *  @param width bitmap width in pixels \n
 *         [option CHECK_NULLPTR] width may be NULL
 *  @param height bitmap height in pixels \n
 *         [option CHECK_NULLPTR] height may be NULL
 *  @param bitmap pointer to the bitmap \n
 *         [option CHECK_NULLPTR] bitmap may be NULL
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  You should switch off text effects before you call v_getbitmap_info().
 *
 *  In general the pointer to the bitmap points into the character cache and therefore 
 *  you should immediately copy the bitmap (and lock the aes context switch by calling 
 *  wind_update()) - otherwise the pointer could be invalid.
 *  
 *  You should not use this function to write your own text output function - this 
 *  function would not be faster than v_ftext() and you would not be able to do pair 
 *  kerning. Use v_ftext()!
 *  
 */

void
v_getbitmap_info (short handle, short ch, long *advancex, long *advancey,
                  long *xoffset, long *yoffset, short *width, short *height,
                  short **bitmap)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[12]; 
	VDI_PARAMS(vdi_control, &ch, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = ch;
#endif
		
	VDI_TRAP (vdi_params, handle, 239, 0,1);
	
#if CHECK_NULLPTR
	if (width)
#endif
	*width    = vdi_intout     [0];
#if CHECK_NULLPTR
	if (height)
#endif
	*height   = vdi_intout     [1];
#if CHECK_NULLPTR
	if (advancex)
#endif
	*advancex = vdi_intout_long(2);
#if CHECK_NULLPTR
	if (advancey)
#endif
	*advancey = vdi_intout_long(4);
#if CHECK_NULLPTR
	if (xoffset)
#endif
	*xoffset  = vdi_intout_long(6);
#if CHECK_NULLPTR
	if (yoffset)
#endif
	*yoffset  = vdi_intout_long(8);
#if CHECK_NULLPTR
	if (bitmap)
#endif
	*bitmap   = (short*)vdi_intout_long(10);
}
