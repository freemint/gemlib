#include "gem_aesP.h"


short
menu_settings (short me_flag, MN_SET * me_values)
{
	aes_intin[0]  = me_flag;
	aes_addrin[0] = (long)me_values;
	
	AES_TRAP (aes_params, 39, 1,1,1,0);
	
	return aes_intout[0];
}
