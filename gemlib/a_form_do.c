/*
 *  $Id$
 */

#include "gem_aesP.h"

/** provides an automated dialog handling function to
 *  the calling application.
 *
 *  @param tree is a pointer to a valid object tree which contains
 *             a dialog with at least one EXIT or TOUCHEXIT button or
 *             object.
 *  @param startobj is the object index into tree which specifies the
 *             desired initial location of the edit cursor (the object
 *             must be flagged as EDITABLE). If the form has no text
 *             editable fields, you should use 0.
 *  @param global_aes global AES array
 *
 *  @return the object index of the EXIT or TOUCHEXIT
 *             button which was selected. If the object was double
 *             clicked, the top bit will be set. This means that to
 *             obtain the actual object number you should mask it
 *             out with 0x7FFF.
 *
 *  @since All AES versions.
 *
 *  It suspends program control,
 *  handles all radio buttons, selectable objects, etc...
 *  until an object with the TOUCHEXIT or EXIT flag is selected.
 *
 */

short
mt_form_do(OBJECT *tree, short startobj, short *global_aes)
{
	AES_PARAMS(50,1,1,1,0);

	aes_intin[0] = startobj;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef form_do
#undef form_do
#endif
short
form_do(OBJECT *tree, short startobj)
{
	return(mt_form_do(tree, startobj, aes_global));
}
