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

#include <mintbind.h>

#include "dragdrop.h"


/*
 * ddcreate: create a pipe for doing the drag & drop,
 *           and send an AES message to the receipient
 *           application telling it about the drag & drop
 *           operation.
 *
 * Input Parameters:
 * apid:        AES id of the window owner
 * winid:       target window (0 for background)
 * msx, msy:    mouse X and Y position
 *              (or -1, -1 if a fake drag & drop)
 * kstate:      shift key state at time of event
 *
 * Output Parameters:
 * exts:        A 32 byte buffer into which the
 *              receipient's 8 favorite
 *              extensions will be copied.
 *
 * Returns:
 * A positive file descriptor (of the opened
 * drag & drop pipe) on success.
 * -1 if the receipient doesn't respond or
 *    returns DD_NAK
 * -2 if appl_write fails
 */
int
dd_create (int apid, int winid, int msx, int msy, int kstate, char *exts)
{
	int fd, i;
	short msg[8];
	long fd_mask;
	char c;

	__dragdrop_pipename[17] = __dragdrop_pipename[18] = 'A';
	fd = -1;
	do
	{
		__dragdrop_pipename[18]++;
		if (__dragdrop_pipename[18] > 'Z')
		{
			__dragdrop_pipename[17]++;
			if (__dragdrop_pipename[17] > 'Z')
				break;
		}
		/* FA_HIDDEN means "get EOF if nobody has pipe open for reading" */
		fd = (int) Fcreate (__dragdrop_pipename, FA_HIDDEN);
	}
#ifdef __MINT__
	while (fd == -EACCES || fd == -EPERM);
#else
	while (fd == EACCDN)
#endif

	if (fd < 0)
		return fd;

	/* construct and send the AES message */
	msg[0] = AP_DRAGDROP;
	msg[1] = gl_apid;
	msg[2] = 0;
	msg[3] = winid;
	msg[4] = msx;
	msg[5] = msy;
	msg[6] = kstate;
	msg[7] = (__dragdrop_pipename[17] << 8) | __dragdrop_pipename[18];
	i = appl_write (apid, (int) sizeof (msg), msg);
	if (i == 0)
	{
		Fclose (fd);
		return -2;
	}

	/* now wait for a response */
	fd_mask = 1L << fd;
	i = Fselect (DD_TIMEOUT, &fd_mask, 0L, 0L);
	if (!i || !fd_mask)	/* timeout happened */
	{
		Fclose (fd);
		return -1;
	}

	/* read the 1 byte response */
	i = (int) Fread (fd, 1L, &c);
	if (i != 1 || c != DD_OK)
	{
		Fclose (fd);
		return -1;
	}

	/* now read the "preferred extensions" */
	i = (int) Fread (fd, DD_EXTSIZE, exts);
	if (i != DD_EXTSIZE)
	{
		Fclose (fd);
		return -1;
	}

#ifdef __MINT__
	__dragdrop_oldpipesig = signal (SIGPIPE, SIG_IGN);
#else
	__dragdrop_oldpipesig = (long) Psignal (SIGPIPE, SIG_IGN);
#endif
	return fd;
}
