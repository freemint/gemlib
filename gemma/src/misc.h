/* Misc module prototypes */

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

long gem_control(BASEPAGE *bp, long fn, short nargs);
long get_users(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long lib_control(BASEPAGE *bp, long fn, short nargs, short function, long enable, PROC_ARRAY *p);
const char *get_version(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long ftext_fix(BASEPAGE *bp, long fn, short nargs, short tree, short obj, PROC_ARRAY *p);
long objc_xchange(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, short obj, short newstate, short redraw, PROC_ARRAY *p);
long objc_xdraw(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, short obj, PROC_ARRAY *p);
long menu_xpop(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, short obj, MENU *menu, PROC_ARRAY *p);

/* EOF */
