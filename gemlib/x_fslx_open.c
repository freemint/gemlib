#include "gem_aesP.h"
#include "gemx.h"


void *
fslx_open (char *title, short x, short y, short *handle, char *path, short pathlen,
	   char *fname, short fnamelen, char *patterns, XFSL_FILTER filter,
	   char *paths, short sort_mode, short flags)
{
	aes_intin[0] = x;
	aes_intin[1] = y;
	aes_intin[2] = pathlen;
	aes_intin[3] = fnamelen;
	aes_intin[4] = sort_mode;
	aes_intin[5] = flags;
	aes_addrin[0] = (long) title;
	aes_addrin[1] = (long) path;
	aes_addrin[2] = (long) fname;
	aes_addrin[3] = (long) patterns;
	aes_addrin[4] = (long) filter;
	aes_addrin[5] = (long) paths;
	aes_control[0] = 190;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 6;
	aes_control[4] = 1;
	aes (&aes_params);
	*handle = aes_intout[0];
	return (void *) aes_addrout[0];
}
