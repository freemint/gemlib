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
 * ACHTNG: Dieses Modul darf nicht mit -O bersetzt werden, da sonst der 
 *         ASM-Hack kaputt-optimiert wird!! (gilt nur fr gcc 2.7.2.3)
 *
 */

#ifdef __MINT__
  #include <osbind.h>
#else
  #include <tos.h>
#endif
#include <gemx.h>

#include "app.h"
#include "intern.h"

#include "xfsl.h"


#ifdef __GNUC__
/*
 * Hier muessen wir basteln, um int-Parameter auf wortbreite umzumappen.
*/
#define xfsl_init(f, w, l) \
__extension__ \
({ \
	register long retvalue __asm__("d0"); \
 \
	__asm__ volatile \
	( \
		"movl	%3,%%sp@-\n\t" \
		"movw	%2,%%sp@-\n\t" \
		"movl	%1,%%a0\n\t" \
		"jsr	%%a0@\n\t" \
		"addql	#6,%%sp" \
	: "=r"(retvalue)				/* output */ \
	: "r"(f), "r"(w), "r"(l)	/* input */ \
	: __CLOBBER_RETURN("d0") "d1", "a0", "a1", "cc"	/* clobbered regs */	\
	AND_MEMORY \
  ); \
  retvalue; \
})

#define xfsl_event(f, w, l) \
__extension__ \
({ \
	register long retvalue __asm__("d0"); \
 \
	__asm__ volatile \
	( \
		"movl	%3,%%sp@-\n\t" \
		"movw	%2,%%sp@-\n\t" \
		"movl	%1,%%a0\n\t" \
		"jsr	%%a0@\n\t" \
		"addql	#6,%%sp" \
	: "=r"(retvalue)				/* output */ \
	: "r"(f), "r"(w), "r"(l)	/* input */ \
	: __CLOBBER_RETURN("d0") "d1", "a0", "a1", "cc"	/* clobbered regs */	\
	AND_MEMORY \
  ); \
  retvalue; \
})

#define xfsl_exit(f, w) \
__extension__ \
({ \
	register long retvalue __asm__("d0"); \
 \
	__asm__ volatile \
	( \
		"movw	%2,%%sp@-\n\t" \
		"movl	%1,%%a0\n\t" \
		"jsr	%%a0@\n\t" \
		"addql	#2,%%sp" \
	: "=r"(retvalue)		/* outputs */ \
	: "r"(f), "r"(w)		/* inputs */ \
	: __CLOBBER_RETURN("d0") "d1", "a0", "a1", "cc"	/* clobbered regs */	\
	AND_MEMORY \
  ); \
  retvalue; \
})

#else
/* [GS] Old:
#define xfsl_init(a,b,c)	a(b, c)
#define xfsl_event(a,b,c)	a(b, c)
#define xfsl_exit(a,b)		a(b)
*/
#endif


static xFSL_PAR	xpar;
static PFONTINFO f_info;
/* static EVENT ev; */

