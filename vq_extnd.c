#include "gem_vdiP.h"

/** This function either returns the output arguments of v_opnwk()/v_opnvwk() or 
 *  additional device-specific information.
 *
 *  @param handle Device handle
 *  @param flag information type
 *         - 0: return v_opnwk()/v_opnvwk() values
 *         - 1: return additional information
 *  @param work_out 
 *         - work_out[0]:  type of screen
 *           - 0: no screen
 *           - 1: separate alpha and graphic controllers and
 *                separate video memory
 *           - 2: separate alpha and graphic controllers with
 *                shared video memory
 *           - 3: common video an graphic controller with 
 *                separate video memory
 *           - 4: common alpha and graphic controller with
 *                shared video memory
 *         - work_out[1]:  number of color levels (refers to the CLUT)
 *         - work_out[2]:  supported text effects
 *         - work_out[3]:  raster scaling flag
 *           - 0: scaling impossible
 *           - 1: scaling possible
 *         - work_out[4]:  number of planes
 *         - work_out[5]:  CLUT flag
              0: no CLUT
              1: CLUT or pseudo-CLUT (true color) exists
 *         - work_out[6]:  performance factor
 *         - work_out[7]:  contour fill capability (v_contourfill)
 *           - 0: not supported
 *           - 1: contour fill supported
 *         - work_out[8]:  text rotation ability
 *           - 0: none
 *           - 1: in steps of 90 degree only
 *           - 2: in steps of 1/10 degree
 *         - work_out[9]:  number of writing modes
 *         - work_out[10]: available input levels
 *           - 0: none
 *           - 1: request
 *           - 2: request and sample
 *         - work_out[11]: text alignment flag
 *           - 0: not available
 *           - 1: available
 *         - work_out[12]: inking capability flag
 *           - 0: device cannot ink
 *           - 1: device can ink
 *         - work_out[13]: rubberbanding capability flag
 *           - 0: no
 *           - 1: capable of rubberband lines
 *           - 2: capable of rubberband lines and rectangles
 *         - work_out[14]: maximum number of input vertices or -1 (unlimited)
 *         - work_out[15]: maximum number of intin arguments or -1 (no limit)
 *         - work_out[16]: number of mouse keys
 *         - work_out[17]: line types for wide lines
 *           - 0: no
 *           - 1: yes
 *         - work_out[18]: number fo writing modes for wide lines
 *         - work_out[19]: clipping flag
 *           - 0: clipping off
 *           - 1: clipping on
 *         - work_out[20]: 0: extend precision pixel size information is not available
 *           - 1: pixel size is in 1/10 microns
 *           - 2: pixel size is in 1/100 microns
 *           - 3: pixel size is in 1/1000 microns
 *         - work_out[21]: pixel width in 1/10, 1/100 or 1/1000 microns
 *         - work_out[22]: pixel height in 1/10, 1/100 or 1/1000 microns
 *         - work_out[23]: horizontal resolution in dpi
 *         - work_out[24]: vertical resolution in dpi
 *         - work_out[28]: bezier flag (bit 1)
 *           - 0: driver has not bezier capability
 *           - 1: driver has bezier capability
 *         - work_out[30]: raster flag (bit 0)
 *           - 0: no scaling              
 *           - 1: vrt/vro_cpyfm() is capable of scaling bitmaps
 *         - work_out[40]: not imprintable left border in pixels (printers/plotters)
 *         - work_out[41]: not imprintable upper border in pixels (printers/plotters)
 *         - work_out[42]: not imprintable right border in pixels (printers/plotters)
 *         - work_out[43]: not imprintable lower border in pixels (printers/plotters)
 *         - work_out[44]: page size (printers etc.), see v_opnwk()/vs_page_size()
 *         - work_out[45..48]: clipping rectangle
 *
 *  @since all VDI versions
 *
 *  Note:\n
 *  If work_out[20] contains a nonzero value, work_out[21..24] and work_out[40..43] 
 *  will contain extended information about pixel size and not imprintable borders.
 *  Usually margins only are returned for printer drivers due to mechanical 
 *  limitations of the printer. Applications should take the margins into account 
 *  to center the document correctly and they should display the margins on screen.
 *  
 *  The addressable raster size returned by v_opnwk() (work_in[0/1]) is the area 
 *  that can be imprinted. That means the upper left corner (0,0) of the imprintable 
 *  page has a distance of (work_out[40], work_out[41]) pixels from the upper left 
 *  corner of the physical sheet of paper.
 *  
 *  If a driver returns more precise pixel sizes, this information should be used 
 *  to calculate the position of graphic objects for printing. In worst case using
 *  the values from v_opnwk() in work_out[3/4] can result in a positioning inaccuracy 
 *  of 2 or 3 mm (for output on a DIN A4 page).
 *  
 *  The original ATARI VDI does not return the clipping flag (work_out[19]), but it
 *  returns the clipping rectangle.
 *  
 *  You should not use the bezier flag (work_out[28]) to determine if the driver 
 *  is capable of generating bezier curves because some drivers have bezier 
 *  support but do not return the bezier flag. We recommend to use v_bez_on()!
 *  
 *
 *
 */

void
vq_extnd (short handle, short flag, short work_out[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, &flag, 0L, &work_out[0], &work_out[45] );
	
	VDI_TRAP (vdi_params, handle, 102, 0,1);
}
