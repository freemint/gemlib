# include <mintbind.h>
# include "../include/slb/gemma.h"

GEM_ARRAY *gem;
SLB gemma, kern;

GEM_ARRAY *
gem_control(void)
{
	return (GEM_ARRAY *)(gemma.exec)(gemma.handle, (long)GEM_CTRL, (short)0);
}

long
appl_open(char *file, short thread, char *pname)
{
	long r;

	r = Slbopen("gemma32.slb", 0L, GEMMA_VERSION, &gemma.handle, &gemma.exec);
	if (r < 0)
		return r;

	r = (gemma.exec)(gemma.handle, (long)AP_OPEN, (short)3, (char *)file, (short)thread, (char *)pname);
	if (r > 0)
	{
		SLB *kern_p;

		/* Sets the gemma pointer inside itself */
		(gemma.exec)(gemma.handle, (long)34, (short)2, 0x0003, (long)&gemma);
		/* Gets the kernel library pointer */
		kern_p = (SLB *)(gemma.exec)(gemma.handle, (long)34, (short)2, 0x0001, (long)&gemma);
		kern.exec = kern_p->exec;
		kern.handle = kern_p->handle;
		gem = gem_control();
	}
	else
	{
		Slbclose((long)gemma.handle);
		gemma.exec = gemma.handle = 0;
	}

	return r;
}

long
appl_close()
{
	long r = 0;

	if (gemma.handle)
	{
		r = (gemma.exec)(gemma.handle, (long)AP_CLOSE, (short)0);
		Slbclose((long)gemma.handle);
		gemma.exec = gemma.handle = 0;
		kern.exec = kern.handle = 0;
	}

	gem = 0;

	return r;
}

/* EOF */
