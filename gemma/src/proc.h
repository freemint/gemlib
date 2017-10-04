/* Proc module prototypes */

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

long proc_exec(BASEPAGE *bp, long fn, short nargs, short mode, long flags, const char *cmd, const char *tail, const char *env, PROC_ARRAY *p);
long thread_fork(BASEPAGE *bp, long fn, short nargs, void *startup, void *address, const char *proctitle, long stacksize, long opt, PROC_ARRAY *p);

/* EOF */
