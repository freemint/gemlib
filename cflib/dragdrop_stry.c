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

#include <osbind.h>

#include "dragdrop.h"


/*
 * ddstry: see if the receipient is willing to accept a certain
 *         type of data (as indicated by "ext")
 *
 * Input parameters:
 * fd           file descriptor returned from ddcreate()
 * ext          pointer to the 4 byte file type
 * name         pointer to the name of the data
 * size         number of bytes of data that will be sent
 *
 * Output parameters: none
 *
 * Returns:
 * DD_OK        if the receiver will accept the data
 * DD_EXT       if the receiver doesn't like the data type
 * DD_LEN       if the receiver doesn't like the data size
 * DD_NAK       if the receiver aborts
 */
int
dd_stry (int fd, char *ext, char *name, long size)
{
	short hdrlen, i;
	char c;

	/* 4 bytes for extension, 4 bytes for size, 1 byte for
	 * trailing 0
	 */
	hdrlen = 9 + strlen (name);
	i = Fwrite (fd, 2L, &hdrlen);

	/* now send the header */
	if (i != 2)
		return DD_NAK;
	i = Fwrite (fd, 4L, ext);
	i += Fwrite (fd, 4L, &size);
	i += Fwrite (fd, (long) strlen (name) + 1, name);
	if (i != hdrlen)
		return DD_NAK;

	/* wait for a reply */
	i = Fread (fd, 1L, &c);
	if (i != 1)
		return DD_NAK;
	return c;
}
