
#include "gem.h"


short
appl_control (short ap_cid, short ap_cwhat, void *ap_cout)
{
	aes_intin[0] = ap_cid;
	aes_intin[1] = ap_cwhat;
	
	aes_addrin[0] = (long) ap_cout;
	
	aes_control[0] = 129;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
