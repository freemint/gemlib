/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 2000 Heiko Achilles
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
 * Farb-Popup mit bis zu 256 Farben
 */

#include "intern.h"
#include <assert.h>


/* Grîûen der einzelnen Farbfelder
 */
#define SMALLSIZE 14
#define BIGSIZE 22


/* flags fÅr ub_parm */
#define F_USEROBJ 0x10000L	/* Objekt ist User-Objekt (durch fix_colorpopobj() umgewandelt) */
				/* (wird etwas anders dargestellt als die Objekte im Farbpopup, */
				/* grîûerer Schatten */

/* Spezielle Werte in ub_parm: (statt Farbindex) */
#define T_COLPOP -1		/* Farbe wird je nach Index im Baum dargestellt */
#define T_NOCOLOR -2		/* "Nichtfarbe", wird durchkreuzt dargestellt */

/* Lokale Variablen
 */
static OBJECT *poptree = NULL;			/* Objekbaum Farb-Popup, wird bei init angelegt */
static int max_displayable_planes;		/* Maximal darstellbare Planes in dieser Auflîsung */
static int framewidth;				/* Berechnung des Abstands zwischen Farbfeldern */
static short fattrib[5], lattrib[6];		/* Sicherung fÅr FÅll- und Linienattribute */
static USERBLK userblk;				/* Ein Userblock fÅr alle EintrÑge im Popup-MenÅ */
static USERBLK noncolor_userblk;		/* Userblock fÅr "Nichtfarbe"-Eintrag */
static USERBLK popobj_userblk[MAX_COLORPOP];	/* Userblock-Liste fÅr alle Farbobjekte */
static int nocolor_sub;
static int handle, use_3D;


/* VDI- Attribute sichern und neue einstellen
 */
static void
save_and_init_attribs (void)
{
	vqf_attributes (handle, fattrib);
	vql_attributes (handle, lattrib);

	vsf_interior (handle, 1);
	vsf_style (handle, 1);
	vswr_mode (handle, MD_REPLACE);
	vsf_perimeter (handle, 0);

	vsl_type (handle, SOLID);
	vsl_width (handle, 1);
	vsl_ends (handle, SQUARE, SQUARE);

}

/* VDI-Attribute wiederherstellen
 */
static void
restore_attribs (void)
{
	vsf_interior (handle, fattrib[0]);
	vsf_color (handle, fattrib[1]);
	vsf_style (handle, fattrib[2]);
	vswr_mode (handle, fattrib[3]);
	vsf_perimeter (handle, fattrib[4]);

	vsl_type (handle, lattrib[0]);
	vsl_color (handle, lattrib[1]);
	vsl_width (handle, lattrib[3]);
	vsl_ends (handle, lattrib[4], lattrib[5]);
}


