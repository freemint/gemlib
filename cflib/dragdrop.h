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

#ifndef _dragdrop_h
#define _dragdrop_h

#include "intern.h"


char __dragdrop_pipename[];

#ifdef __MINT__
#include <errno.h>
#include <signal.h>
extern __sighandler_t __dragdrop_oldpipesig;
#else
#include <atarierr.h>
extern long __dragdrop_oldpipesig;
#endif


#endif /* _dragdrop_h */
