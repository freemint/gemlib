
#include "gem.h"


short
graf_mouse (short Form, void *FormAddress)
{
	aes_intin[0] = Form;
	
	aes_addrin[0] = (long) FormAddress;
	
	aes_control[0] = 78;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
