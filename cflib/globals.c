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
 * Globale Variablen fÅr die cflib.
 */

#include "intern.h"


#ifndef str
# define str(x)		_stringify (x)
# define _stringify(x)	#x
#endif

#define CFLIB_PATCHLEVEL	str(__CFLIB_MAJOR__) "." str(__CFLIB_MINOR__) "." \
				str(__CFLIB_REVISION__) __CFLIB_BETATAG__

/*
 * global identify string for the lib
 */
char __Ident_cflib[] = "$PatchLevel: CF library: " CFLIB_PATCHLEVEL " $";


short	gl_phys_handle = -1;
GRECT	gl_desk;

short	sys_big_id;
short	sys_big_height;
short	sys_big_pts;
short	sys_sml_id;
short	sys_sml_height;
short	sys_sml_pts;
short	sys_wchar;
short	sys_hchar;
short	sys_wbox;
short	sys_hbox;

short	gl_wchar;
short	gl_hchar;
short	gl_wbox;
short	gl_hbox;

short	gl_gdos = FALSE;
short	gl_font_anz = 1;
short	gl_planes = 1;

short	gl_gem = 0;
short	gl_mint = 0;
short	gl_naes = 0;
short	gl_magx = 0;
short	gl_nvdi = 0;

char	gl_appdir[256] = "";
