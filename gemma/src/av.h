/* AV module prototypes */

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

long _send(PROC_ARRAY *proc, short command, short dest, char *buf, long blen);
long va_send(BASEPAGE *bp, long fn, short nargs, short command, char *msg, long len, PROC_ARRAY *p);
long av_dir_update(BASEPAGE *bp, long fn, short nargs, short drive, PROC_ARRAY *p);
long av_view(BASEPAGE *bp, long fn, short nargs, char *pathname, PROC_ARRAY *p);
long av_help(BASEPAGE *bp, long fn, short nargs, char *pathname, PROC_ARRAY *p);
long open_url(BASEPAGE *bp, long fn, short nargs, char *url, PROC_ARRAY *p);

/* EOF */
