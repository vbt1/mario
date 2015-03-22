//-----------------------------------------
//modifier drawbackg
//-----------------------------------------


#define SBL_ON
#include    <machine.h>
#include    "sega_gfs.h"
#include "sega_snd.h"
#include "sega_pcm.h"

#define		_SPR3_
#include "saturn.h"
#include "main.h"
//#include "..\def.h"
//#include "..\main.h"

#include "title/title.cel"
#include "title/title.map"
#include "title/title.pal"

#include "sprites/mario.cel"
#include "sprites/mario.pal"

//#include "sound/pcm_jump.h"


//#define ACTIONREPLAY 1
#define	RGB( r, g, b )		(0x8000U|((b) << 10)|((g) << 5 )|(r))

typedef struct {
    Uint8   id;
    Uint8   size;
    Uint8   data[2];
}SmpPerData;

static SmpPerData *per_data;
static PerMulInfo *mul_data;
Uint32  PadWorkArea[7];
Uint8 per_work[500];
    SclLineparam lp;


#ifdef SBL_ON
SysPort		*__port;
Uint8 *aVRAM;
#define SPRITES 100
SprSpCmd sprites[SPRITES];
SysPort		*__port;
SysDevice	*device;
 trigger_t	        pltrigger[2],pltriggerE[2];
 Uint16 *colBgAddr;
extern Uint8	cel_mario[];
extern Uint8	*t;

#define	SDDRV_NAME	"SDDRVS.TSK"
#define	SDDRV_SIZE	26624 //0x7000
#define	SDDRV_ADDR	0x00220000//0x6080000

#define	RING_BUF_SIZE	(2048L*4)
#define	PCM_ADDR	((void*)0x25a20000)
#define	PCM_ADDR2	((void*)0x25a60000)

//#define	PCM_ADDR	((void*)0x00260000)
//#define	PCM_ADDR2	((void*)0x002a0000)

#define	PCM_SIZE	(4096L*2)				/* 2.. */

Sint8 *g_movie_buf = (Sint8 *)0x25a20000;//0x04000000;
Sint8 *g_movie_buf2 = (Sint8 *)0x25a60000;//0x04000000;

//Sint8 *g_movie_buf =  (Sint8 *)0x00260000;//0x04000000;
//Sint8 *g_movie_buf2 =(Sint8 *)0x002a0000;//0x04000000;


PcmHn pcm[2];
char pcm_sound[5][0x10000];
signed long pcm_size[5];


static void sndInit(void);
static PcmHn createHandle(PcmCreatePara *para);

void	UsrVblankIn( void )
{
	SCL_VblankStart();
            _spr2_transfercommand();  	
				PCM_MeVblIn();
}
void   UsrVblankOut( void ){

		t = PER_GET_TIM();
		PER_GetPort(__port);	
		char my_date[60];
		sprintf(my_date,"%02x%02x/%02d/%02x %02x-%02x-%02x",t[6],t[5],t[4] & 0x0F,t[3],t[2],t[1],t[0] );
		FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,(Uint8 *)my_date,84,220,2,8,9,0);
		SCL_VblankEnd();

}

void	SetVblank( void ){

	__port = PER_OpenPort();
	PER_LInit( PER_KD_PERTIM, 2, 2, per_work, 0 );
	INT_ChgMsk(INT_MSK_NULL,INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT);
	INT_SetScuFunc(INT_SCU_VBLK_IN,UsrVblankIn);
	INT_SetScuFunc(INT_SCU_VBLK_OUT,UsrVblankOut);
	INT_ChgMsk(INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT,INT_MSK_NULL);

}
//	PER_Init(PER_KD_PERTIM,2,PER_ID_DGT,PER_SIZE_DGT,PadWorkArea,0);
#endif

unsigned short palette[16]=
{
RGB( 0, 0, 0 ),RGB( 140>>3, 49>>3 , 0      ),RGB( 189>>3, 66>>3 , 0      ),RGB( 222>>3, 99>>3 , 0      ),
RGB( 0, 0, 0 ),RGB( 136>>3, 0     , 0      ),RGB( 255>>3, 170>>3, 0      ),RGB( 238>>3, 136>>3, 0      ),
RGB( 0, 0, 0 ),RGB( 255>>3, 255>>3, 255>>3 ),RGB( 187>>3, 187>>3, 187>>3 ),RGB( 221>>3, 221>>3, 221>>3 ),
RGB( 0, 0, 0 ),RGB( 0>>3  , 73>>3 , 231>>3 ),RGB( 0>>3  , 182>>3, 231>>3 ),RGB( 148>>3, 219>>3, 247>>3 )

};

