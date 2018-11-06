#include "gem_aesP.h"
#include "mt_gemx.h"

/** Allocate text buffer
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param buf specifies the Length of text buffer inclusive of closing Nullbyte.
 *  @param buflen is a pointer to the Text buffer. The text is present in
 *	       DOS format with CR/LF as line-end identifier and is terminated by a  
 *         Nullbyte.
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  The buffer is allocated to the text object, the number of lines are 
 *  determined. The cursor is set to the start of the text.
 *  This call clears the Dirty flag.
 *
 */

void 
mt_edit_set_buf( OBJECT *tree, short obj, char *buf, long buflen, short *global_aes)
{
	AES_PARAMS(217,4,0,2,0);

	aes_intin[0] = obj;
	aes_intin[1] = 0;
	*(long *) (aes_intin+2) = buflen;
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)buf;

	AES_TRAP(aes_params);
}

