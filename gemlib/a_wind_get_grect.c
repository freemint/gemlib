
#include "gem.h"


void
wind_get_grect (int WindowHandle, int What, GRECT * r)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_control[0] = 104;
	aes_control[1] = 2;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	r->g_x = aes_intout[1];
	r->g_y = aes_intout[2];
	r->g_w = aes_intout[3];
	r->g_h = aes_intout[4];
}
