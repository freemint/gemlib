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
 * Funktionen auf das Dateisystem.
 */

#include <ctype.h>
#ifdef __MINT__
#include <sys/stat.h>
#include <support.h>
#else
#include <ext.h>
#define S_IFMT			0170000
#define S_IFDIR		0040000
#define S_ISDIR(m)	((m & S_IFMT) == S_IFDIR)
#endif

#include "intern.h"


int file_exists(char *filename)
{
	struct stat	s;
	
	if (filename[0] == '\0')
		return FALSE;
	return (stat(filename, &s) == 0);
}

int path_exists(char *pathname)
{
	struct stat	s;
	int			r = FALSE;
	
	if (pathname[0] != '\0')
	{
		if ((stat(pathname, &s) == 0) && S_ISDIR(s.st_mode))
			r = TRUE;

		/* Work-around fÅr MagiCPC, wo der stat(<Laufwerk>) nicht funkt! */
		if (cf_magxPC && !r)
		{
			int	len = (int)strlen(pathname);

			if (pathname[1] == ':' && len <= 3)	/* nur Laufwerk 'X:' oder 'X:\' */
			{
				char	p[80];

				/* Laufwerk existiert, wenn man das akt. Verzeichnis ermitteln kann */			
				if (Dgetpath(p, toupper(pathname[0]) - 64) == 0)
					r = TRUE;
			}
		}
	}
	return r;
}

int get_path(char *path, char drive)
{
	int 	ret, drive_nr;

	if (drive == 0)
	{
		drive = 'A' + Dgetdrv();					/* Aktuelles Laufwerk */
		if (drive > 'Z')
			drive = drive - 'Z' + '0';
	}
	else
		drive = toupper(drive);
	if (drive >= '1' && drive <= '6')			/* Laufwerk nach Z mit Big-DOS oder MetaDOS > 2.60 */
		drive_nr = drive - '1' + 26;
	else
		drive_nr = drive - 'A';
	path[0] = drive;
	path[1] = ':';
	ret = Dgetpath (path + 2, drive_nr + 1);
	strcat (path, "\\");
	
	if (fs_case_sens(path) == NO_CASE)
		str_toupper(path);

	return (ret == 0);
}

int set_path(char *path)
{
	int	drive, ret;

	if (path[0] == '\0')
		return FALSE;

	path[0] = toupper(path[0]);
	if (path[0] >= '1' && path[0] <= '6')
		drive = path[0] - '1' + 26;
	else
		drive = path[0] - 'A';
	Dsetdrv(drive);
	ret = Dsetpath(path + 2);
	return (ret == 0);
}

void split_filename(char *fullname, char *path, char *name)
{
	char	*str;

	str = strrchr (fullname, '\\');

	if (path != NULL)
		path[0] = '\0';		/* schadet nix */
	if (name != NULL)
		name[0] = '\0';		/* ditto */

	if (str != NULL)
	{
		/* Dateinamen holen */
		if (name != NULL)
			strcpy(name, str+1);

		/* Pfad mit Laufwerk bestimmen */
		if (path != NULL)
		{
			int len =  (short)( str - (char *)fullname + 1);
			
			strncpy(path, fullname, len);
			path[len] = '\0';
		}
	}
}

void split_extension(char *filename, char *name, char *extension)
{
	char *ptr = strrchr(filename, '.');
	char *slash = strrchr(filename, '\\');
	char *colon = strrchr(filename, ':');
	
	if (ptr == NULL || ptr == filename || 
		 ptr < slash || ptr - slash == 1 || ptr - colon == 1)
	{
		if (name)
			strcpy(name, filename);

		if (extension)
			extension[0] = '\0';
		return;
	}
	
	if (name)
		strncpy(name, filename, ptr-filename);

	if (extension)
		strcpy(extension, ptr+1);
}

void set_extension(char *filename, char *new_ext)
{
	char *ptr = strrchr(filename, '.');
	char *slash = strrchr(filename, '\\');
	char *colon = strrchr(filename, ':');
	
	if (ptr == NULL || ptr == filename ||
		 ptr < slash || ptr - slash == 1 ||  ptr - colon == 1)
	{
		ptr = filename + strlen(filename);
		*ptr = '.';
	}

	if (fs_case_sens(filename) == NO_CASE)
	{
		char	myext[5];

		strcpy(myext, new_ext);
		str_toupper(myext);
		strcpy(ptr+1, myext);
	}
	else
		strcpy(ptr + 1, new_ext);
}

