#ifndef _MAIN_H_
#define _MAIN_H_
//#define		NBG0_CEL_ADR		( SCL_VDP2_VRAM_B1 )
//#define		NBG0_MAP_ADR		( SCL_VDP2_VRAM_B0 )
//#define		NBG2_CEL_ADR		( SCL_VDP2_VRAM_B1  )
//#define		NBG2_MAP_ADR		( SCL_VDP2_VRAM_B0  )

//#define		NBG2_CEL_ADR		( SCL_VDP2_VRAM_B1 + 0x20000 )
//#define		NBG2_MAP_ADR		( SCL_VDP2_VRAM_B0 + 0x10000 )

#define		NBG0_CEL_ADR		( SCL_VDP2_VRAM_B0   )
#define		NBG0_MAP_ADR		( SCL_VDP2_VRAM_B0 + 0x10000 )

#define		NBG2_CEL_ADR		( SCL_VDP2_VRAM_B1    )
#define		NBG2_MAP_ADR		( SCL_VDP2_VRAM_B1 + 0x10000  )


	#define	AD_VDP2			(0x20000000+0x05E00000)
	
	#define	AD_VDP2_VRAM	(AD_VDP2+0x00000000)
	#define	AD_VDP2_COLOR	(AD_VDP2+0x00100000)
	#define	AD_VDP2_REG		(AD_VDP2+0x00180000)
	
	#define	VDP2_REG		(( volatile Uint16 * )AD_VDP2_REG)
	#define	VDP2_TVMD		VDP2_REG[0]
	#define	VDP2_EXTEN		VDP2_REG[1]
	#define	VDP2_TVSTAT		VDP2_REG[2]
	#define	VDP2_VRSIZE		VDP2_REG[3]
	#define	VDP2_HCNT		VDP2_REG[4]
	#define	VDP2_VCNT		VDP2_REG[5]
	#define	VDP2_RAMCTL		VDP2_REG[7]

//SCL_VDP2_VRAM_B0
#define		BACK_COL_ADR		( VDP2_VRAM_A1 + 0x1fffe )
#define     SystemWork      0x060ffc00              /* System Variable Address */
#define     SystemSize      (0x06100000-0x060ffc00) /* System Variable Size */

extern Uint32   _bstart, _bend;

void ss_main(void);
void Pal2CRAM( Uint16 *Pal_Data , void *Col_Adr , Uint32 suu );
int LoadFile(char *name, Uint8 *location);
void InitCD();
#endif

