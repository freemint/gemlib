/* Statically linked SLB loader
 *
 * (c) 2000 Draco/YC
 *
 * Must be compiled with -mshort, but as far as I can tell
 * may be linked even if the program is compiled without -mshort.
 *
 */

# include <mintbind.h>
# include <sys/stat.h>

static char *
strcopy(char *s, char *d)
{
	char c;

	do {
		c = *d++ = *s++;
	} while(c);
	d--;

	return d;
}

long
_slbopen(char *fname, char *path, long ver, void *hnd, void *exec)
{
	long r;
	unsigned long err;
	char tmp[128], decout[10], *d;
	unsigned short x, quot, remd;
	struct stat st;		/* only some empty room for Fxattr() */

	r = Slbopen(fname, path, ver, hnd, exec);
	if (r < 0)
	{
		d = tmp;
		d = strcopy("Cannot access the library ", d);
		d = strcopy(fname, d);
		d = strcopy(", error -", d);
		err = (unsigned long)~r;
		err++;
		for (x = 0; err && x < 10;)
		{
			quot = (unsigned short)(err / 10);
			remd = (unsigned short)(err % 10);
			err = (unsigned long)quot;
			decout[x++] = remd | 0x30;
		}
		while(x > 0)
			*d++ = decout[--x];
		*d = 0;

		/* This will succeed when we are on MiNT */
		r = Fxattr(0, "u:/proc/.-1", &st);
		if (r < 0)
		{
			Cconws("\r\n");	/* TOS here, write to CON: */
			Cconws(tmp);
			Cconws("\r\nPress a key\r\n");
			Crawcin();
		}
		else
			Salert(tmp);	/* Produce a civilized alert */
	}
	return r;
}

/* EOF */
