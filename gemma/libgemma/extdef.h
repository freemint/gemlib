/* Common definitions
 */

# include <gemma/gemma.h>

extern GEM_ARRAY *gem_control(void);
extern short call_aes(GEM_ARRAY *gem, short fn);

# ifdef GEMMA_MULTIPROC
extern SLB gemma[];
# else
extern SLB gemma;
# endif

/* EOF */
