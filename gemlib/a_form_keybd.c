/*
 *  $Id$
 */

#include "gem_aesP.h"

/** processes keyboard input for dialog box control.
 *
 *  @param tree points to a valid #OBJECT tree containing the dialog
 *               you wish to process.
 *  @param object is the object index of the object
 *               which currently has edit focus (0 if none).
 *  @param reserved should be 1.
 *  @param key is the value returned from mt_evnt_keybd() or mt_evnt_multi()
 *               which represents the keypresses' scan code and ASCII
 *               value.
 *  @param nextobject is a WORD pointer which is filled in on function
 *               exit to be the new object with edit focus unless the return
 *               key was pressed with a default object present in which case
 *               it equals the object index of the object that was the
 *               default. \n
 *             [option CHECK_NULLPTR] nextobject may be NULL
 *  @param nextchar is the value ready to be passed on to mt_objc_edit()
 *               if no processing was required or 0 if the key was processed
 *               and handled by the call. \n
 *             [option CHECK_NULLPTR] nextchar may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if a default #OF_EXIT object was
 *          triggered by this call or 1 if the dialog should continue
 *          to be processed.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_edit(), mt_form_do(), mt_form_button()
 *
 *  It handles special keys such as return, escape,
 *  tab, etc... It is only of real use if you are writing
 *  a customized mt_form_do() routine.
 *
 *  @note This function was not originally documented by Atari.
 *
 */

short
mt_form_keybd(OBJECT *tree, short object, short reserved, short key, short *nextobject, short *nextchar, short *global_aes)
{
	AES_PARAMS(55,3,3,1,0);

	aes_addrin[0] =(long) tree;
	aes_intin[0] = object;
	aes_intin[1] = key;
	aes_intin[2] = reserved;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (nextobject)
#endif
	*nextobject = aes_intout[1];
#if CHECK_NULLPTR
	if (nextchar)
#endif
	*nextchar = aes_intout[2];

	return aes_intout[0];
}
