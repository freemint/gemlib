
#include "gem.h"


int
fsel_input (char *path, char *file, int *exit_but)
{
	aes_addrin[0] = (long) path;
	aes_addrin[1] = (long) file;
	aes_control[0] = 90;
	aes_control[1] = 0;
	aes_control[2] = 2;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	*exit_but = aes_intout[1];
	return aes_intout[0];
}
