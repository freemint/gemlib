
#include "gem.h"


int
menu_settings (int me_flag, MN_SET * me_values)
{
	aes_intin[0] = me_flag;
	aes_addrin[0] = (long) me_values;
	aes_control[0] = 39;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
