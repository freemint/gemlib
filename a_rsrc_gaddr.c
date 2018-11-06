#include "gem_aesP.h"

/** returns the address of an object loaded with mt_rsrc_load().
 *
 *  @param Type see below
 *  @param Index see below
 *  @param Address The pointer pointed to by \a Address will be filled in with the
 *         address of the \a Index -th resource object of type \a Type. Valid
 *         values for \a Type are:
 *         - #R_TREE
 *         - #R_OBJECT	  
 *         - #R_TEDINFO	  
 *         - #R_ICONBLK	  
 *         - #R_BITBLK	  
 *         - #R_STRING	  
 *         - #R_IMAGEDATA  
 *         - #R_OBSPEC	  
 *         - #R_TEPTEXT	  
 *         - #R_TEPTMPLT   
 *         - #R_TEPVALID   
 *         - #R_IBPMASK	  
 *         - #R_IBPDATA	  
 *         - #R_IBPTEXT	  
 *         - #R_BIPDATA	  
 *         - #R_FRSTR 	  
 *         - #R_FRIMG 	 
 *         . 
 *         [option CHECK_NULLPTR] \a Address may be NULL
 *  @param global_aes global AES array
 *
 *  @return The correct return value is 0 if an error occurred or
 *          non-zero if \a Address is valid.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_saddr()
 *
 *  This function is most often used to obtain the address of
 *  OBJECT trees (#R_TREE), 'free' strings (#R_FRSTR), and 'free'
 *  images (#R_FRIMG) after loading a resource file.
 */

short 
mt_rsrc_gaddr(short Type, short Index, void *Address, short *global_aes)
{
    AES_PARAMS(112,2,1,0,1);
                    
	aes_intin[0] = Type;
	aes_intin[1] = Index;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (Address)
#endif
	*((void **) Address) = (void *)aes_addrout[0];
	
	return aes_intout[0];
}
