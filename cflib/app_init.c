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
#include "app.h"


void
init_app (char *rsc)
{
	int d;
	long l;
	int work_out[57];
	char s[128];
	char path[256];

	debug ("started\n");
	gl_apid = appl_init ();
	gl_phys_handle =
		graf_handle (&gl_wchar, &gl_hchar, &gl_wbox, &gl_hbox);
	wind_get_grect (0, WF_WORKXYWH, &gl_desk);
	graf_mouse (ARROW, 0x0L);
	__app_hidden = 0;
#ifdef __MINT__
	gl_gem = aes_global[0];
#else
	gl_gem = _GemParBlk.global[0];
#endif

	if (getcookie ("MiNT", &l))
		gl_mint = (int) l;
	gl_magx = get_magx_version ();
	cf_magxPC = getcookie ("MgPC", NULL);
	if (getcookie ("nAES", &l))
		gl_naes = *(unsigned short *) l;
	if (getcookie ("NVDI", &l))
		gl_nvdi = *(unsigned short *) l;

	/* SystemzeichensÑtze bestimmen */
	if (appl_xgetinfo (0, &sys_big_height, &sys_big_id, &d, &d) == 0)
	{
		sys_big_id = 1;
		if ((Getrez () == 0) || (Getrez () == 1))	/* ST-Low/Mid */
			sys_big_height = 6;
		else
			sys_big_height = 13;
	}
	if (appl_xgetinfo (1, &sys_sml_height, &sys_sml_id, &d, &d) == 0)
	{
		sys_sml_id = 1;
		sys_sml_height = 4;
	}

	cf_vdi_handle = open_vwork (work_out);
	cf_font_anz = work_out[10];
	vq_extnd (cf_vdi_handle, TRUE, work_out);
	gl_planes = work_out[4];

	/* Aus den Pixel-Hîhen Point-Hîhen ermitteln */
	sys_sml_pts = height2pts (cf_vdi_handle, sys_sml_id, sys_sml_height);
	sys_big_pts = height2pts (cf_vdi_handle, sys_big_id, sys_big_height);

	gl_gdos = (vq_vgdos () != -2);
	if (gl_gdos)
		cf_font_anz += vst_load_fonts (cf_vdi_handle, 0);

	vst_font (cf_vdi_handle, sys_big_id);
	vst_point (cf_vdi_handle, sys_big_pts, &sys_wchar, &sys_hchar,
		   &sys_wbox, &sys_hbox);

	/*
	 * Startverzeichnis ermitteln. 
	 * Unter N.AES (Minix) kann es ungÅltige Pfade geben, daher der extra 
	 * path_exitst().
	 */
	shel_read (path, s);
	split_filename (path, gl_appdir, NULL);
	if (!path_exists (gl_appdir))
		get_path (gl_appdir, 0);

	init_userdef ();

	if (rsc && *rsc != '\0')
	{
		__app_rsc_load = (rsrc_load (rsc) != 0);
		if (!__app_rsc_load)
		{
			form_alert (1,
				    "[3][RSC nicht gefunden!|RSC not found!][Exit]");
			exit_app (-1);
		}
	}
}
