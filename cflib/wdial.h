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

#ifndef _wdial_h
#define _wdial_h

#include "intern.h"


extern WDIALOG *__wdial_list;

WDIALOG *get_wdial (int w_handle);
void draw_wdial (WDIALOG * wd, int obj, int depth, int x, int y, int w, int h);
void wdial_draw_cursor (WDIALOG *wd, int mode);
void iconify_wdial (WDIALOG *wd, int x, int y, int w, int h);
void uniconify_wdial (WDIALOG *wd, int x, int y, int w, int h);
void wdial_call_cb (WDIALOG *wd);


#endif /* _wdial_h */
