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


char __dragdrop_pipename[] = "u:\\pipe\\dragdrop.aa";

#ifdef __MINT__
__sighandler_t __dragdrop_oldpipesig;
#else
long __dragdrop_oldpipesig;
#endif
