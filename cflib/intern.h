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

#ifndef _cfl_intern_
#define _cfl_intern_

/*
 * interne Definitionen der CFLib
 */
#include "cflib.h"


#ifndef __PUREC__
#define cdecl
#endif

/* ein paar nicht-standard AES-Messages */
#ifndef WM_SHADED
#define WM_SHADED		0x5758
#define WM_UNSHADED		0x5759
#define WF_SHADE		0x575D
#endif

#ifndef SC_CHANGED
#define SC_CHANGED		80
#endif

#ifndef SM_M_SPECIAL
#define SM_M_SPECIAL		101
#endif

#ifndef K_SHIFT
#define K_SHIFT			(K_RSHIFT|K_LSHIFT)
#endif

/* boolean */
#ifdef TRUE
#undef TRUE
#undef FALSE
#endif

#define TRUE			1
#define FALSE			0

#ifdef __MINT__
/* ist in osbind.h komisch definiert. */
typedef struct
{
	unsigned char	*unshift;
	unsigned char	*shift;
	unsigned char	*capslock;
} KEYTAB;
#endif

void *	cf_malloc (long size, char *who, int global);

/* cicon */
CICON *	fix_cicon (CICONBLK *cicnblk, short screen_planes, short handle);


/* form_do */
#define FMD_BACKWARD	1
#define FMD_FORWARD	2

short	edit_valid (OBJECT *tree, short obj);
short	find_edit (OBJECT *tree, short obj, short mode);
short 	cf_objc_find (OBJECT *tree, short start, short depth, short x, short y);
short 	find_shortcut (OBJECT *tree, short kstate, short kreturn);
short 	cf_form_keybd (OBJECT *tree, short edit_obj, short kstate, short *kreturn, short *next_obj);
void	cf_objc_edit (OBJECT *tree, short obj, short kreturn, short *idx, short mode, short kstate, short *ctrl);


/* mdial */
void handle_mdial_msg (short *msg);


/* userdef */
extern OBJECT	*cf_ascii_tab;
extern OBJECT	*cf_alert_box;

void init_userdef (void);
void exit_userdef (void);

/* popup */
short popup_valid_item (OBJECT *tree, short obj);


#ifdef __MINT__

#include <macros.h>
#include <support.h>
#define ltoa(a,b,c)	_ltoa(a,b,c)
#define ultoa(a,b,c)	_ultoa(a,b,c)

#define DTA _DTA

/* Temporary fix for MiNTLib bug.  */
#if defined(__GNUC__) && defined(__MINTLIB_MAJOR__)
# if __MINTLIB_MAJOR__ == 0 && __MINLIB_MINOR < 54
#  ifdef abs
#   undef abs
#  endif
#  define abs(a) \
    ({__typeof__ (a) _a = (a);     \
	      _a  < ((__typeof__ (a))0) ? -(_a) : _a; })
# endif
#endif

#else /* pure lib */

#define min(a,b)	  (((a) < (b)) ? (a) : (b))
#define max(a,b)	  (((a) > (b)) ? (a) : (b))
short rc_intersect(GRECT *r1, GRECT *r2);
void vqt_real_extent(int handle, short x, short y, char *string, short extent[]);

#endif


#endif
