
#include "gem.h"


short
wind_calc_grect (short Type, short Parts, GRECT *In, GRECT *Out)
{
	aes_intin[0] = Type;
	aes_intin[1] = Parts;
	aes_intin[2] = In->g_x;
	aes_intin[3] = In->g_y;
	aes_intin[4] = In->g_w;
	aes_intin[5] = In->g_h;
	
	aes_control[0] = 108;
	aes_control[1] = 6;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	Out->g_x = aes_intout[1];
	Out->g_y = aes_intout[2];
	Out->g_w = aes_intout[3];
	Out->g_h = aes_intout[4];
	
	return aes_intout[0];
}
