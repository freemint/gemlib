/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** copies a rectangular raster onto another rectangular 
 *  raster and performs the specified logic operations. Both rasters must be in 
 *  device-specific format or they must have only one plane.
 *
 *  @param handle Device handle
 *  @param mode logical operation
 *         - 0:  result=0
 *         - 1:  result=source and destination
 *         - 2:  result=source and (not destination)
 *         - 3:  result=source
 *         - 4:  result=(not source) and destination
 *         - 5:  result=destination (!)
 *         - 6:  result=source xor destination
 *         - 7:  result=source or destination
 *         - 8:  result=not (source or destination)
 *         - 9:  result=not (source xor destination)
 *         - 10: result=not destination
 *         - 11: result=source or (not destination)
 *         - 12: result=not source
 *         - 13: result=(not source) or destination
 *         - 14: result=not (source and destination)
 *         - 15: result=1
 *  @param pxy coordinates
 *         - xyarr[0..3]: coordinates of the source rectangle
 *         - xyarr[4..7]: coordinates of the destination rectangle
 *  @param src pointer to the source MFDB
 *  @param dst pointer to the destination MFDB
 *
 *  @since all VDI versions (extended since NVDI 4.10)
 *
 *  If the screen (or the device specified by <handle>) is the source or destination 
 *  of a raster operation, the MFDB structure element fd_addr should be zero!
 *  
 *  The clipping rectangle for the destination raster is enabled only if fd_addr of 
 *  the destination MFDB is zero.
 *
 *  The source rectangle will not be clipped (it must be within the raster area).
 *
 *  Note:\n
 *  Usually vro_cpyfm() ignores the height and width of the destination rectangle 
 *  and uses the size of the source. If you want to scale a bitmap, you have to 
 *  set the most significant bit in the transfer mode (wr_mode | 0x8000). In this
 *  case vro_cpyfm() scales the bitmap according to the size of the destination 
 *  rectangle. Wheter the driver is able to scale or not is returned by vq_extnd() 
 *  in work_out[30] (you are only allowed to set the upper bit of the mode if it 
 *  is able to).
 *
 */

void
vro_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, &mode, pxy, 0L, 0L);
#else
	vdi_params.ptsin = pxy;
	vdi_intin[0]     = mode;
#endif
	
	vdi_control_ptr(7) = src;
	vdi_control_ptr(9) = dst;
	
	VDI_TRAP (vdi_params, handle, 109, 4,1);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}
