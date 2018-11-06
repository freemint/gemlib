#include "gem_aesP.h"

/** see mt_graf_growbox()
 *
 *  @param in starting rectangle (where the outline will grow from).
 *  @param out ending rectangle (where the outline will grow to).
 *  @param global_aes global AES array
 *
 *  @return  see mt_graf_growbox()
 *
 *  @since  see mt_graf_growbox()
 *
 *
 */

short
mt_graf_growbox_grect( const GRECT *in, const GRECT *out, short *global_aes)
{
	AES_PARAMS(73,8,1,0,0);

	*(GRECT*)(aes_intin  ) = *in;
	*(GRECT*)(aes_intin+4) = *out;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
