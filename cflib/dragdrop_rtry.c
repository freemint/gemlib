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

#ifdef __MINT__
  #include <osbind.h>
#else
  #include <tos.h>
#endif

#include "dragdrop.h"


/*
 * ddrtry: get the next header from the drag & drop originator
 *
 * Input Parameters:
 * fd:          the pipe handle returned from ddopen()
 *
 * Output Parameters:
 * name:        a pointer to the name of the drag & drop item
 *              (note: this area must be at least DD_NAMEMAX bytes long)
 * whichext:    a pointer to the 4 byte extension
 * size:        a pointer to the size of the data
 *
 * Returns:
 * TRUE on success
 * FALSE if the originator aborts the transfer
 *
 * Note: it is the caller's responsibility to actually
 * send the DD_OK byte to start the transfer, or to
 * send a DD_NAK, DD_EXT, or DD_LEN reply with ddreply().
 */
int
dd_rtry (int fd, char *name, char *whichext, long *size)
{
	short hdrlen;
	int i;
	char buf[80];

	i = (int) Fread (fd, 2L, &hdrlen);
	if (i != 2)
		return FALSE;
	if (hdrlen < 9)		/* this should never happen */
		return FALSE;
	i = (int) Fread (fd, 4L, whichext);
	if (i != 4)
		return FALSE;
	whichext[4] = 0;
	i = (int) Fread (fd, 4L, size);
	if (i != 4)
		return FALSE;
	hdrlen -= 8;
	if (hdrlen > DD_NAMEMAX)
		i = DD_NAMEMAX;
	else
		i = hdrlen;
	if (Fread (fd, (long) i, name) != i)
		return FALSE;
	hdrlen -= i;

	/* skip any extra header */
	while (hdrlen > 80)
	{
		Fread (fd, 80L, buf);
		hdrlen -= 80;
	}
	if (hdrlen > 0)
		Fread (fd, (long) hdrlen, buf);

	return TRUE;
}
