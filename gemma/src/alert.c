/* Alert functions */

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

# include <errno.h>
# include <string.h>

# include "gemma.h"
# include "gemproto.h"
# include "dosproto.h"

# include "alert.h"

void
bin2asc(long number, char *out)
{
	char decout[11];
	ulong x, quot, remd;

	if (number)
	{
		if (number < 0)
		{
			*out++ = '-';
			number = ~number;
			number++;
		}

		for (x = 0; number && (x < 10);)
		{
			quot = (ulong)(number / 10);
			remd = (ulong)(number % 10);
			number = (ulong)quot;
			decout[x++] = remd | 0x30;
		}
		while(x > 0)
			*out++ = decout[--x];
	}
	else
		*out++ = '0';

	*out = 0;
}

static void
line_break(char *line, const short rmargin)
{
	short i, left, ms = 0, q = 0;

	left = strlen(line);

	if (left < rmargin)
		return;

	/* First, cut trailing spaces off */

	for (i = left-1; i; i--)
	{
		if (line[i] != ' ')
			break;
		line[i] = 0;
		ms++;
	}

	left -= ms;

	while(left > rmargin)
	{
		for (i = rmargin; i; i--)
		{
			if (line[i + q] == ' ')
				break;
		}
		line[i + q] = '|';
		left -= i;
		q += i;
	}
}

/* Skeleton routine for putting code doing windowed alerts
 */
static long
_wind_alert(PROC_ARRAY *proc, short button, const char *msg)
{
	return _form_alert(proc, button, msg);
}

long
_alert(PROC_ARRAY *proc, short button, const char *msg)
{
	char tmp[512], c;
	short x, y = 0, forcesys = 0;
	long r;

	/* Asterisk at the begin forces usage of regular form_alert()
	 * instead of internal routines. This is intened for internal
	 * error handling purposes, not for the user.
	 */
	if (msg[0] == '*')
	{
		msg++;
		forcesys++;
	}

	for (x = 0; x < 512; x++)
	{
		c = msg[x];
		if (!c)
			break;
		if (c == '%')
		{
			x++;
			if (msg[x] == 'a')
			{
				bin2asc((long)proc->gem.global[2], tmp + y);
				y = strlen(tmp);
				continue;
			}
		}
		tmp[y++] = msg[x];
	}

	if (forcesys || sflags.system_alerts)
		r = _form_alert(proc, button, tmp);
	else
		r = _wind_alert(proc, button, tmp);

	return r;
}

long
windial_alert(BASEPAGE *bp, long fn, short nargs, short button, long object, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long r, obj;

	if (nargs < 2) return -EINVAL;
	if (nargs == 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	obj = object;

	r = (long)obj2addr(proc, R_STRING, (ulong)obj);
	if (r > 0)
		r = _alert(proc, button, (const char *)r);

	return r;
}

long
windial_error(BASEPAGE *bp, long fn, short nargs, long error, const char *message, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	char msgbuf[256];
	const char *m;

	if (nargs < 1) return -EINVAL;
	if (nargs == 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	if (error > 0)
	{
		_alert(proc, 1, "*[1][windial_error():|value out of range for apid %a!][ Cancel ]");
		return -EBADARG;
	}

	strcpy(msgbuf, "[1][");

	if (!error)
	{
		if (proc->gem.global[0] >= 0x0410)
			msgbuf[1] = '4';			/* use new icon */
		else
			msgbuf[1] = '0';
	}

	if (nargs > 1 && (long)message > 0)
	{
		m = (const char *)obj2addr(proc, R_STRING, (ulong)message);
		if ((long)m > 0)
		{
			char trans[256];

			if (strlen(m) > MAX_LINE)
			{
				strcpy(trans, m);
				line_break(trans, MAX_LINE);
				m = trans;
			}
			strcat(msgbuf, m);
			strcat(msgbuf, "|");
		}
	}

	m = dos_serror(proc, error);

	strcat(msgbuf, m);
	
	if (error)
	{
		char *d;

		strcat(msgbuf, "|Status: ");
		d = msgbuf + strlen(msgbuf);
		bin2asc(error, d);
		m = "][ Cancel ]";
	}
	else
		m = "][ OK ]";

	strcat(msgbuf, m);

	DEBUGMSG(msgbuf);

	_alert(proc, 1, msgbuf);

	return 0;
}

/* EOF */