static inline short
do_xfsl (long v, short handle, short flags, char *title, short *id, short *pts)
{
	xFSL *xfsl;
	int ret = 0;
	int win;
	int use_win;
	EVENT ev;

	xfsl = (xFSL *)v;
	memset(&ev, 0, sizeof(EVENT));

	memset(&xpar, 0, sizeof(xFSL_PAR));
	xpar.par_size = sizeof(xFSL_PAR);
	xpar.pfi_size = sizeof(PFONTINFO);
	
	xpar.headline = title;
	xpar.fontflags = FF_ALL;
	if (flags & FS_F_MONO)
		xpar.fontflags &= ~FF_PROPORTIONAL;
				
	f_info.fontid = *id;
	f_info.fontsize.size = *pts;
	xpar.font = &f_info;

	use_win = cf_msg_cb;		/* Msg-Routine da -> Fenster */
	if (use_win)
	{
		xpar.control = (CC_WINDOW|CC_APPMODAL);
		ev.ev_mflags = MU_MESAG;
	}

#ifdef __GNUC__	
	win = xfsl_init(xfsl->xfsl_init, handle, &xpar);
#else
 	win = xfsl->xfsl_init (handle, &xpar);
#endif
	if (win == xFS_ERROR)
		return FALSE;

	if (use_win && (win == xFS_NO_WINDOW))
	{
		xpar.control = 0;
		ev.ev_mflags = 0;
		use_win = FALSE;
	}

	if (use_win)
		disable_menu();

	ret = 0;
	do
	{
#ifdef __GNUC__	
	ret = xfsl_event(xfsl->xfsl_event, win, &ev);
#else
 	ret = xfsl->xfsl_event ( win, &ev);
#endif
		if (ret == xFS_EVENT)
		{
#ifdef __GNUC__
			short m[8], i;
	
			for (i = 0; i<8; i++)
				m[i] = ev.ev_mmgpbuf[i];
			handle_mdial_msg(m);
#else
			handle_mdial_msg((int*)ev.ev_mmgpbuf);
#endif
		}
	}
	while (ret != xFS_OK && ret != xFS_STOP);
#ifdef __GNUC__	
	xfsl_exit(xfsl->xfsl_exit, win);
#else
 	xfsl->xfsl_exit (win);
#endif

	if (use_win)
		enable_menu();

	if (ret == xFS_OK)
	{
		*id = f_info.fontid;
		*pts = f_info.fontsize.size;
	}
	return (ret == xFS_OK);
}

static inline short
check_for_xfsl (long *v)
{
	short ok;
	xFSL *xfsl;
		
	ok = getcookie("xFSL", v);
	if (ok)
	{
		xfsl = (xFSL *)*v;
		if (xfsl->product == 0x4D584653L)	/* MagxUFSL versteht uns nicht! */
		{
			ok = FALSE;								/* -> FALSE, damit MagiC benutz wird */
			*v = 0L;
		}
	}
	return ok;
}

/* --------------------------------------------------------------------------- */

static inline short
check_for_fprot (void)
{
	char name[9], *p;
	short i = -1;

	p = getenv("FONTSELECT");
	if (p)
	{
		strncpy(name, p, 8);
		name[8] = '\0';
		for (i = (int)strlen(name); i < 8; i++)
			strcat(name, " ");
		i = appl_find(name);
	}
	return i;
}

static inline void
do_fprotokoll (int ap_id, int id, int pts)
{
	short msgbuff[8];
	
	msgbuff[0] = 0x7A19;			/* FONT_SELECT */
	msgbuff[1] = gl_apid;
	msgbuff[2] = 0;
	msgbuff[3] = -1;
	msgbuff[4] = id;
	msgbuff[5] = pts;
	msgbuff[6] = 1;
	msgbuff[7] = 0;

	appl_write(ap_id, (int)sizeof(msgbuff), msgbuff);
}

/* --------------------------------------------------------------------------- */

