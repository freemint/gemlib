
#include "gemx.h"


void *
fslx_do (char *title, char *path, short pathlen, char *fname, short fnamelen,
	 char *patterns, XFSL_FILTER filter, char *paths, short *sort_mode,
	 short flags, short *button, short *nfiles, char **pattern)
{
	aes_intin[0] = pathlen;
	aes_intin[1] = fnamelen;
	aes_intin[2] = *sort_mode;
	aes_intin[3] = flags;
	aes_addrin[0] = (long) title;
	aes_addrin[1] = (long) path;
	aes_addrin[2] = (long) fname;
	aes_addrin[3] = (long) patterns;
	aes_addrin[4] = (long) filter;
	aes_addrin[5] = (long) paths;
	aes_control[0] = 194;
	aes_control[1] = 4;
	aes_control[2] = 4;
	aes_control[3] = 6;
	aes_control[4] = 2;
	aes (&aes_params);
	*button = aes_intout[1];
	*nfiles = aes_intout[2];
	*sort_mode = aes_intout[3];
	*pattern = (char *) aes_addrout[1];
	return (void *) aes_addrout[0];
}
