/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param xscroll  \n
 *         [option CHECK_NULLPTR] xscroll may be NULL
 *  @param yscroll  \n
 *         [option CHECK_NULLPTR] yscroll may be NULL
 *  @param cyscroll  \n
 *         [option CHECK_NULLPTR] cyscroll may be NULL
 *  @param cursorpos  \n
 *         [option CHECK_NULLPTR] cursorpos may be NULL
 *  @param cx  \n
 *         [option CHECK_NULLPTR] cx may be NULL
 *  @param cy  \n
 *         [option CHECK_NULLPTR] cy may be NULL
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 */

void 
mt_edit_get_pos( OBJECT *tree, short obj, short *xscroll, long *yscroll,
				 char **cyscroll, char **cursorpos, short *cx, short *cy, short *global_aes)
{
	AES_PARAMS(216,2,6,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 5;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (xscroll)
#endif
	*xscroll = aes_intout[1];
#if CHECK_NULLPTR
	if (yscroll)
#endif
	*yscroll = *((long *) (aes_intout+2));
#if CHECK_NULLPTR
	if (cyscroll)
#endif
	*cyscroll = (char *)aes_addrout[0];
#if CHECK_NULLPTR
	if (cx)
#endif
	*cx = aes_intout[4];
#if CHECK_NULLPTR
	if (cy)
#endif
	*cy = aes_intout[5];
#if CHECK_NULLPTR
	if (cursorpos)
#endif
	*cursorpos = (char *)aes_addrout[1];
}

