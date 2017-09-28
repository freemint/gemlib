/* compiler.h for lattice C */

#ifndef __COMPILER_H__
#define __COMPILER_H__ 1

#ifndef cdecl
#define cdecl __stdargs
#endif

#ifndef __CDECL
#define __CDECL cdecl
#endif

#ifndef __cdecl
#define __cdecl cdecl
#endif

#define __BEGIN_DECLS
#define __END_DECLS

#define inline

#define __LATTICE__

#endif /* __COMPILER_H__ */
