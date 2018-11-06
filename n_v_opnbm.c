#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function creates an offscreen bitmap on which can draw with VDI functions.
 *  You can pass a pointer to a bitmap or otherwise the VDI will allocate the memory 
 *  for it. The pixel sizes will be used to scale vector fonts, so that the aspect 
 *  ratio and the proportions will be correct.
 *
 *  @param work_in 
 *         - work_in[0..10]:   see v_opnwk()/v_opnvwk()
 *         - work_in[11]:      width -1 (e.g. 1279)
 *         - work_in[12]:      height -1 (e.g. 959)
 *         - work_in[13]:      pixel width in microns
 *         - work_in[14]:      pixel height in microns
 *         - work_in[15..19]:  must be 0 (!!) if you want to create a bitmap in 
 *                             device specific format
 *         .
 *         If the EdDI cookie has version number 1.1 or newer, v_opnbm() takes 
 *         additional arguments in work_in[15..19] into account:
 *         - work_in[15..16]:  number of simultaneously displayable colors
 *         - work_in[17]:      number of planes
 *         - work_in[18]:      pixel format
 *         - work_in[19]:      bit order
 *         .
 *         For a more detailed description of the pixel format and bit order see vq_scrninfo().
 *  @param bitmap pointer to the MFDB of the bitmap.\n
 *         If bitmap->fd_addr is zero, the VDI will 
 *         allocate memory for the bitmap according to the width an height in work_on
 *         (and the bitmap will be erased).\n
 *         To create a bitmap in device specific format, bitmap->fd_nplanes has to be 
 *         zero or the number of planes of the screen (returned by vq_extnd() in
 *         work_out[4]). If bitmap->fd_nplanes is 1, the VDI creates a monochrome 
 *         bitmap.\n
 *         The structure members of the MFDB (fd_addr, fd_w, fd_h, fd_wdwidth, fd_stand, 
 *         fd_nplanes) will be initialized by the VDI driver and returned to the calling 
 *         application. If there is not enough memory for the bitmap, the MFDB will not
 *         be changed and a zero-handle will be returned.\n
 *         If bitmap->fd_addr is a nonzero value, the VDI will use it as a pointer to 
 *         a bitmap and if the bitmap is in standard format, it will be transformed to 
 *         the device specific format.\n
 *         If v_opnbm() does not support the requested format of the bitmap (that means 
 *         the number of colors, planes and the organisation), a zero-handle will 
 *         indicate an error. 
 *  @param handle Device handle
 *  @param work_out 
 *
 *  @since since EdDI 1.00
 *
 *  If your redraw (of a window region) is very complex or time consuming and causes 
 *  a flickering on the screen, you should use an offscreen bitmap to create an image 
 *  and then you should copy it to the screen via vrt_cpyfm() or vro_cpyfm().
 *  
 *
 */

void
v_opnbm (short *work_in, MFDB *bitmap, short *handle, short *work_out)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, work_in, 0L, &work_out[0], &work_out[45]);
	
	vdi_control_ptr(0, MFDB *) = bitmap;

	VDI_TRAP_ESC (vdi_params, *handle, 100,1, 0,20);
	
	*handle = vdi_control[6];
}
