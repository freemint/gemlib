# include "extdef.h"

# ifndef GEMMA_MULTIPROC

GEM_ARRAY *
gem_control(void)
{
	return (GEM_ARRAY *)(gemma.exec)(gemma.handle, (long)GEM_CTRL, (short)0);
}

short
call_aes(GEM_ARRAY *gem, short fn)
{
	return (short)(gemma.exec)(gemma.handle, (long)CALL_AES, (short)2, gem, fn);
}

# else

# include <mintbind.h>

short
call_aes(GEM_ARRAY *gem, short fn)
{
	long pid = Pgetpid();

	return (short)(gemma[pid].exec)(gemma[pid].handle, (long)CALL_AES, (short)2, gem, fn);
}

GEM_ARRAY *
gem_control(void)
{
	long pid = Pgetpid();

	return (GEM_ARRAY *)(gemma[pid].exec)(gemma[pid].handle, (long)GEM_CTRL, (short)0);
}

# endif

/* EOF */
