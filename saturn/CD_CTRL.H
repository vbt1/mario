#if	!defined( __CD_CTRL_H )
	#define	__CD_CTRL_H

#include	"sega_sys.h"
#include	"sega_cdc.h"
/*** Initialize datas. ***/
#define	INITDATA		((Sint32)0)
#define	STANDBYTIME		((Sint32)0)
#define	ECCTIMES		((Sint32)0)
#define	RETRYTIMES		((Sint32)0)

/*** function prottypes. ***/
extern void	InitCDBlock( void );	/* Initialize at first. */
extern void	CheckCDOpen( void );	/* Cover Open check. */
extern void	PlayMusic( Uint8 );		/* Play Music. */
extern void	StopMusic( void );		/* Stop Music. */

#endif
