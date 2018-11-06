#include "gem_vdiP.h"

/** loads a device driver and opens a physical workstation. The 
 *  driver is loaded according to ASSING.SYS and the device is initialized with 
 *  parameters in the input array.
 *
 *  @param work_in work_in Meaning of work_in[0..10]:
 *         - work_in[0]: Device ID number. This value determines which
 *           device driver will be opened.
 *           - 1-10: Screen
 *           - ab 11: Plotter
 *           - ab 21: Printer
 *           - ab 31: Metafile
 *           - ab 41: Kamera
 *           - ab 51: Tablet
 *           - ab 61: Memory
 *         - work_in[1]: Line type
 *         - work_in[2]: Line color index
 *         - work_in[3]: Marker type
 *         - work_in[4]: Marker color index
 *         - work_in[5]: font id
 *         - work_in[6]: text color index
 *         - work_in[7]: fill interior style
 *         - work_in[8]: fill style index
 *         - work_in[9]: fill color index
 *         - work_in[10]:transformation flag 0: NDC , 2: RC
 *         .
 *         Meaning of work_in[11..15]:
 *         - work_in[11]:   page size
 *           -  PAGE_DEFAULT   (0)	  use default setting 
 *           -  PAGE_A3 	   (1)	  DIN A3 
 *           -  PAGE_A4 	   (2)	  DIN A4 
 *           -  PAGE_A5 	   (3)	  DIN A5 
 *           -  PAGE_B5 	   (4)	  DIN B5 
 *           -  PAGE_LETTER    (16)	  Letter size 
 *           -  PAGE_HALF	   (17)	  Half size 
 *           -  PAGE_LEGAL     (18)	  Legal size 
 *           -  PAGE_DOUBLE    (19)	  Double size 
 *           -  PAGE_BROAD     (20)	  Broad sheet size
 *         - work_in[12/13]: pointer to a GEMDOS file name (C string) or 0L
 *         - work_in[14]:    0, reserved
 *         - work_in[15]:    0, reserved
 *  @param handle before the call, \p handle should contain 0 or 1.
 *         after the call, \p handle will contain the handle of the
 *         physical workstation, or 0 if an error has occured.
 *  @param work_out Meaning of work_out[0..56]:
 *         - work_out[0]:  Maximum addressable width (0 - xmax)
 *         - work_out[1]:  Maximum addressable height (0 - ymax)
 *         - work_out[2]:  Device Coordinate units flag
 *           -  0: Device capable of producing a precisely scaled
 *                 image (e.g. screen)
 *           -  1: Device not capable of producing a precisely scaled 
 *                 image (e.g. film recorder)
 *         - work_out[3]:  Pixel width in microns
 *         - work_out[4]:  Pixel height in microns
 *         - work_out[5]:  Number of character heights (0: continous scaling)
 *         - work_out[6]:  Number of line types
 *         - work_out[7]:  Number of line widths (0: continous scaling)
 *         - work_out[8]:  Number of marker types
 *         - work_out[9]:  Number of marker heights (0: continous scaling)
 *         - work_out[10]: Number of accessible fonts
 *         - work_out[11]: Number of patterns
 *         - work_out[12]: Number of hatch styles
 *         - work_out[13]: Number of simultaneously displayed colors
 *              (e.g. 256 on an 8 bit screen)
 *         - work_out[14]: Number of GDPs
 *         - work_out[15] to work_out[24]:
 *              List of the supported GDPs. -1 indicates the end 
 *              of the list.
 *         - work_out[25] to work_out[34]:
 *              List of attributes associated with each GDP:
 *           -  0: Line
 *           -  1: Marker
 *           -  2: Text
 *           -  3: Fill area
 *           -  4: no attributes
 *         - work_out[35]: Color capability flag
 *         - work_out[36]: Text rotation capability flag
 *         - work_out[37]: Fill area capability falg
 *         - work_out[38]: CELLARRAY flag
 *         - work_out[39]: Number of color levels (0: more than 32767)
 *         - work_out[40]: Number of locator devices available
 *           -  1: Keyboard
 *           -  2: Keyboard and mouse (or other devices)
 *         - work_out[41]: Number of valuator devices available
 *           -  1: Keyboard
 *           -  2: another device is available
 *         - work_out[42]: Number of choice devices available
 *           -  1: Function keys
 *           -  2: another button pad
 *         - work_out[43]: Number of string devices available
 *           -  1: Keyboard
 *         - work_out[44]: Device type
 *           -  0: Output only
 *           -  1: Input only
 *           -  2: Input and Output
 *           -  4: Metafile output
 *         - work_out[45]: minimum character width
 *         - work_out[46]: minimum character height
 *         - work_out[47]: maximum character width
 *         - work_out[48]: maximum character height
 *         - work_out[49]: minimum line with
 *         - work_out[50]: 0
 *         - work_out[51]: maximum line width
 *         - work_out[52]: 0
 *         - work_out[53]: minimum marker width
 *         - work_out[54]: minimum marker height
 *         - work_out[55]: maximum marker width
 *         - work_out[56]: maximum marker height
 *
 *  @since all VDI versions
 *
 *  Important:  The screen driver is opened by the AES after all programs
 *              in the AUTO folder have been executed. Therefore applications
 *              have to call v_opnvwk()
 *
 *  If you open a NVDI printer or IMG driver, you can set the page size and
 *  the GEMDOS output device. The Metafile driver ignores the page size
 *  (it should be 0) but it uses the device name.
 */

void
v_opnwk (short work_in[], short *handle, short work_out[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, work_in, 0L, work_out, &work_out[45] );
	
	VDI_TRAP (vdi_params, *handle, 1, 0,11);

	*handle = vdi_control[6];
}