/* nicht-3d-Darstellung fÅr Farb-Objekt */
static void
draw_non_3d (PARMBLK * parmblk)
{
	short pxy[12];
	int color = (int) parmblk->pb_parm;
	int state = parmblk->pb_currstate;


	/* Rahmen zeichnen */
	if (state & OS_SELECTED) /* selektierter Rahmen ist 2 Pixel dick und schwarz */
	{
		vsf_color (handle, G_BLACK);
		grect_to_array ((GRECT *) &(parmblk->pb_x), pxy);
		v_bar (handle, pxy);
		parmblk->pb_x += 2;
		parmblk->pb_y += 2;
		parmblk->pb_w -= 4;
		parmblk->pb_h -= 4;
	}
	else /* nichtselektierter Rahmen ist 1 Pixel dick und schwarz */
	{
		vsf_color (handle, G_WHITE);	/* erst ggf. vorher vorhandene Selektion weiû Åbermalen */
		grect_to_array ((GRECT *) &(parmblk->pb_x), pxy);
		v_bar (handle, pxy);

		parmblk->pb_x++;
		parmblk->pb_y++;
		parmblk->pb_w -= 2;
		parmblk->pb_h -= 2;
		vsf_color (handle, G_BLACK);
		grect_to_array ((GRECT *) & (parmblk->pb_x), pxy);
		v_bar (handle, pxy);
		parmblk->pb_x++;
		parmblk->pb_y++;
		parmblk->pb_w -= 2;
		parmblk->pb_h -= 2;
	}

	/* Farbfeld zeichnen */
	if (color == T_COLPOP)	/* Eintrag im Farbpopup: Objektindex bestimmt die Farbe */
		vsf_color (handle, parmblk->pb_obj - 1 - nocolor_sub);
	else if (color == T_NOCOLOR)	/* Nichtfarbobjekt wird dargestellt */
		vsf_color (handle, G_WHITE);
	else			/* sonst Farbe aus ub_parm darstellen */
		vsf_color (handle, color);

	grect_to_array ((GRECT *) &(parmblk->pb_x), pxy);
	v_bar (handle, pxy);

	/* Kreuz fÅr Nichtfarbobjekt zeichnen */
	if (color == T_NOCOLOR)
	{
		vsl_color (handle, G_BLACK);
		pxy[0] = parmblk->pb_x;
		pxy[1] = parmblk->pb_y;
		pxy[2] = parmblk->pb_x + parmblk->pb_w - 1;
		pxy[3] = parmblk->pb_y + parmblk->pb_h - 1;
		v_pline (handle, 2, pxy);
		pxy[0] = parmblk->pb_x + parmblk->pb_w - 1;
		pxy[1] = parmblk->pb_y;
		pxy[2] = parmblk->pb_x;
		pxy[3] = parmblk->pb_y + parmblk->pb_h - 1;
		v_pline (handle, 2, pxy);

	}

}

/* 3d-Darstellung fÅr Farbobjekt */
static void
draw_3d (PARMBLK *parmblk)
{
	short pxy[12];
	int color = (int) parmblk->pb_parm;
	long flags = parmblk->pb_parm;
	int state = parmblk->pb_currstate;

	/* Farbfeld zeichnen */
	if (color == T_COLPOP)	/* Eintrag im Farbpopup: Objektindex bestimmt die Farbe */
	{
		vsf_color (handle, parmblk->pb_obj - 1 - nocolor_sub);
		parmblk->pb_x += framewidth >> 1;
		parmblk->pb_y += framewidth >> 1;
		parmblk->pb_w -= framewidth;
		parmblk->pb_h -= framewidth;
	}
	else if (color == T_NOCOLOR)	/* Nichtfarbobjekt wird dargestellt */
	{
		vsf_color (handle, G_WHITE);
		parmblk->pb_x += framewidth >> 1;
		parmblk->pb_y += framewidth >> 1;
		parmblk->pb_w -= framewidth;
		parmblk->pb_h -= framewidth;
	}
	else			/* sonst Farbe aus ub_parm darstellen */
		vsf_color (handle, color);

	grect_to_array ((GRECT *) &(parmblk->pb_x), pxy);
	v_bar (handle, pxy);

	/* Schatten (selektiert) oder Licht (nicht selektiert) links und oben zeichnen */
	vsl_color (handle, state & OS_SELECTED ? G_BLACK : G_WHITE);
	pxy[0] = parmblk->pb_x;
	pxy[1] = parmblk->pb_y + parmblk->pb_h - 1;
	pxy[2] = parmblk->pb_x;
	pxy[3] = parmblk->pb_y;
	pxy[4] = parmblk->pb_x + parmblk->pb_w - 1;
	pxy[5] = parmblk->pb_y;

	if (state & OS_SELECTED) /* der Schatten ist dicker als das Licht */
	{
		pxy[6] = pxy[4] - 1;
		pxy[7] = pxy[5] + 1;
		pxy[8] = pxy[2] + 1;
		pxy[9] = pxy[3] + 1;
		pxy[10] = pxy[0] + 1;
		pxy[11] = pxy[1] - 1;
		v_pline (handle, 6, pxy);
	}
	else
		v_pline (handle, 3, pxy);

	/* Schatten (nicht selektiert) oder Licht (selektiert) rechts und unten zeichnen */
	vsl_color (handle, state & OS_SELECTED ? G_WHITE : G_BLACK);
	pxy[0] = parmblk->pb_x + parmblk->pb_w - 1;
	pxy[1] = parmblk->pb_y;
	pxy[2] = parmblk->pb_x + parmblk->pb_w - 1;
	pxy[3] = parmblk->pb_y + parmblk->pb_h - 1;
	pxy[4] = parmblk->pb_x;
	pxy[5] = parmblk->pb_y + parmblk->pb_h - 1;

	if (flags & F_USEROBJ)	/* Benutzerobjekte haben dickeren Schatten (da sie meist grîûer sind) */
	{
		pxy[6] = pxy[4] + 1;
		pxy[7] = pxy[5] - 1;
		pxy[8] = pxy[2] - 1;
		pxy[9] = pxy[3] - 1;
		pxy[10] = pxy[0] - 1;
		pxy[11] = pxy[1] + 1;
		v_pline (handle, 6, pxy);
	}
	else
		v_pline (handle, 3, pxy);

	/* Kreuz fÅr Nichtfarbobjekt zeichnen */
	if (color == T_NOCOLOR)
	{
		int movewidth = flags & F_USEROBJ ? 1 : 2;

		if (state & OS_SELECTED) /* Das selektierte Kreuz ist weiter nach rechts unten verschoben, "eingedrÅckt" */
		{
			vsl_color (handle, G_BLACK);

			pxy[0] = parmblk->pb_x + movewidth;
			pxy[1] = parmblk->pb_y + movewidth;
			pxy[2] = parmblk->pb_x + parmblk->pb_w - 1 - 1;
			pxy[3] = parmblk->pb_y + parmblk->pb_h - 1 - 1;
			v_pline (handle, 2, pxy);

			pxy[0] = parmblk->pb_x + parmblk->pb_w - 1 - 1;
			pxy[1] = parmblk->pb_y + movewidth;
			pxy[2] = parmblk->pb_x + movewidth;
			pxy[3] = parmblk->pb_y + parmblk->pb_h - 1 - 1;
			v_pline (handle, 2, pxy);
		}
		else
		{
			vsl_color (handle, G_BLACK);

			pxy[0] = parmblk->pb_x;
			pxy[1] = parmblk->pb_y;
			pxy[2] = parmblk->pb_x + parmblk->pb_w - 1 - movewidth;
			pxy[3] = parmblk->pb_y + parmblk->pb_h - 1 - movewidth;
			v_pline (handle, 2, pxy);

			pxy[0] = parmblk->pb_x + parmblk->pb_w - 1 - movewidth;
			pxy[1] = parmblk->pb_y;
			pxy[2] = parmblk->pb_x;
			pxy[3] = parmblk->pb_y + parmblk->pb_h - 1 - movewidth;
			v_pline (handle, 2, pxy);
		}
	}
}


