/*
 * Drag & drop sample code.
 * Copyright 1992 Atari Corporation
 *
 * global variables used:
 * gl_apid: our AES application id
 *
 * BUGS/CAVEATS:
 * This code is not re-entrant (it uses a static
 * variable for the pipe name and for saving the
 * SIGPIPE signal handler).
 *
 * While doing the drag and drop, the SIGPIPE
 * signal (write on an empty pipe) is ignored
 */

#include "dragdrop.h"


/*
 * ddopen: open a drag & drop pipe
 *
 * Input Parameters:
 * ddnam:       the pipe's name (from the last word of
 *              the AES message)
 * preferext:   a list of DD_NUMEXTS 4 byte extensions we understand
 *              these should be listed in order of preference
 *              if we like fewer than DD_NUMEXTS extensions, the
 *              list should be padded with 0s
 *
 * Output Parameters: none
 *
 * Returns:
 * A (positive) file handle for the drag & drop pipe, on success
 * -1 if the drag & drop is aborted
 * A negative error number if an error occurs while opening the
 * pipe.
 */
int
dd_open (int ddnam, char *preferext)
{
	int fd;
	char outbuf[DD_EXTSIZE + 1];

	__dragdrop_pipename[18] = ddnam & 0x00ff;
	__dragdrop_pipename[17] = (ddnam & 0xff00) >> 8;

	fd = (int) Fopen (__dragdrop_pipename, 2);
	if (fd < 0)
		return fd;

	outbuf[0] = DD_OK;
	strncpy (outbuf + 1, preferext, DD_EXTSIZE);

#ifdef __MINT__
	__dragdrop_oldpipesig = signal (SIGPIPE, SIG_IGN);
#else
	__dragdrop_oldpipesig = (long) Psignal (SIGPIPE, SIG_IGN);
#endif

	if (Fwrite (fd, (long) DD_EXTSIZE + 1, outbuf) != DD_EXTSIZE + 1)
	{
		dd_close (fd);
		return -1;
	}

	return fd;
}
