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


int	gl_apid = -1;
int	gl_phys_handle = -1;

GRECT	gl_desk;

int	sys_big_id;
int	sys_big_height;
int	sys_big_pts;
int	sys_sml_id;
int	sys_sml_height;
int	sys_sml_pts;
int	sys_wchar;
int	sys_hchar;
int	sys_wbox;
int	sys_hbox;

int	gl_wchar;
int	gl_hchar;
int	gl_wbox;
int	gl_hbox;

int	gl_gdos = FALSE;
int	gl_font_anz = 1;
int	gl_planes = 1;

int	gl_gem = 0;
int	gl_mint = 0;
int	gl_naes = 0;
int	gl_magx = 0;
int	gl_nvdi = 0;

char	gl_appdir[256] = "";
