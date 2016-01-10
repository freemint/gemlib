/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** converts \p src_index according to the encodings \p src_mode 
 *  and \p dst_mode. If it is not possible to convert an index, \p dst_index will 
 *  be 0xffff.
 *
 *  @param handle Device handle
 *  @param scr_index 
 *  @param scr_mode Mapping of \a src_index
 *         - 0: \p src_index is a direct index
 *         - 1: \p src_index is an ASCII index 
 *         - 2: \p src_index is a unicode index
 *  @param dst_mode Mapping of \a dst_index
 *         - 0: \p dst_index is a direct index
 *         - 1: \p dst_index is an ASCII index 
 *         - 2: \p dst_index is a unicode index
 *
 *  @return dst_index
 *
 *  @since NVDI 4.00
 *
 *  @note
 *  If you want to convert an index from ASCII to ASCII, only the range from 32 
 *  to 255 is used. The control codes are not translated, e.g. a call like 
 *  vqt_char_index( handle, 10, 1, 0 ) returns 0xffff.
 *  
 *  For example, to determine if the font contains a character with 
 *  unicode 0x201e ("quotedblbase", DOUBLE LOW-9 QUOTATION MARK ), you should 
 *  use the following function:
 *
\verbatim  
WORD  is_char_available( WORD handle, UWORD unicode )
{
   UWORD direct_index;
   
   // translate <unicode> into a direct index 
   direct_index = vqt_char_index( handle, unicode, 2, 0 );
   
   if ( direct_index == 0xffff )
      return( 0 );                     // character is available
   else
      return( 1 );                     // not available
}
\endverbatim  
 *  
 */

short
vqt_char_index (short handle, short scr_index, short scr_mode, short dst_mode)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	vdi_intin[0] = scr_index;
	vdi_intin[1] = scr_mode;
	vdi_intin[2] = dst_mode;
	
	VDI_TRAP (vdi_params, handle, 190, 0,3);
	
	return vdi_intout[0];
}
