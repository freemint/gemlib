# include "gemma.h"

extern const unsigned long ctrl_list[];

struct gemma_flags sflags =
{
	14,		/* number of fields below */
	MAX_PID,	/* self explaining */
	DEF_PAGE_SIZE,	/* default size of MMU pages */
	MIN_PAGE_SIZE,	/* minimum size of memory pages */
	1,		/* verify addresses before passing away to AES */
	0,		/* reserved */
	50,		/* button delay in ms */
	200,		/* AV protocol buffer release delay in ms */
	MAX_AES_OP,	/* maximum AES function code */
	ctrl_list,	/* pointer to AES control list */
	1,		/* draw classic zoomboxes */
	0,		/* draw moveboxes for WM_MOVED */
	0,		/* enable desktop size compensation */
	1,		/* use form_alert() for displaying alerts */
	0 		/* alert handles redraws in windows below */
};

/* EOF */
