#include "gem.h"


short
wind_set_grect (short WindowHandle, short What, const GRECT * r)
{
	aes_intin[0]            = WindowHandle;
	aes_intin[1]            = What;
	*(GRECT*)(aes_intin +2) = *r;
	
	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