//int game(void);

int main(void)
{
	Uint8	*dst;
    Uint16  loop;	

    // 1.Zero Set .bss Section
    for (dst = (Uint8 *)&_bstart; dst < (Uint8 *)&_bend; dst++)
    {
		*dst = 0;
	}
	
    for (dst = (Uint8 *)SystemWork, loop = 0; loop < SystemSize; loop++)
    {
		*dst = 0;
	}
	
	VDP2_InitVRAM();   

	ss_main();
	return 0;
}
void Cel2VRAM( Uint8 *Cel_Data , void *Cell_Adr , Uint32 suu )
{
	Uint32 i;
	Uint8 *VRAM;

	VRAM = (Uint8 *)Cell_Adr;

	for( i = 0; i < suu; i++ )
		*(VRAM++) = *(Cel_Data++);
}

//---------------------------------------------------------------------------------------------------------------

void Map2VRAM( Uint16 *Map_Data , void *Map_Adr , Uint16 suuj , Uint16 suui , Uint16 palnum ,Uint32 mapoff)
{
	Uint16 i , j;
	Uint16 paloff;
	Uint16 *VRAM;

	paloff= palnum << 12;
	VRAM = (Uint16 *)Map_Adr;
	

	for( i = 0; i < suui; i++ ) {
		for( j = 0; j < suuj; j++ ) {
			*VRAM++ = (*Map_Data | paloff) + mapoff;
			Map_Data++;
		}
		VRAM += (64 - suuj);
	}
}

//---------------------------------------------------------------------------------------------------------------

void Pal2CRAM( Uint16 *Pal_Data , void *Col_Adr , Uint32 suu )
{
	Uint16 i;
	Uint16 *VRAM;

	VRAM = (Uint16 *)Col_Adr;

	for( i = 0; i < suu; i++ )
		*(VRAM++) = *(Pal_Data++);
}


