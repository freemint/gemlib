/* Dialog function prototypes */

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

long windial_size(void) __attribute__ ((const));
long windial_create(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, short obj, short icon, short field, char *title, short gadgets, PROC_ARRAY *p);
long windial_open(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_close(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_delete(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_formdo(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_center(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long _rc_intersect(BASEPAGE *bp, long fn, short nargs, GRECT *rc1, GRECT *rc2);
long windial_link(BASEPAGE *bp, long fn, short nargs, WINDIAL *old, WINDIAL *new, PROC_ARRAY *p);
long windial_unlink(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_close_all(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long windial_delete_all(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);

/* EOF */

