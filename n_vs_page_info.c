#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function should be used to change the information about a document.
 *  They will be wrote to the job printing history as well as to the log file 
 *  when printing.
 *
 *  @param handle Device handle
 *  @param type kind of info
 *         - 0 (APPL):  application name
 *         - 1 (DOC):   document title
 *         - 2 (CREAT): author name
 *         - 3 (REM):   comment
 *  @param txt text to send (max 60 characters, including null-byte)
 *
 *  @return 0 if this function is not supported by the driver, any other value if
 *          the driver support this function. 
 * 
 * 
 *  @since depend of the driver
 *
 */

short vs_page_info(short handle, short type, const char txt[60])
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[1];
	short vdi_intin[62];
	short i;

	VDI_PARAMS (vdi_control, vdi_intin, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intin[0] = type;
	i = vdi_str2array_n(txt, &vdi_intin[1], 60) + 1;
	vdi_intin[i++] = '\0';
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2103, 0, i);
	
	return vdi_intout[0];
}
