
#include "gem.h"


void
wind_set_grect (short WindowHandle, short What, GRECT * r)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_intin[2] = r->g_x;
	aes_intin[3] = r->g_y;
	aes_intin[4] = r->g_w;
	aes_intin[5] = r->g_h;
	
	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
