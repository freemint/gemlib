/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns a string from the keyboard. "INPUT STRING, SAMPLE MODE" 
 *  returns if the maximum string length is reached, if the user has pressed RETURN 
 *  or if the user has not pressed a key.
 *
 *  @param handle Device handle
 *  @param len is the maximum length of the string returned in intout. If max_length 
 *         is negative, the absolute value is considered to be the maximum length and scan 
 *         codes are returned instead of ASCII values.
 *  @param echo 0: no output 1: echo
 *  @param echoxy 
 *  @param str input buffer
 *
 *  @return 0 (no input) or the length of the string otherwise.

 *
 *  @since all VDI versions
 *
 */

short
vsm_string (short handle, short len, short echo, short echoxy[], char *str)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_ptsin[2];   
	short vdi_intout[VDI_INTOUTMAX]; 
	
	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_intout, vdi_dummy );
	
	vdi_intin[0]      = len;
	vdi_intin[1]      = echo;
	*(long*)vdi_ptsin = *(long*)echoxy;
	
	VDI_TRAP (vdi_params, handle, 31, 1,2);
	
	vdi_array2str (vdi_intout, str, vdi_control[4]);
	
	return vdi_control[4];
}
