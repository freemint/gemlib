/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Text buffer
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param buf this pointer will be filled with the address of buffer \n
 *         [option CHECK_NULLPTR] buf may be NULL
 *  @param buflen this pointer will be filled with the buffer length \n
 *         [option CHECK_NULLPTR] buflen may be NULL
 *  @param txtlen this pointer will be filled with the current
 *         text length without EOS \n
 *         [option CHECK_NULLPTR] txtlen may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 for error, else 1
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 */

short 
mt_edit_get_buf( OBJECT *tree, short obj, char **buf, long *buflen,
				 long *txtlen, short *global_aes )
{
	AES_PARAMS(216,2,5,1,1);

	aes_intin[0]  = obj;
	aes_intin[1]  = 0;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (buf)
#endif
	*buf = (char *)aes_addrout[0];
#if CHECK_NULLPTR
	if (buflen)
#endif
	*buflen = *((long *) (aes_intout+1));
#if CHECK_NULLPTR
	if (txtlen)
#endif
	*txtlen = *((long *) (aes_intout+3));

	return(aes_intout[0]);
}
