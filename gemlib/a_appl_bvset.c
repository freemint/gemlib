#include "gem_aesP.h"


short
appl_bvset (short bvdisk, short bvhard)
{
	aes_intin[0] = bvdisk;
	aes_intin[1] = bvhard;
	
	AES_TRAP (aes_params, 16, 2,1,0,0);
	
	return aes_intout[0];
}
