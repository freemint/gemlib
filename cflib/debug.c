/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

/*
 * Debug ermîglicht das Debuggen von GEM-Programmen.
 * Dazu wird eines der mîglichen DEBUGDEVICEs geîffnet und dann
 * kann es wie eine normale Datei fÅr Ausgaben benutzt werden.
 *
 */

#include <stdarg.h>
#include "intern.h"


int gl_debug = FALSE;

static FILE *debug_handle = NULL;
static DEBUGDEV device;
static char progName[25];

void
debug_init (char *prog, DEBUGDEV dev, char *file)
{
	char devicename[20] = "";

	strcpy (progName, prog);
	device = dev;
	switch (dev)
	{
		case Con:
			debug_handle = stdout;
			break;
		case TCon:
			if (appl_find ("T-CON   ") > 0)
				debug_handle = stdout;
			else
				device = null;
			break;
		case Datei:
			strcpy (devicename, file);
			break;
		case Terminal:
			strcpy (devicename, "u:\\dev\\modem1");
			break;
		case Modem1:
			strcpy (devicename, "u:\\dev\\modem1");
			break;
		case Modem2:
			strcpy (devicename, "u:\\dev\\modem2");
			break;
		case Seriell1:
			strcpy (devicename, "u:\\dev\\serial1");
			break;
		case Seriell2:
			strcpy (devicename, "u:\\dev\\serial2");
			break;
		case Prn:
			strcpy (devicename, "u:\\dev\\prn");
			break;
		default:
			device = null;
			break;
	}

	if (device != null)
		gl_debug = TRUE;

	if (device != null && device != Con && device != TCon)
	{
		if (device == Datei)
			debug_handle = fopen (devicename, "a");
		else
			debug_handle = fopen (devicename, "w");
		if (debug_handle != NULL)
			setvbuf (debug_handle, NULL, _IONBF, 0);
	}

	if (device == Terminal)
		debug ("\33[2J\33[0;0H");	/* VT100-Terminal an Modem 1 */
}


void
debug_exit (void)
{
	if (debug_handle != NULL && debug_handle != stdout)
		fclose (debug_handle);
	debug_handle = NULL;
	gl_debug = FALSE;
}


void
debug (char *FormatString, ...)
{
	va_list arg_ptr;

	if (gl_debug)
	{
		fprintf (debug_handle, "%s: ", progName);
		va_start (arg_ptr, FormatString);
		vfprintf (debug_handle, FormatString, arg_ptr);
		va_end (arg_ptr);
		if (device == Datei)
			fflush (debug_handle);
	}
}
