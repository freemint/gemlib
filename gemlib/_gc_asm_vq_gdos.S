
	.globl	_vq_gdos

_vq_gdos:
	movew	#-2,d0
	trap	#2
	cmpw	#-2,d0
	sne	d0
	extw	d0
# ifndef __MSHORT__
	extl	d0
# endif
	rts