/* Die Userdef-Routine, welche die einzelnen Farbfelder
 * darstellt
 */
static short cdecl
colorpop_userdef (PARMBLK *parmblk)
{
	short pxy[4];
	long flags = parmblk->pb_parm;

	if (flags & F_USEROBJ)
		save_and_init_attribs ();

	grect_to_array ((GRECT *) &(parmblk->pb_xc), pxy);
	vs_clip (handle, 1, pxy);

	if (use_3D)
		draw_3d (parmblk);
	else
		draw_non_3d (parmblk);

	if (flags & F_USEROBJ)
		restore_attribs ();

	return parmblk->pb_currstate & ~OS_SELECTED;

}

/* öberprÅfen, ob Objekt Farb-Popup-Objekt ist
 * (nur fÅr Assertion in set_popobjcolor() / get_popobjcolor()
 */
static short
is_colorpop_object (OBJECT *tree, short obj)
{
	return (tree[obj].ob_type & 0xff) == G_USERDEF
		&& ((tree[obj].ob_spec.userblk == &userblk)
		    || (tree[obj].ob_spec.userblk == &noncolor_userblk)
		    || (tree[obj].ob_spec.userblk >= popobj_userblk
			&& tree[obj].ob_spec.userblk <
			popobj_userblk + MAX_COLORPOP));
}

/* Farb-Popub-Objektfarbe setzen */
void
set_popobjcolor (OBJECT *tree, short obj, short color)
{
	assert (is_colorpop_object (tree, obj));
	tree[obj].ob_spec.userblk->ub_parm &= 0xffff0000L;
	tree[obj].ob_spec.userblk->ub_parm |= ((long) color & 0xffffL);
}

