/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Alter settings: Font
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param font_id specifies the Font-ID
 *  @param font_h specifies the Character height in "points"
 *  @param font_pix specifies the font size unit (0=points, 1=pixels) (available from 3.5.98 on)
 *  @param mono specifies the "Equidistant" flag
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  If the editable object was opened previously, then one should generally 
 *  trigger a redraw when changing the font.
 *  The " \p mono " flag is required to give the editable object the possibility to 
 *  handle equidistant fonts (\p mono == 1) appreciably faster that proportional
 *  fonts (\p mono == 0).
 *  \p font_pix is only available from version 8 of the SLB onwards. Older versions 
 *  always assume \p font_pix=0, i.e. exclusiely use vst_point() for setting the 
 *  character height.
 *  
 */

void 
mt_edit_set_font( OBJECT *tree, short obj, short font_id, short font_h,
                  short font_pix, short mono, short *global_aes )
{
	AES_PARAMS(217,6,0,1,0);

	aes_intin[0] = obj;
	aes_intin[1] = 3;
	aes_intin[2] = font_id;
	aes_intin[3] = font_h;
	aes_intin[4] = mono;
	aes_intin[5] = font_pix;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);
}
