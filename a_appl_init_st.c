#include "mt_gem.h"

#define appl_init _no_appl_init  /* to disable the appl_init inline function from gem.h */
#include "gem.h"

#undef appl_init
short appl_init(void);

short appl_init(void)
{
	gl_apid = mt_appl_init(aes_global);
	gl_ap_version = aes_global[0];
	return gl_apid;
}
