/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns the address of an object loaded with mt_rsrc_load().
 *
 *  @param Type see below
 *  @param Index see below
 *  @param Address The pointer pointed to by \p Address will be filled in with the
 *         address of the \p Index th resource object of type \p Type. Valid
 *         values for type are as follows:<pre>
Name		 type  Resource Object
R_TREE  	  0    Object tree
R_OBJECT	  1    Individual object
R_TEDINFO	  2    TEDINFO structure
R_ICONBLK	  3    ICONBLK structure
R_BITBLK	  4    BITBLK structure
R_STRING	  5    Free String data
R_IMAGEDATA   6    Free Image data
R_OBSPEC	  7    ob_spec field within OBJECTs
R_TEPTEXT	  8    te_ptext within TEDINFOs
R_TEPTMPLT    9    te_ptmplt within TEDINFOs
R_TEPVALID    10   te_pvalid within TEDINFOs
R_IBPMASK	  11   ib_pmask within ICONBLKs
R_IBPDATA	  12   ib_pdata within ICONBLKs
R_IBPTEXT	  13   ib_ptext within ICONBLKs
R_BIPDATA	  14   bi_pdata within BITBLKs
R_FRSTR 	  15   Free string
R_FRIMG 	  16   Free image</pre>
 *  @param global_aes global AES array
 *
 *  @return The correct return value is 0 if an error occurred or
 *          non-zero if addr is valid.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_saddr()
 *
 *  This function is most often used to obtain the address of
 *  OBJECT trees, 'free' strings, and 'free' images after
 *  loading a resource file.
 */

short 
mt_rsrc_gaddr(short Type, short Index, void *Address, short *global_aes)
{
    AES_PARAMS(112,2,1,0,1);
                    
	aes_intin[0] = Type;
	aes_intin[1] = Index;

	AES_TRAP(aes_params);

	*((void **) Address) = (void *)aes_addrout[0];
	
	return aes_intout[0];
}

#ifdef rsrc_gaddr
#undef rsrc_gaddr
#endif
short 
rsrc_gaddr(short Type, short Index, void *Address)
{
	return( mt_rsrc_gaddr( Type, Index,Address, aes_global));
}


