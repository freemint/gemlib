#include "gem.h"


short
wind_get_grect (short WindowHandle, short What, GRECT *r)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	aes_control[0] = 104;
	aes_control[1] = 2;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*r = *(GRECT*)(aes_intout +1);
	
	return aes_intout[0];
}
