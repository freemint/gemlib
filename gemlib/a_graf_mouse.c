#include "gem_aesP.h"


short
graf_mouse (short Form, const MFORM *FormAddress)
{
	aes_intin[0]  = Form;
	aes_addrin[0] = (long)FormAddress;
	
	AES_TRAP (aes_params, 78, 1,1,1,0);
	
	return aes_intout[0];
}
