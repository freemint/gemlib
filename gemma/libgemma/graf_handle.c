# include "extdef.h"

long
graf_handle(short *hwc, short *hhc, short *hwb, short *hhb)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	r = call_aes(gem, 77);

	*hwc = gem->int_out[1];
	*hhc = gem->int_out[2];
	*hwb = gem->int_out[3];
	*hhb = gem->int_out[4];

	return r;
}

/* EOF */