/* Farb-Popup-Objektfarbe abfragen */
short
get_popobjcolor (OBJECT *tree, short obj)
{
	assert (is_colorpop_object (tree, obj));
	return (tree[obj].ob_spec.userblk->ub_parm & 0xffff);
}

/* Farbobjekt auf Userdef umstellen
 */
void
fix_colorpopobj (OBJECT *tree, short obj, short color)
{
	USERBLK *userblkp = popobj_userblk;

	while (userblkp->ub_code)
		userblkp++;

	/* FIXME: Zur Zeit funzt das wg. get_objframe() nicht mit altem Typ im hibyte. */
	tree[obj].ob_type = G_USERDEF;
	tree[obj].ob_spec.userblk = userblkp;
	userblkp->ub_code = colorpop_userdef;
	userblkp->ub_parm = F_USEROBJ | (long) color;

}


/* Initialisierung
 */
short
init_colorpop (short maxplanes)
{
	short workout[57];
	short i, d;
	short maxcolors;

	handle = open_vwork (workout);

	if (appl_xgetinfo (13, &i, &d, &d, &d))
		use_3D = ((workout[13] >= 16) && i == 1);
	else
		use_3D = FALSE;

	userblk.ub_code = colorpop_userdef;	/* Userblk fÅr die Farbfelder im Farb-Popup init. */
	userblk.ub_parm = (long) T_COLPOP & 0xffffl;	/* -1: Farbe wird je nach Index im Baum dargestellt. */
	noncolor_userblk.ub_code = colorpop_userdef;	/* Userblk fÅr das "Nichtfarb"-Feld im Farb-Popup init. */
	noncolor_userblk.ub_parm = (long) T_NOCOLOR & 0xffffl;	/* -2: Nichtfarbe wird dargestellt. */

	vq_extnd (handle, 1, workout);
	max_displayable_planes = min (workout[4], maxplanes);
	maxcolors = min (1 << max_displayable_planes, 1 << maxplanes);

	if (poptree)
		poptree = realloc (poptree, (maxcolors + 2) * sizeof (OBJECT));
	else
		poptree = calloc (maxcolors + 2, sizeof (OBJECT));

	if (!poptree)
		/* error message? */
		return FALSE;

	poptree[0].ob_next = -1;
	poptree[0].ob_head = 1;
	poptree[0].ob_x = 0;
	poptree[0].ob_y = 0;
	poptree[0].ob_type = G_BOX;
	poptree[0].ob_spec.index = 0x00ff1100L;
	poptree[0].ob_flags = OF_FL3DBAK;
	poptree[0].ob_state = OS_SHADOWED;

	return TRUE;
}


/* Abmeldung
 */
void
exit_colorpop (void)
{
	if (handle != -1)
		v_clsvwk (handle);
	free ((void *) poptree);
	poptree = NULL;
}


/* Initialisierung des Baumes fÅr
 * das Farb-Popup; wird bei jedem Aufruf von
 * do_colorpop() erneut aufgerufen, um den Baum
 * fÅr unterschiedliche Farbanzahl zu initialisieren
 */