static inline short
do_magx (short handle, short f_anz, short flags, short *id, short *pts)
{
	FNT_DIALOG *fnt_ptr;
	int f_typ, ret, win;
	long ratio = 1l << 16, n_id, n_pts;
	short but, check, d;
	EVNT ev;
	
	f_typ = FNTS_BTMP|FNTS_OUTL|FNTS_MONO;
	if (!(flags & FS_F_MONO))
		f_typ |= FNTS_PROP;
		
	n_id = *id;
	n_pts = (long) *pts << 16;
	
	fnt_ptr = fnts_create(handle, f_anz, f_typ, FNTS_3D, "The quick brown...", NULL);

	if (!cf_msg_cb)	/* keine Msg-Routine -> modal */
		ret = fnts_do(fnt_ptr,  FNTS_BSET, n_id, n_pts, ratio, &check, &n_id, &n_pts, &ratio);
	else
	{
		disable_menu();
		
		win = fnts_open(fnt_ptr, FNTS_BSET, -1, -1, n_id, n_pts, ratio);
		
		ret = 0;
		while (ret == 0)
		{
#ifdef __GNUC__
			short msg[8], i, mx, my, mb, mc, ks, kr;

			/*
			 * GNU erwartet beim evnt_multi wirklich 'int', in EVNT sind aber
			 * nur 'short', so dass die Struktur nicht bergeben werden kann!
			*/
			ev.mwhich = (short)evnt_multi(MU_KEYBD|MU_MESAG|MU_BUTTON, 2, 1, 1, 
											0, 0, 0, 0, 0,	0, 0, 0, 0, 0,
											msg, 0, &mx, &my, &mb, &ks, &kr, &mc);
			ev.mx = mx;
			ev.my = my;
			ev.mbutton = mb;
			ev.kstate = ks;
			ev.key = kr;
			ev.mclicks = mc;
			for (i = 0; i<8; i++)
				ev.msg[i] = msg[i];
#else
			ev.mwhich = (short)evnt_multi(MU_KEYBD|MU_MESAG|MU_BUTTON, 2, 1, 1, 
											0, 0, 0, 0, 0,	0, 0, 0, 0, 0,
											(int*)ev.msg, 0, (int*)&ev.mx, (int*)&ev.my, (int*)&ev.mbutton, 
											(int*)&ev.kstate,	(int*)&ev.key, (int*)&ev.mclicks);
#endif
			if (ev.mwhich & MU_MESAG)
			{
				switch (ev.msg[0])
				{
					case WM_REDRAW :
					case WM_MOVED :
					case WM_SIZED:
						if (ev.msg[3] != win)		/* fuer fremdes Fenster */
#ifdef __GNUC__
							handle_mdial_msg(msg);
#else
							handle_mdial_msg((int*)ev.msg);
#endif
						break;

					case WM_BOTTOMED:					/* nicht erlaubt! */
						break;
					
					case WM_TOPPED :
					case WM_NEWTOP :
					case WM_ONTOP :		
						ev.msg[0] = WM_TOPPED;		/* immer Fontbox toppen! */
						ev.msg[3] = win;
						break;
				}

			}
			ret = fnts_evnt(fnt_ptr, &ev, &but, &check, &n_id, &n_pts, &ratio);
			
			if (ret == 0)
				ret = but;
			else
				ret = 0;
		}
		fnts_close(fnt_ptr, &d, &d);
		
		enable_menu();
	}
	
	fnts_delete(fnt_ptr, 0);

	if (ret == FNTS_OK|| ret == FNTS_SET)
	{
		*id = (int) n_id;
		*pts = (int) (n_pts >> 16);
		return TRUE;
	}
	return FALSE;
}

/* --------------------------------------------------------------------------- */

short
do_fontsel (short flags, char *title, short *id, short *pts)
{
	short new_id, new_pts;
	short fs_handle, workout[57], f_anz, d, i;
	short ok = FALSE;
	long v;
				
	/* 
	 * Wir machen einfach eine eigene WS auf, da MagiC am Handle rumfummelt und
	 * alte UFSL den Demotext drucken wuerden.
	 * Wer einen Font fuer den Drucker nicht fuer den Bildschirm anmeldet,
	 * hat selber schuld!
	 */
	fs_handle = open_vwork(workout);
	f_anz = workout[10];

	if (gl_gdos)
	{
		f_anz += vst_load_fonts(fs_handle, 0);
		vst_font(fs_handle, *id);
		vst_point(fs_handle, *pts, &d,&d,&d,&d);
	}
	new_id = *id;
	new_pts = *pts;

	if ((flags & FS_M_XFSL) && check_for_xfsl(&v))
	{
		ok = do_xfsl(v, fs_handle, flags, title, &new_id, &new_pts);
	}

	else if ((flags & FS_M_FPROT) && (i = check_for_fprot()) >= 0)
	{
		do_fprotokoll(i, *id, *pts);
		return FALSE; /* immer so, da neuer Font per Message kommt! */
	}		

	else if ((flags & FS_M_MAGX) && (appl_xgetinfo(7, &i, &d, &d, &d) && (i & 0x04)))
	{
		ok = do_magx(fs_handle, f_anz, flags, &new_id, &new_pts);
	}
	else /* keine der drei Methoden moeglich */
	{
		*id = -1;
		*pts = -1;
		ok = FALSE;
	}	

	if (gl_gdos)
		vst_unload_fonts(fs_handle, 0);

	v_clsvwk(fs_handle);

	if (ok)
	{
		*id = new_id;
		*pts = new_pts;
	}

	return ok;
}
