#include "gem_aesP.h"

/** processes keyboard input for dialog box control.
 *
 *  @param tree points to a valid #OBJECT tree containing the dialog
 *              you wish to process.
 *  @param editfocus is the object index of the object
 *                   which currently has edit focus (0 if none).
 *  @param nextobj   When return value is 1 and keyout is not 0 to indicate
 *                 it was not used, the value in nextobj is passed back in
 *                 newobj. Setting both 'object' and 'nextobj' to the same
 *                 value is recomended, since then if editfocus change
 *                 happens, 'newobj' will be different from value passsed
 *                 in 'object'.
 *  @param key is the value returned from mt_evnt_keybd() or mt_evnt_multi()
 *             which represents the keypresses' scan code and ASCII
 *             value.
 *  @param newobj is a WORD pointer which can have two meanings :
 *                - first, depending on the value returned:
 *                   - If the the function returns 1, and the key passed
 *                      in 'key' is returned in 'keyout', (key not used)
 *                      then 'newobj' is filled with the value passed to
 *                      function in 'nextobj'. (See NOTE: below)\n
 *                   - If a 0 is returned in 'keyout', indicating that the
 *                      key used and the object acted on is not an "exit"
 *                      object (i.e. is not having #OF_EXIT or #OF_TOUCHEXIT
 *                      set), 'newobj' is filled in with the index of the
 *                      object which should get editfocus. If editfocus
 *                      didnt change, the index passed in 'editobj' is
 *                      returned.
 *                   .
 *                   Now it becomes clear why its recommended to set 'editobj'
 *                   and 'nextobj' to the same value. Either a new editfocus,
 *                   the same value as passed in 'editfocus' if key used and
 *                   editfocus didnt change, or the value passed in 'nextobj'
 *                   if key was not used.
 *                -  If the function returns 0, then object the key acted on
 *                   was an "exit" object, and 'newobj' contains the index of
 *                   that object. This happens if, for example, RETURN
 *                   is pressed to activate the default object. In this case
 *                   one have to manually check if the object is an editable
 *                   (#OF_EDITABLE), if one uses editables with #OF_EXIT or
 *                   #OF_TOUCHEXIT bit set, and set new editfocus accordingly
 *                   using mt_objc_edit().
 *                .
 *                NOTE: XaAES may return a new editfocus even if the key was not
 *                      used! This happens when the object whose index passed in
 *                      'editobj' is 0, or is not a valid editable object.
 *                      In this case XaAES returns the first valid editable
 *                      object it finds, if any. \n
 *             [option CHECK_NULLPTR] newobj may be NULL
 *  @param keyout is the value ready to be passed on to mt_objc_edit()
 *                if no processing was required or 0 if the key was processed
 *                and handled by the call. \n
 *             [option CHECK_NULLPTR] keyout may be NULL
 *  @param global_aes global AES array
 *
 *  @retval 0 if a default #OF_EXIT object was triggered by this call
 *  @retval 1 if the dialog should continue to be processed.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_edit(), mt_form_do(), mt_form_button()
 *
 *  XaAES implements a keyboard navigation system that is totally
 *  dependant on the usage of this function. Therefore, always let the
 *  AES get a chance to act on keypresses by calling this function when
 *  servicing a dialog!
 *
 *  @par Example code to correctly handle output form form_keybd()
@code
	// This code is based on always passing the current
	// editfocus in both 'editfocus' and 'nextobj', as this lets
	// us check for a change by using "if (newobj != editfocus)"
	// which is simple :) Read the section about 'nextobj' above
	// for more info!
	short newobj;
	short keyout;
	short idx;
 
	if (mt_form_keybd(tree, editfocus, editfocus, keycode, &newobj, &keyout, &globl))
	{
		// We dont check if a key is returned first. We know
		//  that "if (newobj != editfocus)", the editfocus did infact
		//  change.
		if (newobj != editfocus)
		{
			objc_edit(tree, editfocus, 0, 0, ED_END);
			objc_edit(tree, newobj, 0, &idx, ED_INIT);
			editfocus = newobj;
		}
		if (keyout)
		{
			objc_edit(tree, editfocus, keyout, &idx, ED_CHAR);
		}
	}
	else
	{
		// Since object is exit, we need to manually check if
		// it is also an editable object. This can be skipped if
		// you dont use objects where you have both #OF_EDITABLE and
		// #OF_EXIT or #OF_TOUCHEXIT set.
		if (newobj != editfocus && (tree[newobj].ob_flags & OF_EDITABLE))
		{
			objc_edit(tree, editfocus, 0, 0, ED_END);
			objc_edit(tree, newobj, 0, &idx, ED_INIT);
			editfocus = newobj;
		}
		
		// .... continue processing exit object ....
		  
	}
@endcode
 *
 * It handles special keys such as return, escape,
 * tab, etc... It is only of real use if you are writing
 * a customized mt_form_do() routine.
 *
 *
 *  @note This function was not originally documented by Atari.
 *
 */

short
mt_form_keybd(OBJECT *tree, short editfocus, short nextobj, short key, short *newobj, short *keyout, short *global_aes)
{
	AES_PARAMS(55,3,3,1,0);

	aes_addrin[0] =(long) tree;
	aes_intin[0] = editfocus;
	aes_intin[1] = key;
	aes_intin[2] = nextobj;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (newobj)
#endif
	*newobj = aes_intout[1];
#if CHECK_NULLPTR
	if (keyout)
#endif
	*keyout = aes_intout[2];

	return aes_intout[0];
}
