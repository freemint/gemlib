
#include "gem.h"


short
wind_open_grect (short WindowHandle, GRECT *r)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = r->g_x;
	aes_intin[2] = r->g_y;
	aes_intin[3] = r->g_w;
	aes_intin[4] = r->g_h;
	
	aes_control[0] = 101;
	aes_control[1] = 5;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
