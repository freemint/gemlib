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
 * ddreply: send a 1 byte reply to the drag & drop originator
 *
 * Input Parameters:
 * fd:          file handle returned from ddopen()
 * ack:         byte to send (e.g. DD_OK)
 *
 * Output Parameters:
 * none
 *
 * Returns: TRUE on success, FALSE on failure
 * in the latter case the file descriptor is closed
 */
int
dd_reply (int fd, int ack)
{
	char c = ack;

	if (Fwrite (fd, 1L, &c) == 1L)
		return TRUE;
	else
		Fclose (fd);
	return FALSE;
}