//--------------------------------------------------------------------------------------------------------------
void	_spr2_transfercommand(){

	memcpy(aVRAM,sprites,sizeof( sprites ) );
}
//-------------------------------------------------------------------------------------------------------------------------------------
void	_spr2_transferimage(int nb, void	*image, Uint32	size ){
//sizeof(cel_mario)
	memcpy(&aVRAM[4096+nb*size],image,size );
//	memcpy(&aVRAM[512+nb*size],image,size );
}
//--------------------------------------------------------------------------------------------------------------
void	_spr2_initialize( void ){

	set_imask(0);

	SCL_Vdp2Init();
    SCL_SetPriority(SCL_SP0|SCL_SP1|SCL_SP2|SCL_SP3|
                    SCL_SP4|SCL_SP5|SCL_SP6|SCL_SP7,7);

    SCL_SetSpriteMode(SCL_TYPE1,SCL_MIX,SCL_SP_WINDOW);
//    SCL_SetColRamMode(SCL_CRM15_2048);
    SCL_SetColRamMode(SCL_CRM15_1024);
    
    SPR_Initial(&aVRAM);

	SetVblank();
//	set_imask(0);
    
//    SCL_SetFrameInterval(-1 );
    SCL_SetFrameInterval(1 );
    SCL_DisplayFrame();    

	SCL_AllocColRam(SCL_NBG1,16,OFF); 
   	SCL_SetColRam(SCL_NBG1,0,16,palette);    
	
	SCL_SetDisplayMode( SCL_NON_INTER, SCL_240LINE, SCL_NORMAL_A );
	SPR_SetTvMode( SPR_TV_NORMAL, SPR_TV_320X240, OFF );
	SPR_SetEraseData( 0x0000, 0, 0, 320-1 ,240-1 );

	SCL_SetSpriteMode(SCL_TYPE0,SCL_MIX,SCL_SP_WINDOW);

	SCL_SetPriority(SCL_NBG1,6);
	SCL_SetPriority(SCL_NBG2,3);
	SCL_SetPriority(SCL_NBG0,5);
    SCL_SetPriority(SCL_SPR,4);

    /* Enable line and vertical cell scroll for NBG0-1 */
// (*(Uint16 *)0x25F8009A) = 0x0303; 
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ss_main(void)
{
//ss main ok
//	Uint16	dummy_pad = 0;
	int i=0;
	int action = 0;
//    unsigned char *tno;
	
    SetVblank();
    
    CdUnlock();    
    
   InitCD();     // init GFS
   InitCDBlock();     // init lecture CD audio 
   sndInit();  // chargement driver son

	_spr2_initialize();
	initSprites();    
	initLayers();
	
 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,32,16,288-1,208-1);
// 	SCL_SetWindow(SCL_W1,SCL_NBG1,SCL_NBG1,SCL_NBG0,0x30,16,256+48-1,192+16-1);
//PlayMusic(*((unsigned char *)0x06000CCD)));
//  tno = (unsigned char *) 0x6000CCD;

//  PlayMusic(tno[0]);
	pcm_size[0]=LoadFile("JUMP.PCM",pcm_sound[0]);
	pcm_size[1]=LoadFile("COIN.PCM",pcm_sound[1]);

	PcmLoad(0);
	PcmLoad(1);

  while(1)
  {
      switch (action)
      {
             case 0 : //loadBackground(pal_title,cel_title,map_title,64,8,59648);    
							initSprites();
//							getmario(); remplacé par init sprites
//							getinputs();
//							startscreen();
							main2();
                       action++;
                       
                       break;  
                       
             case 1 :  i++;
//                       action = displayTextMainMenu(&i);
                       break;
                       
             case 2 :  loadBackground(pal_title,cel_title,map_title,64,8,59648);   
                       action = displayTextSubMenu(&i);
                       break;
                       
             case 3 :  //nplayers = 1;
//                       action = game();
                       break;
                       
             case 4 :  //nplayers = 2;
//                       action = game();
                       break;
             
             case 5 :  action = displayConfiguration(&i);
                       break;
             
             case 6 :  action = displayTextCredits(&i);
                       break;
             
             default:
                     action=3;                     
                     break;
      }
//      SCL_DisplayFrame();  
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
/*
unsigned char update_input(void)
{
    static Uint16 pad_asign[]={
	PER_DGT_U,
	PER_DGT_D,
	PER_DGT_R,
	PER_DGT_L,
	PER_DGT_A,
	PER_DGT_B,
	PER_DGT_S,
	PER_DGT_TR,
	PER_DGT_TL,
};
	Bool result;
	int i=0;
	result = FALSE;
	byte temp = 0xFF;

if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
{
	pltriggerE[0] = pltrigger[0];
	pltrigger[0]  = PER_GetTrigger( device );
	pltriggerE[0] = (pltrigger[0]) ^ (pltriggerE[0]);
	pltriggerE[0] = (pltrigger[0]) & (pltriggerE[0]);

			for(i=0;i<9;i++)
			{
           		if((pltrigger[0] & pad_asign[i])!=0)
			    {			   
//                   switch(pad_asign[i])
                   switch(pltrigger[0] & pad_asign[i] )
	               {
	                    case PER_DGT_U: 
		                temp &= ~0x01;
			            break;

			            case PER_DGT_D:
		                temp &= ~0x02;
			            break;

			            case PER_DGT_R:
		                temp &= ~0x08;
			            break;

			            case PER_DGT_L:
		                temp &= ~0x04;
			            break;

			            case PER_DGT_A:
		                temp &= ~0x10;
			     		break;

			            case PER_DGT_B:
		                temp &= ~0x20;
						break;

					    default:					        
						break;
					}
				}
              }					
		}
		else
			pltrigger[0] = pltriggerE[0] = 0;
    return temp;
}
*/
//--------------------------------------------------------------------------------------------------------------
void VDP2_InitVRAM(void)
{
	/* Variables. */

	Uint32	loop;
	Uint32	maxloop;

	loop = 0;
	maxloop = 1024*512;
//	maxloop = BITMAP_PIXEL_WIDTH * BITMAP_PIXEL_HEIGHT;

	while (loop < maxloop)
	{
		*((Uint32 *) (SCL_VDP2_VRAM_A0 + loop)) = 0;
		*((Uint32 *) (SCL_VDP2_VRAM_B0 + loop)) = 0;
		loop += 4;
	}
}
//--------------------------------------------------------------------------------------------------------------
void initLayers(void)
{

//    SclConfig	config;
    Uint16	CycleTb[]={
/*           
//     0x4455,0x66FF,
 0xff44,0x5566,
      0x02ff,0xFFFF,
     0xffff,0xffff,
     0xffff,0xffff,     
     */
/*
		0x55ff, 0xffff, //A1   //nbg1 bitmap
//		0xeeee, 0xeeee,	//A0       ///VBT 29/12/2006 acncienne valeur
		0xffff,0xffff,
//		0x0022,0x4466,   //B1  //nbg0/nbg2 tiles
//		0x0022,0x4466,   //B1  //nbg0/nbg2 tiles
        0x0244,0xee66,   //B1  //nbg0/nbg2 tiles
//        0xf266, 0xffff,   //B1  //nbg0/nbg2 tiles
		0xeeee,0xeeee  //B0    //nbg0/nbg2 map

*/
		0x55ff, 0xffff, //A1   //nbg1 bitmap
//		0xeeee, 0xeeee,	//A0       ///VBT 29/12/2006 acncienne valeur
		0xffff,0xffff,
//		0x0022,0x4466,   //B1  //nbg0/nbg2 tiles
//		0x0022,0x4466,   //B1  //nbg0/nbg2 tiles
        0x0244,0xff66,   //B1  //nbg0/nbg2 tiles
//        0xf266, 0xffff,   //B1  //nbg0/nbg2 tiles
		0xffff,0xffff  //B0    //nbg0/nbg2 map



/*
		0x55ee, 0xeeee,	//A0
		0xeeee, 0xeeee, //A1
		0xeeee, 0xeeee,	//A0		
//		0x0f44,0xf266,   //B1
		0xeeee,0xeeee  //B0
*/	};

/*
#define		NBG0_CEL_ADR		( SCL_VDP2_VRAM_B1 )
#define		NBG0_MAP_ADR		( SCL_VDP2_VRAM_B0 )
//#define		NBG1_COL_ADR		( VDP2_COLRAM + 0x00200 )
#define		NBG2_CEL_ADR		( SCL_VDP2_VRAM_B1 + 0x20000 )//0x1D400 )//( SCL_VDP2_VRAM_B1 + 0x50000 )
#define		NBG2_MAP_ADR		( SCL_VDP2_VRAM_B0 + 0x12000 )

*/

/*
voir page 58 vdp2
voir plutot p355 vdp2
*/

//VDP2_RAMCTL = 0x0300;

 	SclConfig	scfg;
	int         i;
//	Uint16	dummy_pad = 0;

	SCL_InitConfigTb(&scfg);
	scfg.dispenbl      = ON;
	scfg.charsize      = SCL_CHAR_SIZE_2X2;//OK du 1*1 surtout pas toucher
	scfg.pnamesize     = SCL_PN1WORD;
	scfg.flip          = SCL_PN_10BIT; 
	scfg.platesize     = SCL_PL_SIZE_1X1;
	scfg.coltype       = SCL_COL_TYPE_256;
	scfg.datatype      = SCL_CELL;
	scfg.patnamecontrl =  0x0008;//((NBG0_CEL_ADR/64)>>10)&0x0F;//0x000c;// VRAM B1 ‚ÌƒIƒtƒZƒbƒg 
	for(i=0;i<4;i++)   
	   scfg.plate_addr[i] = NBG0_MAP_ADR;
	SCL_SetConfig(SCL_NBG0, &scfg);

	SCL_InitConfigTb(&scfg);
	scfg.dispenbl 	 = ON;
	scfg.bmpsize 		 = SCL_BMP_SIZE_512X256;
	scfg.coltype 		 = SCL_COL_TYPE_256;
	scfg.datatype 	 = SCL_BITMAP;
	scfg.mapover       = SCL_OVER_0;
//	for(i=0;i<4;i++)  
		scfg.plate_addr[0] = SCL_VDP2_VRAM_A1;
	SCL_SetConfig(SCL_NBG1, &scfg);

	SCL_InitConfigTb(&scfg);
	scfg.dispenbl      = ON;
	scfg.charsize      = SCL_CHAR_SIZE_2X2;//OK du 1*1 surtout pas toucher
	scfg.pnamesize     = SCL_PN1WORD;
	scfg.flip          = SCL_PN_10BIT; 
	scfg.platesize     = SCL_PL_SIZE_1X1;
	scfg.coltype       = SCL_COL_TYPE_256;
	scfg.datatype      = SCL_CELL;
	scfg.patnamecontrl = 0x000c;//0x000c;//((NBG2_CEL_ADR/64)>>12)&0x0F;//0x000c;//0xC00C;//((NBG2_CEL_ADR/64)>>10)&0x0F;// VRAM B1 ‚ÌƒIƒtƒZƒbƒg 
	for(i=0;i<4;i++)   
		scfg.plate_addr[i] = NBG2_MAP_ADR;
	SCL_SetConfig(SCL_NBG2, &scfg);	
	

	SCL_SetCycleTable(CycleTb);	

	PER_SMPC_RES_ENA();// ƒŠƒZƒbƒgƒ{ƒ^ƒ“—LŒø 
	FNT_SetBuffSize(512,256,1);	

    SCL_Open(SCL_NBG1);
	SCL_MoveTo(FIXED(0), FIXED(0),0);
	SCL_Close();
	
    SCL_Open(SCL_NBG0);
	SCL_MoveTo(FIXED(0), FIXED(0),0);
	SCL_Close();	
	
    SCL_Open(SCL_NBG2);
	SCL_MoveTo(FIXED(0), FIXED(0),0);
	SCL_Close();	
}
//--------------------------------------------------------------------------------------------------------------
void wait(long wait)
{
     long i=0;
     while(i<wait)
     {
         i++;
     }
}
//--------------------------------------------------------------------------------------------------------------
void initSprites(void)
{
    int i;
    
    SCL_AllocColRam(SCL_SPR,256,OFF);
    SCL_SetColRam(SCL_SPR,0,256,pal_mario);        
//    SCL_SetColRam(SCL_SPR,0,256,pal_gold);        

    sprites[0].control    = (JUMP_NEXT | FUNC_SCLIP);
    sprites[0].link       = 0;        
    sprites[0].drawMode   = 0;
    sprites[0].color      = 0;
    sprites[0].charAddr   = 0; //0x0010*(i+1);  //allocBlock(w);//
    sprites[0].charSize   = 0;//charSize; //0x0108,  /* x*y = 8*16 : 0x0110 	 x*y = 8*8 : 0x0108 */       
    sprites[0].ax         = 0;
    sprites[0].ay         = 0;
    sprites[0].bx         = 0;
    sprites[0].by         = 0;
    sprites[0].cx         = 320-1;
    sprites[0].cy         = 240-1;
    sprites[0].dx         = 0;
    sprites[0].dy         = 0;        
    sprites[0].grshAddr   = 0;
    sprites[0].dummy      = 0;    

    sprites[1].control    =  (JUMP_NEXT | FUNC_LCOORD);
    sprites[1].link       = 0;        
    sprites[1].drawMode   = 0;
    sprites[1].color      = 0;
    sprites[1].charAddr   = 0;
    sprites[1].charSize   = 0;
    sprites[1].ax         = 32;
    sprites[1].ay         = 32;
    sprites[1].bx         = 0;
    sprites[1].by         = 0;
    sprites[1].cx         = 0;
    sprites[1].cy         = 0;        
    sprites[1].dx         = 0;
    sprites[1].dy         = 0;        
    sprites[1].grshAddr   = 0;
    sprites[1].dummy      = 0;    

    sprites[2].control    = (JUMP_NEXT | FUNC_UCLIP);
    sprites[2].link       = 0;        
    sprites[2].drawMode   = 0;
    sprites[2].color      = 0;
    sprites[2].charAddr   = 0; 
    sprites[2].charSize   = 0;
    sprites[2].cx         = 0;
    sprites[2].cy         = 0;
    sprites[2].bx         = 0;
    sprites[2].by         = 0;
    sprites[2].ax         = 320-1;
    sprites[2].ay         = 240-1;
    sprites[2].dx         = 0;
    sprites[2].dy         = 0;        
    sprites[2].grshAddr   = 0;
    sprites[2].dummy      = 0;    

    for (i=3;i<SPRITES;i++)
    {
        
        
        sprites[i].control    = 0;
        sprites[i].link       = 0;        
        sprites[i].drawMode   = 0;                
        sprites[i].color      = 0;                
        sprites[i].charAddr   = 0;                
        sprites[i].charSize   = 0;
        sprites[i].ax         = 0;
        sprites[i].ay         = 0;
        sprites[i].bx         = 0;
        sprites[i].by         = 0;
        sprites[i].cx         = 0;
        sprites[i].cy         = 0;
        sprites[i].dx         = 0;
        sprites[i].dy         = 0;
        sprites[i].grshAddr   = 0;
        sprites[i].dummy      = 0;

    }
    
    sprites[SPRITES-1].control    = (CTRL_END);
    
	_spr2_transferimage(0,cel_mario, 256);
	_spr2_transferimage(1,cel_mario+256, 256);	
	_spr2_transferimage(2,cel_mario+512, 256);
	_spr2_transferimage(3,cel_mario+768, 256);	
	_spr2_transferimage(4,cel_mario+1024, 256);	
	_spr2_transferimage(5,cel_mario+1280, 256);	
	_spr2_transferimage(6,cel_mario+1536, 256);
	_spr2_transferimage(7,cel_mario+1792, 256);	  

//	_spr2_transferimage(8,cel_mario+2048, 256);	 	
    
//            _spr2_transfercommand();  
            
            SCL_DisplayFrame();    
}
     
static void sndInit(void)
{
	SndIniDt 	snd_init;
	char sound_map[]={0xFF,0xFF};

#ifndef ACTION_REPLAY
	GFS_Load(GFS_NameToId(SDDRV_NAME),0,(void *) SDDRV_ADDR,SDDRV_SIZE);
	SND_INI_PRG_ADR(snd_init) = (Uint16 *)SDDRV_ADDR;
	SND_INI_PRG_SZ(snd_init)  = (Uint16)  SDDRV_SIZE;
#else
	
	SND_INI_PRG_ADR(snd_init) = (Uint16 *)snddrv;
	SND_INI_PRG_SZ(snd_init)  = (Uint16)  sizeof(snddrv);
#endif

	SND_INI_ARA_ADR(snd_init) 	= (Uint16 *)sound_map;
	SND_INI_ARA_SZ(snd_init) 	= (Uint16)sizeof(sound_map);

	SND_Init(&snd_init);
	SND_ChgMap(0);

    SND_SetCdDaLev(7,7);                        /* CD-DAƒŒƒxƒ‹‚Ìİ’è         */
    SND_SetCdDaPan(0,0);                        /* CD-DA‚ÌPANİ’è            */
    SND_SetTlVl(15);                            /* Total Volume‚Ìİ’è        */
    SND_RESET_INT();                            /* Š„‚İƒXƒe[ƒ^ƒXƒŠƒZƒbƒg  */
//SND_SET_ENA_INT(SND_INT_PCM_ADR);  



	PCM_MeInit();
	PcmCreatePara	para;
	PcmInfo 		info;
	PcmStatus	*st;
	static PcmWork g_movie_work;
	static PcmWork g_movie_work2;

	PCM_PARA_WORK(&para) = (struct PcmWork *)&g_movie_work;
	PCM_PARA_RING_ADDR(&para) = (Sint8 *)g_movie_buf;
	PCM_PARA_RING_SIZE(&para) = RING_BUF_SIZE;
	PCM_PARA_PCM_ADDR(&para) = PCM_ADDR;
	PCM_PARA_PCM_SIZE(&para) = PCM_SIZE;
 	st = &g_movie_work.status;

	memset((Sint8 *)g_movie_buf,0,11025L*4);

	st->need_ci = PCM_ON;
	PCM_INFO_FILE_TYPE(&info) = PCM_FILE_TYPE_NO_HEADER;			
	PCM_INFO_DATA_TYPE(&info)=PCM_DATA_TYPE_RLRLRL;//PCM_DATA_TYPE_LRLRLR;
	PCM_INFO_FILE_SIZE(&info) = 11025L;//*2;
	PCM_INFO_CHANNEL(&info) = 0x01;
	PCM_INFO_SAMPLING_BIT(&info) = 8;
	PCM_INFO_SAMPLING_RATE(&info)	= 11025L;
	PCM_INFO_SAMPLE_FILE(&info) = 11025L;//*2;
			
	pcm[0] =createHandle(&para);
	PCM_SetPcmStreamNo(pcm[0], 0); // vbt pas utile ?

	PCM_SetInfo(pcm[0], &info);
	PCM_ChangePcmPara(pcm[0]);

	if (pcm[0] == NULL) {
		return;
	}


// vbt : lazy work :)

	PCM_PARA_WORK(&para) = (struct PcmWork *)&g_movie_work2;
	PCM_PARA_RING_ADDR(&para) = (Sint8 *)g_movie_buf2;
	PCM_PARA_RING_SIZE(&para) = RING_BUF_SIZE;
	PCM_PARA_PCM_ADDR(&para) = PCM_ADDR2;
	PCM_PARA_PCM_SIZE(&para) = PCM_SIZE;
 	st = &g_movie_work2.status;

	memset((Sint8 *)g_movie_buf2,0,11025L*4);

	st->need_ci = PCM_ON;
	PCM_INFO_FILE_TYPE(&info) = PCM_FILE_TYPE_NO_HEADER;			
	PCM_INFO_DATA_TYPE(&info)=PCM_DATA_TYPE_RLRLRL;//PCM_DATA_TYPE_LRLRLR;
	PCM_INFO_FILE_SIZE(&info) = 11025L;//*2;
	PCM_INFO_CHANNEL(&info) = 0x01;
	PCM_INFO_SAMPLING_BIT(&info) = 8;
	PCM_INFO_SAMPLING_RATE(&info)	= 11025L;
	PCM_INFO_SAMPLE_FILE(&info) = 11025L;//*2;
			
	pcm[1] =createHandle(&para);
	PCM_SetPcmStreamNo(pcm[1], 1); // vbt pas utile ?

	PCM_SetInfo(pcm[1], &info);
	PCM_ChangePcmPara(pcm[1]);

	if (pcm[1] == NULL) {
		SYS_Exit(0);
		return;
	}






/*
	while(1)
	{
		PCM_Task(pcm);
	}
*/
}

static PcmHn createHandle(PcmCreatePara *para)
{
	PcmHn pcm;

	pcm = PCM_CreateMemHandle(para);
	if (pcm == NULL) {
		return NULL;
		SYS_Exit(0);
	}
//	PCM_NotifyWriteSize(pcm, 11025*2);
	PCM_NotifyWriteSize(pcm, 11025);
//	PCM_NotifyWriteSize(pcm, 2048);

	return pcm;
}

 void PcmStart(int pcm_number)
 {
		if (PCM_GetPlayStatus(pcm[pcm_number]) != PCM_STAT_PLAY_TIME) 
//		if (PCM_GetPlayStatus(pcm) != PCM_STAT_PLAY_TIME) 
		{
			PCM_Start(pcm[pcm_number]);
//			PCM_Start(pcm);
		}
 }

 void PcmStop(int pcm_number)
 {
//		if (PCM_GetPlayStatus(pcm[pcm_number]) == PCM_STAT_PLAY_END) 
//		if (PCM_GetPlayStatus(pcm) == PCM_STAT_PLAY_END) 
		{
//			graphstring(130,100,"stop playing",0,NULL);
			PCM_Stop(pcm[pcm_number]);
//			PCM_Stop(pcm);
		}
 }

 
 void PcmTask(int pcm_number)
 {
//	PCM_Task(pcm);
	PCM_Task(pcm[pcm_number]);
 }

void PcmLoad(int pcm_number)
{
	PcmInfo 		info;
	//char pcm_sound[5][0x10000];

	PCM_INFO_FILE_TYPE(&info) = PCM_FILE_TYPE_NO_HEADER;			
	PCM_INFO_DATA_TYPE(&info)=PCM_DATA_TYPE_RLRLRL;//PCM_DATA_TYPE_LRLRLR;
	PCM_INFO_FILE_SIZE(&info) = pcm_size[pcm_number]*2;
	PCM_INFO_CHANNEL(&info) = 0x01;
	PCM_INFO_SAMPLING_BIT(&info) = 8;
	PCM_INFO_SAMPLING_RATE(&info)	= 11025L;
	PCM_INFO_SAMPLE_FILE(&info) = pcm_size[pcm_number];//11025L;//*2;
	PCM_SetInfo(pcm[pcm_number], &info);
//	PCM_SetInfo(pcm, &info);

//	PCM_SetLoop(pcm[pcm_number], 20);
//	if (pcm_number==0)
		memcpy(g_movie_buf+0x40000*pcm_number,pcm_sound[pcm_number],pcm_size[pcm_number]);
//	else
//		memcpy(g_movie_buf2,pcm_sound[pcm_number],pcm_size[pcm_number]);
}

void wait_seconds(int seconds)
{
  int wait[3];

  wait[0]=(t[0]>>4)*10 + (t[0] & 0x0F);
  wait[1]=wait[0];
  wait[2]=0;

  while(wait[2]!=seconds)
  {
	t = PER_GET_TIM();
    wait[0]=(t[0]>>4)*10 + (t[0] & 0x0F);

    if(wait[0]!=wait[1])
    {
      wait[1]=wait[0];
      wait[2]++;
    }
  }
}


/********************************************************************
 * ƒ‰ƒCƒ“ƒpƒ‰ƒ[ƒ^ƒe[ƒuƒ‹‚Ìƒ_ƒ~[‚ğì¬‚·‚é                       *
 ********************************************************************/
#define X_SIZE		320
#define Y_SIZE		240
#define Y_SIZE_H	240

void SetAutoLinePara(Uint16 SclNum)
{
    Fixed32 count;

	double ra;
	double r;
	long v;
	
	
	ra = 2*3.1415/0.25;
	r = 0;


    SCL_InitLineParamTb(&lp);

    lp.delta_enbl=OFF;
    lp.v_enbl=OFF;
    lp.h_enbl=ON;
    lp.line_addr=SCL_VDP2_VRAM_A0;
    lp.interval=0;
/*
    for(count=0;count<Y_SIZE;count++)
    {
    	lp.line_tbl[count].h = (2*MTH_Sin(r))<<16;
//    	lp.line_tbl[count].v = FIXED(count/4+MTH_Sin(count*2)); //FIXED(count)/2;
//	lp.line_tbl[count].v = FIXED(count)*2;
//	lp.line_tbl[count].dh
//	= DIV_FIXED((FIXED(X_SIZE)-(2* lp.line_tbl[count].h)),FIXED(X_SIZE));
		r += ra;
    }
*/

    SCL_Open(SclNum);
	SCL_SetLineParam(&lp);
    SCL_Close();
    SCL_DisplayFrame();

}

void changeLinePara(Uint16 SclNum,int delta)
{
    Fixed32 count;


	double ra;
	double r;
	long v;
	
	
//	ra = 2.0 * 3.1415 / 128;
	ra =  6.283/128;
	r = 0;


    for(count=1;count<Y_SIZE_H;count++)
    {
//		if(delta%2)
    	lp.line_tbl[count].h = sin(r+delta)*16;
    	lp.line_tbl[count].h <<= 16;
		r += ra;
    }
    SCL_Open(SclNum);
	SCL_SetLineParam(&lp);
    SCL_Close();
    SCL_DisplayFrame();

}



/********************************************************************
 * ƒ‰ƒCƒ“ƒpƒ‰ƒ[ƒ^ƒe[ƒuƒ‹‚ğ–³Œø‚É‚·‚é                             *
 ********************************************************************/
void ClrLinePara(Uint16 SclNum)
{
/*
	SclLineparam lp;

    SCL_InitLineParamTb(&lp);

    SCL_Open(SclNum);
	SCL_SetLineParam(&lp);
    SCL_Close();
    SCL_DisplayFrame();

*/
	int count;

    for(count=1;count<Y_SIZE_H;count++)
    {
//		if(delta%2)
    	lp.line_tbl[count].h = 0;
    	lp.line_tbl[count].h <<= 16;

    }
    lp.h_enbl=OFF;
    SCL_Open(SclNum);
	SCL_SetLineParam(&lp);
    SCL_Close();
    SCL_DisplayFrame();




}



