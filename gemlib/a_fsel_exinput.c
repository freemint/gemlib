
#include "gem.h"


short
fsel_exinput (char *path, char *file, short *exit_but, const char *title)
{
	aes_addrin[0] = (long) path;
	aes_addrin[1] = (long) file;
	aes_addrin[2] = (long) title;
	
	aes_control[0] = 91;
	aes_control[1] = 0;
	aes_control[2] = 2;
	aes_control[3] = 3;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*exit_but = aes_intout[1];
	
	return aes_intout[0];
}
