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

# ifndef _magx_h
# define _magx_h

/*
 * Der MagX-Cookie
 */

typedef struct
{
	char		*in_dos;			/* Adresse der DOS- Semaphore */
	int		*dos_time; 			/* Adresse der DOS- Zeit */
	int		*dos_date; 			/* Adresse des DOS- Datums */
	long		res1;
	long		res2;
	long		res3;
	void		*act_pd;			/* Laufendes Programm */
	long		res4;
	int		res5;
	void		*res6;
	void		*res7;				/* interne DOS- Speicherliste */
	void		(*resv_intmem)(void);	 	/* DOS- Speicher erweitern */
	long		(*etv_critic)(void);		/* etv_critic des GEMDOS */
	char*		((*err_to_str)(char e)); 	/* Umrechnung Code->Klartext */
	long		res8;
	long		res9;
	long		res10;
}
DOSVARS;


typedef struct
{
	long		magic;				/* muž $87654321 sein */
	void		*membot;		   	/* Ende der AES- Variablen */
	void		*aes_start;		   	/* Startadresse */
	long		magic2;			 	/* ist 'MAGX' */
	long		date; 				/* Erstelldatum ttmmjjjj */
	void		(*chgres)(int res, int txt);	/* Aufl”sung „ndern */
	long		(**shel_vector)(void);  	/* residentes Desktop */
	char		*aes_bootdrv; 		 	/* von hieraus wurde gebootet */
	int		*vdi_device;			/* vom AES benutzter VDI-Treiber */
	void		*reservd1;
	void	 	*reservd2;
	void	 	*reservd3;
	int		version;		   	/* z.B. $0201 ist V2.1 */
	int		release;		   	/* 0=alpha..3=release */
}
AESVARS;


typedef struct
{
	long		config_status;
	DOSVARS		*dosvars;
	AESVARS		*aesvars;
	void		*res1;
	void		*hddrv_functions;
	long		status_bits;
}
MAGX_COOKIE;


# endif /* _magx_h */
