#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree is a pointer to a valid object tree 
 *  @param x
 *  @param y coordinates around which the tree will be centered, or 0
 *         (the position of the tree is not changed).
 *  @param global_aes global AES array
 *
 *  @return the index of the object which has been clicked by the user
 *          to close the popup, or -1.
 *
 *  @since the availability of this function can be checked by calling
 *         mt_appl_getinfo() with the parameter #AES_MENU
 *
 *  Selectable objects of this dialog don't need to have the #OF_SELECTABLE
 *  flag set. If an object don't have to be selectable, then set the
 *  flag #OS_DISABLED.
 *
 *  The object type of the root object (index 0) shall be either #G_BOX or
 *  #G_IBOX.
 *
 *  @note  One shall ensure that the tree object fit entierely in the 
 *         screen.
 */

short 
mt_form_popup(OBJECT *tree, short x, short y, short *global_aes)
{
	AES_PARAMS(135,2,1,1,0);
                    
	aes_intin[0] = x;
	aes_intin[1] = y;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
