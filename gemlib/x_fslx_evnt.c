
#include "gemx.h"


short
fslx_evnt (void *fsd, EVNT * events, char *path, char *fname, short *button,
	   short *nfiles, short *sort_mode, char **pattern)
{
	aes_addrin[0] = (long) fsd;
	aes_addrin[1] = (long) events;
	aes_addrin[2] = (long) path;
	aes_addrin[3] = (long) fname;
	aes_control[0] = 193;
	aes_control[1] = 0;
	aes_control[2] = 4;
	aes_control[3] = 4;
	aes_control[4] = 1;
	aes (&aes_params);
	*button = aes_intout[1];
	*nfiles = aes_intout[2];
	*sort_mode = aes_intout[3];
	*pattern = (char *) aes_addrout[0];
	return aes_intout[0];
}
