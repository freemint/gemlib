/* The AES gateway.
 */

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

# include "gemma.h"
# include "dosproto.h"
# include "gemproto.h"
# include "callout.h"
# include "emu.h"

# ifdef DEBUG
#  define DEBUGFAC 1
# else
#  define DEBUGFAC 0
# endif

/* Helper struct
 */
typedef struct
{
	uchar c1 : 8;
	uchar c2 : 8;
	uchar c3 : 8;
	uchar c4 : 8;
} CTRL;

/* The GEM AES control list
 */
static const long ctrl_list[] =
{

/* 0: none */

	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* 10: appl_xxxx() */

	0x00010000, 0x02010100, 0x02010100, 0x00010100, 0x02010100,
	0x01010100, 0x02010000, 0x00010000, 0x01030100, 0x00010000,

/* 20: evnt_xxxx() */

	0x00010000, 0x03050000, 0x05050000, 0x00010100, 0x02010000,
	0x10070100, 0x02010000, 0x00000000, 0x00000000, 0x00000000,

/* 30: menu_xxxx() */

	0x01010100, 0x02010100, 0x02010100, 0x02010100, 0x01010200,
	0x01010100, 0x02010200, 0x02010200, 0x03010100, 0x01010100,

/* 40: objc_xxxx() */

	0x02010100, 0x01010100, 0x06010100, 0x04010100, 0x01030100,
	0x02010100, 0x04020100, 0x08010100, 0x04030000, 0x04010100,

/* 50: form_xxxx() */

	0x01010100, 0x09010000, 0x01010100, 0x01010000, 0x00050100,
	0x03030100, 0x02020100, 0x00000000, 0x00000000, 0x00000000,

/* 60: none */

	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x04030100,

/* 70: graf_xxxx() */

	0x04030000, 0x08030000, 0x06010000, 0x08010000, 0x08010000,
	0x04010100, 0x03010100, 0x00050000, 0x01010100, 0x00050000,

/* 80: scrp_xxxx() */

	0x00010100, 0x00010100, 0x00010000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* 90: fsel_xxxx() */

	0x00020200, 0x00020300, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02010000,

/* 100: wind_xxxx() */

	0x05010000, 0x05010000, 0x01010000, 0x01010000, 0x06050000,
	0x06010000, 0x02010000, 0x01010000, 0x06050000, 0x00000000,

/* 110: rsrc_xxxx() */

	0x00010100, 0x00010000, 0x02010001, 0x02010100, 0x01010100,
	0x00010100, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* 120: shel_xxxx() */

	0x00010200, 0x03010200, 0x01010100, 0x01010100, 0x00010100,
	0x00010300, 0x00010200, 0x00010200, 0x01010200, 0x02010100,

/* 130: miscellaneous */

	0x01050000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x02010100, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* 140: testing */

	0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* 150: none */

	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

/* Configuration flags
 */
struct gemma_flags sflags =
{
	0xDEADEFEB,	/* magic number */
	(sizeof(sflags)/sizeof(long)),
	MAX_PID,	/* self explaining */
	DEF_PAGE_SIZE,	/* default size of MMU pages */
	MIN_PAGE_SIZE,	/* minimum size of memory pages */
	MAX_AES_OP,	/* maximum AES function code */
	ctrl_list,	/* pointer to AES control list */
	50,		/* button release delay in ms */
	200,		/* AV protocol buffer release delay in ms */
	1,		/* verify addresses before passing away to AES */
	1,		/* draw classic zoomboxes */
	0,		/* draw moveboxes for WM_MOVED */
	0,		/* enable desktop size compensation */
	1,		/* use form_alert() for displaying alerts */
	0, 		/* unassigned, reserved */
	DEBUGFAC,	/* global debugging facility */
	0,		/* load external fileselector library */
	0		/* fix for buggy linker */
};

/* The extreme border: this below traps to the AES
 */
static long
_aes(PROC_ARRAY *proc, short opcode)
{
	ushort c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	union {
		CTRL bf;
		long nm;
	} ctrl;

	if (opcode < 512)
	{
		ctrl.nm = ctrl_list[opcode];

		c4 = ctrl.bf.c4;
		c3 = ctrl.bf.c3;
		c2 = ctrl.bf.c2;
		c1 = ctrl.bf.c1;

		proc->gem.control[4] = c4;
		proc->gem.control[3] = c3;
		proc->gem.control[2] = c2;
		proc->gem.control[1] = c1;
	}
	else
		opcode -= 512;

	proc->gem.control[0] = opcode;

	gemsys(AESSYS, proc->gem.aesparams);

	return (long)proc->gem.int_out[0];
}

/* This is the user AES calling routine. All user calls go this way
 * (also from within other library modules and functions).
 */
long
call_aes(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *proc, short opcode)
{
	long r;
	short x;

	if (nargs < 2) return -EINVAL;
	if ((opcode & 0x00ff) > MAX_AES_OP) return -ENOSYS;
	if (!proc) proc = get_contrl(bp);

	TOUCH(proc);		/* make sure arrays are accessible */

	if (opcode != 10)	/* appl_init() */
		if (!proc->gem.global[0])
			return -EACCES;

	/* Fixes section */
	switch(opcode)
	{
		case 10:	/* appl_init() */
		{
			if (proc->gem.global[0])
				return -EACCES;
			for (x = 0; x < 16; x++)
				proc->gem.global[x] = 0;	/* safe sex */
			proc->gem.vwk_handle = -1;		/* even safer sex */
			break;
		}

		case 12:	/* appl_write(), round length up to 16 byte boundary */
		{
			short t;

			TOUCH(proc->gem.addr_in[0]);	/* access test */
			t = proc->gem.int_in[1];
			if (t & 0x000f)
			{
				t += 0xf;
				t &= ~0xf;
				proc->gem.int_in[1] = t;
			}
			TOUCH((proc->gem.addr_in[0] + t - 1));	/* also for the end of the buffer */
			break;
		}

		case 16:	/* odd PC GEM function, appl_bvset() */
		{
			ulong bset;

			bset = *(ulong *)&proc->gem.int_in[0];
			proc->bvset = ((bset >> 16) | (bset << 16));
			proc->gem.int_out[0] = 1;

			return 1;
		}

# ifndef _HAVE_APPL_YIELD
		case 17:	/* appl_yield() */
		{
			proc->gem.int_out[0] = 1;
			_yield(proc);

			return 1;
		}
# endif
		case 51:	/* form_dial() */
		{
			if ((proc->gem.int_in[0] == 0) || (proc->gem.int_in[0] == 3))
				break;
			if (sflags.zoomboxes)
				break;
			proc->gem.int_out[0] = 1;

			return 1;
		}

		case 72:	/* graf_movebox() */
		case 73:	/* graf_growbox() */
		case 74:	/* graf_shrinkbox() */
		{
			if (sflags.zoomboxes)
				break;
			proc->gem.int_out[0] = 1;

			return 1;
		}

		case 82:	/* scrp_clear(), emulate */
		{
			return emu_scrp_clear(proc);
		}

		case 91:	/* fsel_exinput() */
		{
			/* When proc->cb_fsel is not zero, then
			 * this is a call-back from the fileselector.slb
			 */
			if (proc->cb_fsel == 0)
			{
				if (sflags.xfselect && proc->ego && proc->fsel.exec)
				{
					long quid;

					proc->cb_fsel = 1;	/* set callback flag */
					quid = (proc->fsel.exec)(proc->fsel.handle, (long)0, (short)3, proc, proc->ego, proc->bvset);
					proc->cb_fsel = 0;

					return quid;
				}
			}
# ifndef _HAVE_FSEL_EXINPUT
			if (proc->gem.global[0] < 0x0140)
			{
				TOUCH(proc->gem.addr_in[0]);
				TOUCH(proc->gem.addr_in[1]);

				return _aes(proc, 90);
			}
# endif
			TOUCH(proc->gem.addr_in[0]);
			TOUCH(proc->gem.addr_in[1]);
			TOUCH(proc->gem.addr_in[2]);

			break;
		}

		case 109:	/* wind_new(), ignore on AES < 1.40 */
		{
			if (proc->gem.global[0] < 0x0140)
			{
				proc->gem.int_out[0] = 0;
				return 0;
			}
			break;
		}

		case 130:	/* appl_getinfo(), emulate on AES < 4.0 */
		{
			for (x = 0; x < 4; x++)
				proc->gem.int_out[x] = 0;
# ifndef _HAVE_APPL_GETINFO
			if (!aes40(proc))
				return emu_appl_getinfo(proc);
# endif
			break;
		}

		case 135:	/* form_popup() */
		{
# ifndef _HAVE_FORM_POPUP
			return emu_form_popup(proc);
# else
			TOUCH(proc->gem.addr_in[0]);
# endif
			break;
		}

		case 512+36:	/* menu_unregister() */
		case 512+37:	/* menu_click() */
		{
			proc->gem.int_out[0] = 0;

			return 0;
		}
	}

	/* Access test section */

# ifndef _ROBUST_AES
	switch(opcode)
	{
		case 13:	/* appl_find() */
		{
			ulong adr, rv;

			adr = (ulong)proc->gem.addr_in[0];
			rv = adr & 0xffff0000L;
			rv >>= 16;
			if (!rv || (rv == 0xfffe) || (rv == 0xffff))
			{
				short ap[4];

				_appl_getinfo(proc, AES_PROCESS, ap);	/* this will re-enter call_aes() :-) */
				if (ap[1])
					break;
			}
			TOUCH(adr);	/* access test */
			break;
		}

		case 14:	/* appl_tplay() */
		case 15:	/* appl_trecord() */
		{
			long adr;

			adr = proc->gem.addr_in[0];
			TOUCH(adr);
			adr += (long)((proc->gem.int_in[0] * 6) - 1);
			TOUCH(adr);
			break;
		}

		case 18:	/* appl_search() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 23:	/* evnt_mesag() */
		case 25:	/* evnt_multi() */
		{
			long adr;

			adr = proc->gem.addr_in[0];
			TOUCH(adr);
			adr += 15;
			TOUCH(adr);
			break;
		}

		case 30:	/* menu_bar() */
		case 31:	/* menu_icheck() */
		case 32:	/* menu_ienable() */
		case 33:	/* menu_tnormal() */
		case 35:	/* menu_register() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 34:	/* menu_text() */
		case 36:	/* menu_popup() */
		{
			TOUCH(proc->gem.addr_in[0]);
			TOUCH(proc->gem.addr_in[1]);
			break;
		}

		case 40:	/* objc_add() */
		case 41:	/* objc_delete() */
		case 42:	/* objc_draw() */
		case 43:	/* objc_find() */
		case 44:	/* objc_offset() */
		case 45:	/* objc_order() */
		case 46:	/* objc_edit() */
		case 47:	/* objc_change() */
		case 49:	/* objc_xfind() */
		case 50:	/* form_do() */
		case 52:	/* form_alert() */
		case 54:	/* form_center() */
		case 55:	/* form_keybd() */
		case 56:	/* form_button() */
		case 75:	/* graf_watchbox() */
		case 76:	/* graf_slidebox() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 78:	/* graf_mouse() */
		{
			if (proc->gem.int_in[0] == 255)
				TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 80:	/* scrp_read() */
		case 81:	/* scrp_write() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 105:	/* wind_set() */
		{
			long adr;
			short mode;

			mode = proc->gem.int_in[1];

			switch(mode)
			{
				case WF_NEWDESK:
				case WF_TOOLBAR:
				{
					adr = *(long *)&proc->gem.int_in[0];
					if (adr)
						TOUCH(adr);
					break;
				}

				case WF_NAME:
				case WF_INFO:
				{
					TOUCH(*(long *)&proc->gem.int_in[0]);
					break;
				}
			}
			break;
		}

		case 110:	/* rsrc_load() */
		case 113:	/* rsrc_sadr() */
		case 114:	/* rsrc_obfix() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 115:	/* rsrc_rcfix() */
		{
			short ap[4];

			_appl_getinfo(proc, AES_PROCESS, ap);
			if (ap[3])
				TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 120:	/* shel_read() */
		{
			TOUCH(proc->gem.addr_in[0]);
			TOUCH(proc->gem.addr_in[1]);
			break;
		}

		case 121:	/* shel_write() */
		{
			switch(proc->gem.int_in[0])
			{
				case SWM_LAUNCH:
				case SWM_LAUNCHNOW:
				case SWM_LAUNCHACC:
				{

					if (proc->gem.addr_in[1])
						TOUCH(proc->gem.addr_in[1]);

					if (proc->gem.int_in[0] & 0xff00)
					{
						SHELW *shp;

						shp = (SHELW *)proc->gem.addr_in[0];
						TOUCH(shp);
						TOUCH(shp->newcmd);
						if (shp->defdir)
							TOUCH(shp->defdir);
						if (shp->env)
							TOUCH(shp->env);
					}
					else
					{
						if (proc->gem.addr_in[0])
							TOUCH(proc->gem.addr_in[0]);
					}

					break;
				}
				case SWM_SHUTDOWN:
				{
					if (proc->gem.addr_in[0])
						TOUCH(proc->gem.addr_in[0]);
					break;
				}
				case SWM_BROADCAST:
				{
					TOUCH(proc->gem.addr_in[0])
					break;
				}
				case SWM_ENVIRON:
				{
					if (proc->gem.int_in[1])
						TOUCH(proc->gem.addr_in[0]);
					break;
				}
				case SWM_AESMSG:
				{
					TOUCH(proc->gem.addr_in[0])
					break;
				}
			}
			break;
		}

		case 122:	/* shel_get() */
		case 123:	/* shel_put() */
		case 124:	/* shel_find() */
		{
			TOUCH(proc->gem.addr_in[0]);
			break;
		}

		case 125:	/* shel_envrn() */
		case 126:	/* shel_rdef() */
		{
			TOUCH(proc->gem.addr_in[0]);
			TOUCH(proc->gem.addr_in[1]);
			break;
		}

		case 127:	/* shel_wdef() */
		{
			ulong adr;

			adr = proc->gem.addr_in[0];
			if (adr)
				TOUCH(adr);
			adr = proc->gem.addr_in[1];
			if (adr)
				TOUCH(adr);
			break;
		}

		case 128:	/* shel_help() */
		{
			ulong adr;

			TOUCH(proc->gem.addr_in[0]);
			adr = proc->gem.addr_in[1];
			if (adr)
				TOUCH(adr);
			break;
		}

		case 129:	/* appl_control() */
		{
			switch(proc->gem.int_in[1])
			{
				case 14:	/* APC_INFO */
				case 15:	/* APC_MENU */
				case 16:	/* APC_WIDGETS */
					TOUCH(proc->gem.addr_in[0]);
					break;
			}
			break;
		}
	}
# endif

	r = _aes(proc, opcode);

	/* Fixes continued */
	switch(opcode)
	{
		case 19:		/* appl_exit() */
		{
			proc->gem.global[0] = 0;
			break;
		}

		case 130:		/* appl_getinfo() */
		{
			if (!r)
				for (x = 0; x < 4; x++)
					proc->gem.int_out[x] = 0;
			break;
		}
	}

	return r;
}

/* EOF */
