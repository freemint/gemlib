
#include "gem.h"


int
shel_read (char *Command, char *Tail)
{
	aes_addrin[0] = (long) Command;
	aes_addrin[1] = (long) Tail;
	aes_control[0] = 120;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
