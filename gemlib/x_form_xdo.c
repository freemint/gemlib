/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** provides an extended automated dialog handling function to
 *  the calling application
 *
 *  @param tree is a pointer to a valid object tree which contains
 *             a dialog with at least one #OF_EXIT or #OF_TOUCHEXIT button or
 *             object.
 *  @param startob is the object index into tree which specifies the
 *             desired initial location of the edit cursor (the object
 *             must be flagged as #OF_EDITABLE). If the form has no text
 *             editable fields, you should use 0.
 *  @param lastcrsr will contain the index of the editable field in which the
 *             edit cursor was when the function returned. \n
 *             [option CHECK_NULLPTR] lastcrsr may be NULL
 *  @param tabs pointer on keyboard tables, or NULL.
 *  @param flydial parameter \a *flydial returned by mt_form_xdial() with #FMD_START
 *           command.
 *  @param global_aes global AES array
 *
 *  @return the object index of the #OF_EXIT or #OF_TOUCHEXIT
 *             button which was selected.
 *
 *  @since MagiC 2.0. The presence of the flydials, the keyboard tables and the possibility
 *         of inquiring the last cursor position can be checked by calling mt_appl_getinfo()
 *         with parameter #AES_FORM.
 *
 */

short 
mt_form_xdo(OBJECT *tree, short startob, short *lastcrsr, XDO_INF *tabs, void *flydial, short *global_aes)
{
	AES_PARAMS(50,1,2,3,0);
                    
	aes_intin[0] = startob;
	
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)tabs;
	aes_addrin[2] = (long)flydial;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (lastcrsr)
#endif
	*lastcrsr = aes_intout[1];
	
	return aes_intout[0];
}
