#include "gem_aesP.h"


short
appl_control (short ap_cid, short ap_cwhat, void *ap_cout)
{
	aes_intin[0]  = ap_cid;
	aes_intin[1]  = ap_cwhat;
	aes_addrin[0] = (long)ap_cout;
	
	AES_TRAP (aes_params, 129, 2,1,1,0);
	
	return aes_intout[0];
}
