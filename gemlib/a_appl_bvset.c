
#include "gem.h"


short
appl_bvset (short bvdisk, short bvhard)
{
	aes_intin[0] = bvdisk;
	aes_intin[1] = bvhard;
	
	aes_control[0] = 16;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