int make_normalpath(char *path)
{
	int	i;
	char	p[256];
	char	*f, drv;
	int	ret;

	if (path[0] == '\0')
		return FALSE;

#ifdef __MINT__
	if (path[0] == '/')				/* UNIX-Pfad */
	{
		unx2dos(path, p);
		strcpy(path, p);
	}
#endif

	/* Laufwerk bestimmen */
	if (path[1] != ':') 				/* Kein Laufwerk */
	{
		drv = 'A' + Dgetdrv();		/* aktuelles Laufwerk */
		if (drv > 'Z')
			drv = drv - 'Z' + '0';	/* A..Z 1..6 */
		f = path;
	}
	else
	{
		path[0] = toupper(path[0]);
 		drv = path[0];
		if (drv > 'Z')
			drv = drv - 'Z' + '0';	/* A..Z 1..6 */
 		f = path + 2;
	}
	/* Pfad mit Laufwerk bestimmen */
	if (f[0]=='.' && (f[1]=='\\' || f[1]=='\0'))
	{
		get_path(p, drv); 			/* aktuellen Pfad nehmen */
		if (f[1]=='\\') 
			strcat(p,f+2);
	}
	else if (f[0]!='\\') 			/* Keine Root */
	{
		get_path(p, drv);
		strcat (p, f);
	}
	else
	{
		p[0] = drv;
		p[1] = ':';
		p[2] = '\0';
		strcat (p, f);
	}

	i = (int)strlen(p);
	if (p[i-1] != '\\')
	{
		p[i] = '\\';
		p[i+1] = '\0';
	}

	ret = path_exists(p);
	if (!ret)
		p[i] = '\0';

	strcpy(path,p);
	return ret;
}

void make_shortpath(char *path, char *shortpath, int maxlen)
{
	char	help[256];
	int	path_len;
	char	*p1, *p2;

	strcpy(help, path);
	path_len = (int)strlen(help);
	if (maxlen < 18)
		split_filename(path, NULL, help);
	else if (path_len > maxlen)
	{
		p1 = strchr(help, '\\');
		p2 = p1;
		path_len += 2; 				/* zwei Punkte neu */
		while(*p2 != '\0' && path_len > maxlen)
		{
			p2++;
			while(*p2 != '\\' && *p2 != '\0')
			{
				p2++;
				path_len--;
			}
		}
		if (*p2 != '\0')
		{
			memmove(p1 + 3, p2, strlen(p2) + 1);
			p1[1] = '.';
			p1[2] = '.';
		}
		else
		{
			p2 = strrchr(help, '\\');
			memmove(help, p2, strlen(p2) + 1);
		}
	}
	strcpy(shortpath, help);
}

int fs_long_name(char *filename)
{
	char	path[256];
	long	ret;

	/* eigentlichen Dateinamen abschneiden und durch '.' ersetzen -
		muû sein, da Datei evtl. noch nicht existiert... */
	split_filename(filename, path, NULL);
	strcat(path, ".");
	ret = Dpathconf(path, 3);
	if ((ret < 0) || (ret == 12))
		ret = 0;
	return (int) ret;
}

int fs_case_sens(char *filename)
{
	char	path[256];
	int	ret;

	/* Eigentlichen Dateinamen abschneiden und durch '.' ersetzen -
		muû sein, da Datei evtl. noch nicht existiert... */
	split_filename(filename, path, NULL) ;
	strcat(path, ".") ;
	ret = (int)Dpathconf(path, 6);

	/* MagiCPC 6.0 meldet 0, das ist aber falsch!! */
	if (cf_magxPC && ret == 0)
		ret = 2;

	switch (ret)
	{
		case 0 :				/* echter Unterschied, MinixFS */
			ret = FULL_CASE;
			break;
		case 2 :				/* kein echter Unterschied, VFAT, MacFS */
			ret = HALF_CASE;
			break;
		default:
			ret = NO_CASE;		/* Dpathconf() nicht verfÅgbar, oder kein Unterschied */
	}
	return ret;
}
