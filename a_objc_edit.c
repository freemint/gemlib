/*
 *  $Id$
 */

#include "gem_aesP.h"

/** allows manual control of an editable text field.
 *
 *  @param tree specifies the object tree containing the editable object
 *  @param object is the editable object to modify
 *  @param ch a character to insert, depending of \a kind. See below.
 *  @param index pointer to the index (cursor position of the editable object).
 *         See below.
 *  @param kind specifies the action of the call and the meaning of the other
 *         parameters as follows:
 *         - #ED_START (0) Reserved for future use. Do not call.
 *         - #ED_INIT  (1) Display the edit cursor in the object
 *                        specified. \a ch is ignored. The WORD pointed to
 *                        by \a index is filled in with the current index of
 *                        the edit cursor in the field.
 *         - #ED_CHAR  (2) A key has been pressed that needs special
 *                        processing. \a ch contains the keyboard scan
 *                        code in the high byte and ASCII code in the
 *                        low byte. \a index points to the current index of
 *                        the text cursor in the field. \a index will be
 *                        updated as a result of this call.
 *         - #ED_END   (3) Turn off the text cursor.
 *         - #ED_CRSR (100) TO BE COMPLETED (TODO)
 *         - #ED_DRAW (103) TO BE COMPLETED (TODO)
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_xedit(), mt_form_keybd()
 *
 *  This function is usually used in conjunction with
 *  mt_form_keybd() in a custom mt_form_do() handler.
 *
 */
 
short 
mt_objc_edit(OBJECT *tree, short object, short ch, short *index, short kind, short *global_aes)
{
	AES_PARAMS(46,4,2,1,0);
                    
	aes_intin[0]  = object;
	aes_intin[1]  = ch;
	aes_intin[2]  = *index;
	aes_intin[3]  = kind;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*index = aes_intout[1];
	
	return aes_intout[0];
}