static void
ini_colorpop (short planes, short show_noncolor)
{
	short colors;
	short i;
	short x = 0, y = 0;
	short size = 0;
	short maxx = 0;
	short startframe = 0;

	planes = min (planes, max_displayable_planes);
	colors = 1 << planes;
	if (planes <= 4)
	{
		size = BIGSIZE;
		maxx = colors / 2;
		framewidth = 2;
	}
	else if (planes <= 6)
	{
		size = BIGSIZE;
		maxx = 8;
		framewidth = 2;
	}
	else if (planes <= 8)
	{
		size = SMALLSIZE;
		maxx = 16;
		framewidth = 1;
	}

	startframe = framewidth % 2;

	poptree[0].ob_tail = colors + (show_noncolor ? 1 : 0);
	poptree[0].ob_width = startframe + maxx * size;
	poptree[0].ob_height =
		startframe + colors * size / maxx +
		(show_noncolor ? size : 0);

	if (show_noncolor)
		colors += 1;

	for (i = 1; i <= colors; i++)
	{
		poptree[i].ob_next = i + 1;
		poptree[i].ob_head = -1;
		poptree[i].ob_tail = -1;
		poptree[i].ob_x = startframe + x * size;
		poptree[i].ob_y = startframe + y * size;
		poptree[i].ob_width = size;
		poptree[i].ob_height = size;
		poptree[i].ob_type = G_USERDEF;
		poptree[i].ob_spec.userblk = &userblk;
		poptree[i].ob_flags = OF_SELECTABLE;
		poptree[i].ob_state = 0;
		
		x += 1;
		
		if (x == maxx || y == 0 && show_noncolor)
		{
			x = 0;
			y++;
		}
	}
	
	if (show_noncolor)
		poptree[1].ob_spec.userblk = &noncolor_userblk;
	
	poptree[colors].ob_next = 0;
	poptree[colors].ob_flags |= OF_LASTOB;


}


/* Farbpopup ausfÅhren
 */
short
do_colorpop (short x, short y, short act_color, short planes, short show_noncolor)
{
	MENU menu, cmenu;
	GRECT r;

	nocolor_sub = show_noncolor ? 1 : 0;

	menu.mn_tree = poptree;
	menu.mn_menu = 0;
	menu.mn_item = 1;
	menu.mn_scroll = 0;
	menu.mn_keystate = 0;

	cmenu = menu;
	ini_colorpop (planes, show_noncolor);
	if (act_color != -1)
	{
		if (show_noncolor && act_color == T_NOCOLOR)
		{
			cmenu.mn_item = 1;
			x -= poptree[1].ob_x;
			y -= poptree[1].ob_y;
		}
		else
		{
			cmenu.mn_item = act_color + 1 + nocolor_sub;
			x -= poptree[act_color + 1 + nocolor_sub].ob_x;
			y -= poptree[act_color + 1 + nocolor_sub].ob_y;
		}
	}

	get_objframe (poptree, 0, &r);

	if (x < gl_desk.g_x)
		x = gl_desk.g_x;
	if ((x + r.g_w) > (gl_desk.g_x + gl_desk.g_w))
		x = (gl_desk.g_x + gl_desk.g_w) - r.g_w;
	if (y < gl_desk.g_y)
		y = gl_desk.g_y;
	if ((y + r.g_h) > (gl_desk.g_y + gl_desk.g_h))
		y = (gl_desk.g_y + gl_desk.g_h) - r.g_h;

	save_and_init_attribs ();
	cf_menu_popup (&menu, x, y, &cmenu, 0, 0);
	restore_attribs ();

	if (cmenu.mn_item == -1)
		return -1;
	if (show_noncolor && cmenu.mn_item == 1)
		return -2;
	return cmenu.mn_item - 1 - nocolor_sub;

}


/* Farbpopup fÅr gegebenes Farbobjekt ausfÅhren
 */
short
handle_colorpop (OBJECT *dial, short dial_obj, short mode, short planes,
		 short show_noncolor)
{
	short ret;
	short act_color, max_color;
	short mx, my, mb;
	short di; /* dummy */

	graf_mkstate (&mx, &my, &mb, &di);

	planes = min (planes, max_displayable_planes);
	max_color = 1 << planes;

	act_color = get_popobjcolor (dial, dial_obj);
	if (act_color > max_color)
		act_color = 1;

	if (mode == POP_CYCLE)
	{
		if (act_color == T_NOCOLOR)
			act_color = 0;
		else if (++act_color > max_color)
		{
			if (show_noncolor)
				act_color = T_NOCOLOR;
			else
				act_color = 0;
		}
		set_popobjcolor (dial, dial_obj, act_color);
		redraw_obj (dial, dial_obj);
		while (mb)
			graf_mkstate (&di, &di, &mb, &di);
		return act_color;
	}

	ret = do_colorpop (mx - 4, my - 4, act_color, planes, show_noncolor);
	if (ret != -1)
	{
		set_popobjcolor (dial, dial_obj, ret);
		redraw_obj (dial, dial_obj);
	}
	return ret;
}
