# include "extdef.h"

# ifndef GEMMA_MULTIPROC

short
call_aes(GEM_ARRAY *gemstr, short fn)
{
	return (short)(gemma.exec)(gemma.handle, (long)CALL_AES, (short)2, gemstr, fn);
}

# else

short
call_aes(GEM_ARRAY *gemstr, short fn)
{
	return (short)(gemma[_pid].exec)(gemma[_pid].handle, (long)CALL_AES, (short)2, gemstr, fn);
}

# endif

/* EOF */
