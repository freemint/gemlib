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

#include "intern.h"
#include "inline.h"


#define AL_STR_ANZ	5
#define AL_STR_LEN	40
#define AL_BUT_ANZ	3
#define AL_BUT_LEN	14

static int alert_key(OBJECT *tree, int edit_obj, int kstate, int *kreturn, int *next_obj)
{
	int	cont = TRUE;
	int	scan;
	int	but = 0;
		
	scan = *kreturn >> 8;
	switch (scan)
	{
		case 0x3B :				/* F1 -> erster Button */
			but = AL_BUT1;
			break;
		case 0x3C :				/* F2 -> zweiter Button */
			but = AL_BUT2;
			break;
		case 0x3D :				/* F3 -> dritter Button */
			but = AL_BUT3;
			break;
	}
	if ((but != 0) && !get_flag(tree, but, HIDETREE))
	{
		*next_obj = but;
		*kreturn = 0;			/* Lib soll Key nicht mehr auswerten. */
		cont = FALSE;
	}
	return cont;
}
				
static int make_alert(int def, int undo, char *alert_str, int win)
{
	char	al_str[AL_STR_ANZ][AL_STR_LEN];
	int	str_cnt;
	char	al_btn[AL_BUT_ANZ][AL_BUT_LEN];
	int	btn_cnt,	i, str_len, btn_len, h;
	char	*p, str[40];
		
	/* erst mal alles verstecken */
	for (i = 1; i <= AL_BUT3; i++)
		set_flag(cf_alert_box, i, HIDETREE, TRUE);

	for (i = AL_BUT1; i <= AL_BUT3; i++)
	{
		set_flag(cf_alert_box, i, DEFAULT, FALSE);
		set_flag(cf_alert_box, i, FLAG11, FALSE);
	}
	
	/* damit jedes Mal zentriert wird */
	cf_alert_box[0].ob_x = 0;
	cf_alert_box[0].ob_y = 0;


	/* Icon setzen */
	i = AL_INFO;
	switch (alert_str[1])
	{
		case '0' :
			break;
		case '1' :
			i = AL_ACHT;
			break;
		case '2' :
			i = AL_QST;
			break;
		case '3' :
			i = AL_STOP;
			break;
		default:
			debug("make_alert: Unbekanntes Icon: %c\n", alert_str[1]);
			break;
	}
	if (i > 0)
	{
		set_flag(cf_alert_box, i, HIDETREE, FALSE);
		if (win)
			cf_alert_box[i].ob_y = 2 * gl_hchar;	/* 1 tiefer wegen Titel */
	}

	/* Strings suchen */
	p = alert_str + 4;
	str_cnt = 0;
	str_len = 0;
	while ((*p != ']') && (str_cnt <= AL_STR4))
	{
		i = 0;
		while ((*p != '|') && (*p != ']'))
		{
			str[i] = *p;
			i++;
			p++;
			if (i >= AL_STR_LEN)
				break;
		}
		if (*p != ']')
			p++;
		str[i] = '\0';
		if (strlen(str) > str_len)
			str_len = (int)strlen(str);
		strcpy(al_str[str_cnt], str);
		str_cnt++;
	}

	/* Buttons suchen */
	p += 2;
	btn_cnt = 0;
	btn_len = 0;
	while ((*p != ']') && (btn_cnt <= AL_BUT3))
	{
		i = 0;
		while ((*p != '|') && (*p != ']'))
		{
			str[i] = *p;
			i++;
			p++;
			if (i >= AL_BUT_LEN)
				break;
		}
		if (*p != ']')
			p++;
		str[i] = '\0';
		if (strlen(str) > btn_len)
			btn_len = (int)strlen(str);
		strcpy(al_btn[btn_cnt], str);
		btn_cnt++;
	}
	btn_len++;	/* immer ein breiter */
	if (btn_len < 6)
		btn_len = 6;

	/* frei + Texte + frei + Buttons + frei */
	h = 1 + str_cnt + 1 + 1 + 1;
	if (win)
		h++;
		
	/* Box anpassen */
	cf_alert_box[0].ob_width = cf_alert_box[AL_STR1].ob_x + gl_wchar * (str_len + 2);
	/* passen die Buttons auch rein? */
	i = (1 + (btn_cnt + 1) * btn_len) * gl_wchar;
	if (cf_alert_box[0].ob_width < i)
		cf_alert_box[0].ob_width = i;
	cf_alert_box[0].ob_height = h * gl_hchar;

	/* Falls im Fenster, alles eine Zeile tiefer wegen des Titels */
	if (win)
		h = 1;
	else
		h = 0;
		
	/* Texte eintragen */
	for (i = 0; i < str_cnt; i++)
	{
		set_flag(cf_alert_box, AL_STR1 + i, HIDETREE, FALSE);
		set_string(cf_alert_box, AL_STR1 + i, al_str[i]);
		cf_alert_box[AL_STR1 + i].ob_y = (1 + i + h) * gl_hchar;
	}
	
	for (i = 0; i < btn_cnt; i++)
	{
		set_flag(cf_alert_box, AL_BUT1 + i, HIDETREE, FALSE);
		set_string(cf_alert_box, AL_BUT1 + i, al_btn[i]);

		/* Position anpassen */
		cf_alert_box[AL_BUT1 + i].ob_x = cf_alert_box[0].ob_width - (btn_cnt - i) * (btn_len + 2) * gl_wchar;
		cf_alert_box[AL_BUT1 + i].ob_y = (1 + str_cnt + 1 + h) * gl_hchar;
		/* Breite anpassen */
		cf_alert_box[AL_BUT1 + i].ob_width = btn_len * gl_wchar;
	}

	if ((def > 0) && (def < 4))
		set_flag(cf_alert_box, AL_BUT1 + def - 1, DEFAULT, TRUE);
	if ((undo > 0) && (undo < 4) && (undo != def))
		set_flag(cf_alert_box, AL_BUT1 + undo - 1, FLAG11, TRUE);

	return TRUE;
}

static int alert(int def, int undo, char *str, char *title, int win)
{
	int		ret = 0;
	KEY_CB	old;
	
	if (make_alert(def, undo, str, win))
	{
		if (win && title[0] != '\0')
			set_string(cf_alert_box, AL_TITLE, title);
		
		old = set_formdo_keycb(alert_key);
		graf_mouse(ARROW, NULL);
		if (win)
			ret = simple_mdial(cf_alert_box, 0) & 0x7fff;
		else
			ret = simple_dial(cf_alert_box, 0) & 0x7fff;
		set_formdo_keycb(old);
		set_state(cf_alert_box, ret, SELECTED, FALSE);
		ret = ret - AL_BUT1 + 1;
	}
	return ret;
}

int do_alert(int def, int undo, char *str)
{
	return alert(def, undo, str, "", FALSE);
}

int do_walert(int def, int undo, char *str, char *win_title)
{
	return alert(def, undo, str, win_title, TRUE);
}
