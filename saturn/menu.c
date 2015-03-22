#include "saturn.h"
#include "main.h"



#include "saturn/title/mariomap.cel"
#include "saturn/title/mariomap.map"
#include "saturn/title/mariomap.pal"
#include "saturn/title/cloud.cel"
#include "saturn/title/cloud.map"
#include "saturn/title/cloud.pal"


//extern Uint16 map_foreground[];
extern Uint16 *pal_title2, *map_title2;
extern Uint8 * cel_title2;
extern SysDevice	*device;
extern SysPort		*__port;
extern  trigger_t	        pltrigger[2],pltriggerE[2];
//-----------------------------------------------------------------------------
void restoreForeground()
{
    Uint16 map_save[] ={
    	0x0000,0x0002,0x0004,0x0006,0x0000,0x0002,0x0004,0x0006,
    	0x0000,0x0002,0x0004,0x0006,0x0000,0x0002,0x0004,0x0006,
    	0x0008,0x0000,0x0002,0x0004,0x0006,0x0008,0x0000,0x0000,
    	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
    };
    
    int i = 0 , j = 0, k = 0, l = 0;
/*    
    for ( l = 0 ; l < 2 ; l++ )
    {
        for ( j = 0 ; j < 0x180 ; j += 0x40 )
        {
            for (i = 0; i < 32;i++)
            {
                map_foreground[k]=map_save[i]+j;
                k++;
            }
        }
    }
*/
}
//-----------------------------------------------------------------------------
void loadBackground(Uint8 *palette,Uint16 *cell,Uint16 *map,Uint8 blockx,Uint8 blocky,Uint32 size)
{
     
	SCL_AllocColRam(SCL_NBG0,256,OFF); 
   	SCL_SetColRam(SCL_NBG0,0,256,palette); 
            
    Cel2VRAM	(cell , (void *)NBG0_CEL_ADR , size) ; 
    Map2VRAM	(map  , (void *)NBG0_MAP_ADR , blockx , blocky, 0 , 0) ;

}
//-----------------------------------------------------------------------------
void loadForeground(Uint8 *palette,Uint16 *cell,Uint16 *map,Uint8 blockx,Uint8 blocky,Uint32 size)
{
     
	SCL_AllocColRam(SCL_NBG2,256,OFF); 
   	SCL_SetColRam(SCL_NBG2,0,256,palette); 
                                
    Cel2VRAM	(cell , (void *)NBG2_CEL_ADR , size) ; 
    Map2VRAM	(map  , (void *)NBG2_MAP_ADR , blockx , blocky, 0 , 0) ;

}
/*
//-----------------------------------------------------------------------------
int displayTextMainMenu(int *i)
{

    unsigned char *tno;
    char tutu[80];
//    tno = (unsigned char *) 0x6000CCD;
/*
	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"C4 - 2006   www.rockin-b.de",56,200,9,10,11,0);	
	
//    sprintf(tutu,"track number : %02d",tno[0]);
    
//	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
//				(Uint8 *)tutu,56,8,9,10,11,0);	    
/               
	if (*i<30)
       FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"PRESS START BUTTON",87,140,5,6,7,0);
    else if(*i==60)
      *i = -1;
    else if (*i>29)
       FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"PRESS START BUTTON",87,140,0,0,0,0);
    			
	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"ONE OR TWO PLAYERS",87,156,1,2,3,0);
				
	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"2005 - VBT",119,212,9,10,11,0);					
			
    return getControlMainMenu(i);
}


//-----------------------------------------------------------------------------
int displayTextSubMenu(int *i)
{
    int selected[4];
    int value;
    selected[0] = (*i == 0) ? 4 : 0;
    selected[1] = (*i == 1) ? 4 : 0;
    selected[2] = (*i == 2) ? 4 : 0;
    selected[3] = (*i == 3) ? 4 : 0;  
    
	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"C4 - 2005   www.rockin-b.de",56,8,9,10,11,0);	      
    
     FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
			(Uint8 *)"1 PLAYER",115,140,     5-selected[0],6-selected[0],7-selected[0],0);

     FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
			(Uint8 *)"2 PLAYERS",115,156,    5-selected[1],6-selected[1],7-selected[1],0);

     FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
			(Uint8 *)"CONFIGURATION",115,172,5-selected[2],6-selected[2],7-selected[2],0);

     FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
			(Uint8 *)"CREDITS",115,188,      5-selected[3],6-selected[3],7-selected[3],0);

	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)"2005 - VBT",119,212,9,10,11,0);				

    value = getControlSubMenu(i); 

    return value;
}
*/
//-----------------------------------------------------------------------------
int displayTextCredits(int *i)
{

	Uint16 *VRAM;    
	int x,j;
    VRAM = (Uint16 *)NBG0_MAP_ADR;

	for( x = 0; x < 8; x++ ) 
    {
		for( j = 0; j < 64; j++ ) 
			*VRAM++ = 0x0000;
//		VRAM += (64);
	}

 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,0,0,0,0);

		  graphstring(160,118,"                                      ",0,NULL);
		  graphstring(80,131,"                                      ",0,NULL);
		  graphstring(80,141,"                                      ",0,NULL);
		  graphstring(80,151,"                                      ",0,NULL);
		  graphstring(80,162,"                                      ",0,NULL);
    
    graphstring(88,24,"SPECIAL THANKS TO :",0,NULL);

    graphstring(34,54,"- ROCKIN'-B for the C4 contest\n  and all his work on saturn\n" \
				"- People and shop who offered prizes\n" \
				"- Maxim of smspower.org for his\n  4BPP tile editor\n" \
				"- CyberWarriorX for PER_GET_TIM help\n"\
				"- All people of segaxtreme channel\n"\
				"- All people of SX forums, admins\n"\
				"- All people of smspower channel\n"\
				"- All people of yabause channel\n"\
				"- Antime for Saturn documentation\n" \
				"- All contributors to the Saturn \n  Dev scene\n" \
				"- All C4 contestants");
                				
//    return getControlCreditsMenu(i);
	wait_key(PER_DGT_B);
}
//-----------------------------------------------------------------------------
int displayConfiguration(int *i)
{

	Uint16 *VRAM;    
	int x,j;

	VRAM = (Uint16 *)NBG0_MAP_ADR;   //SCL_VDP2_VRAM_A1

	for( x = 0; x < 8; x++ ) 
    {
		for( j = 0; j < 64; j++ ) 
			*VRAM++ = 0x0000;
//		VRAM += (64);
	}

 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,0,0,0,0);

  graphstring(160,118,"                                ",0,NULL);
  graphstring(120,146,"                                ",0,NULL);
  graphstring(120,162,"                                ",0,NULL);

//	FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
//				(Uint8 *)"C4 - 2006   www.rockin-b.de",56,8,9,10,11,0);	
    
		  graphstring(160,118,"                                      ",0,NULL);
		  graphstring(80,131,"                                      ",0,NULL);
		  graphstring(80,141,"                                      ",0,NULL);
		  graphstring(80,151,"                                      ",0,NULL);
		  graphstring(80,162,"                                      ",0,NULL);
    

    graphstring(88,24,"CONFIGURATION",0,NULL);

    graphstring(34,54,"- UP :   MOVE UP\n" \
				"- DOWN : MOVE DOWN\n" \
				"- RIGHT :MOVE RIGHT\n" \
				"- LEFT : MOVE LEFT\n" \
				"- START  START GAME\n"\
                "         PAUSE THE GAME\n" \
				"- A :    RUN \n"\
				"- B :    JUMP\n         BACK TO TITLE\n"\
				"- X :    SHOW THIS HELP\n"\
				"- Y :    SHOW CREDITS\n"
				,0,NULL);

	wait_key(PER_DGT_B);
/*
		device = PER_GetDeviceR( &__port[0], 0 );

		while((pltrigger[0] & PER_DGT_B)==0)
		{
			pltrigger[0]  = PER_GetTrigger( device );
			checkExitHere(pltrigger[0]);
		}

		for (j=17;j<210 ;j+=8 )
		{
		    graphstring(32, j,"                                                ",0,NULL);
		}

		SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,32,16,288-1,208-1);
*/
}


void wait_key(Uint8 key)
{
	int j;

	device = PER_GetDeviceR( &__port[0], 0 );

	while((pltrigger[0] & PER_DGT_B)==0)
	{
		pltrigger[0]  = PER_GetTrigger( device );
		checkExitHere(pltrigger[0]);
	}

	for (j=17;j<210 ;j+=8 )
	{
		graphstring(32, j,"                                                ",0,NULL);
	}

	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,32,16,288-1,208-1);
}


//-----------------------------------------------------------------------------
void ending_screen()
{
	int ending=1;
	int delta=0;
	int text_scroll=-1;

	StopMusic();
	PlayMusic(9);
	SCL_SetPriority(SCL_NBG1,6);
	SCL_SetPriority(SCL_NBG2,5);
	SCL_SetPriority(SCL_NBG0,3);
    SCL_SetPriority(SCL_SPR,2);
/*
	memset(SCL_VDP2_VRAM_A0,0x00,512*512);
	memset(SCL_VDP2_VRAM_A1,0x00,512*512);
	memset(SCL_VDP2_VRAM_B0,0x00,512*512);
	memset(SCL_VDP2_VRAM_B0,0x00,512*512);
	memset(NBG0_MAP_ADR,0x00,1024);
	memset(NBG2_MAP_ADR,0x00,1024);
*/
	SPR_SetEraseData( 0x0000, 0, 0, 320-1 ,240-1 );

	loadBackground(pal_mariomap,cel_mariomap,map_mariomap,64,8,126208);   

	 SCL_SetColRam(SCL_NBG2,0,256,pal_cloud); 
	 Cel2VRAM	(cel_cloud , (void *)NBG2_CEL_ADR , sizeof(cel_cloud)) ; 
	 Map2VRAM	(map_cloud  , (void *)NBG2_MAP_ADR , 64 , 8, 0 , 0) ;

SetAutoLinePara(SCL_NBG0);
//SCL_SetMosaic(SCL_NBG2|SCL_NBG1,6,6);
SCL_SetColMixRate(SCL_NBG0|SCL_NBG2,4);
SCL_EnableBlur(SCL_NBG0|SCL_NBG2);
//SCL_SetShadowBit(SCL_NBG0|SCL_NBG2);
		graphstring(0,1,"                                          ",0,NULL);
		graphstring(0,10,"                                          ",0,NULL);

 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,0,0,320-1,240-1);
	while(ending)
	{

		changeLinePara(SCL_NBG0,delta);
		delta+=1;
		if (delta>=320)
		{
			delta=0;
		}
		SCL_Open(SCL_NBG2);
		SCL_Move(FIXED(-8), FIXED(0),0);/* Home Position */
		SCL_Close();

if(128-text_scroll>0)
    graphstring(16,128-text_scroll,"Well done you have finished       \n",0,NULL);
if(138-text_scroll>0)
	graphstring(16,138-text_scroll,"my C4 entry for 2006                  \n",0,NULL);
if(148-text_scroll>0)
	graphstring(16,148-text_scroll,"                                                    \n",0,NULL);
if(158-text_scroll>0)
	graphstring(16,158-text_scroll,"I hope you noticed the progress \n",0,NULL);
if(168-text_scroll>0)
	graphstring(16,168-text_scroll,"I did since last year                     \n",0,NULL);
if(178-text_scroll>0)
	graphstring(16,178-text_scroll,"                                                    \n",0,NULL);
if(188-text_scroll>0)
	graphstring(16,188-text_scroll,"- CDDA playing                           \n",0,NULL);
if(198-text_scroll>0)
	graphstring(16,198-text_scroll,"- PCM playing                             \n",0,NULL);
if(208-text_scroll>0)
	graphstring(16,208-text_scroll,"- Transparency                                 \n",0,NULL);
if(218-text_scroll>0)
	graphstring(16,218-text_scroll,"- Mosaic                                             \n",0,NULL);
if(228-text_scroll>0)
	graphstring(16,228-text_scroll,"- Line scroll                                       \n",0,NULL);
if(238-text_scroll>0)
	graphstring(16,238-text_scroll,"                                                          \n",0,NULL);
if(248-text_scroll>0&& 248-text_scroll<240)
	graphstring(16,248-text_scroll,"Again a big thanks to Rockin'-B       \n",0,NULL);
if(258-text_scroll>0 && 258-text_scroll<240)
	graphstring(16,258-text_scroll,"for having organized this nice contest.\n",0,NULL);
if(268-text_scroll>0 && 268-text_scroll<240)
	graphstring(16,268-text_scroll,"I'll try to do better next year with        \n",0,NULL);
if(278-text_scroll>0 && 288-text_scroll<240)
	graphstring(16,278-text_scroll,"who knows maybe 3D ? Good luck to    \n",0,NULL);
if(288-text_scroll>0 && 288-text_scroll<240)
	graphstring(16,288-text_scroll,"everybody for the results.                   \n",0,NULL);
if(298-text_scroll>0 && 298-text_scroll<240)
	graphstring(16,298-text_scroll,"                                                          \n",0,NULL);
/*
if(308-text_scroll>0 && 308-text_scroll<240)
	graphstring(16,308-text_scroll,"                                                          \n",0,NULL);
*/
if(308-text_scroll>0 && 308-text_scroll<240)
	graphstring(16,308-text_scroll,"Best wishes for the new year.           \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                         THE END                 \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"\
									"                                                          \n"
		,0,NULL);


		if (text_scroll<1000)
		text_scroll+=10;

SCL_DisplayFrame();

if (text_scroll>=1000)
{
		memset(NBG0_MAP_ADR,0x00,1024);
		ending=0;
}


/*
		SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG3,SCL_NBG3,	0+text_scroll-1000,
																													0+text_scroll-1000,
																													288-1-text_scroll-1000,
																													208-1-text_scroll-1000);
		text_scroll++;
*/




	}
	StopMusic();
	graphstring(160,95,	"                                                          \n",0,NULL);
	graphstring(160,103,"                                                          \n",0,NULL);
	graphstring(160,111,"                                                          \n",0,NULL);
	graphstring(160,119,"                                                          \n",0,NULL);
	SCL_SetPriority(SCL_NBG1,6);
	SCL_SetPriority(SCL_NBG2,3);
	SCL_SetPriority(SCL_NBG0,5);
    SCL_SetPriority(SCL_SPR,4);
	SCL_DisplayFrame();
	SCL_SetColMixRate(SCL_NBG0|SCL_NBG2,0);
	SCL_DisplayFrame();

	ClrLinePara(SCL_NBG0);
 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,32,16,288-1,208-1);
	/*
	ClrLinePara(SCL_NBG0);
	SCL_SetPriority(SCL_NBG1,6);
	SCL_SetPriority(SCL_NBG2,3);
	SCL_SetPriority(SCL_NBG0,5);
    SCL_SetPriority(SCL_SPR,4);
	SCL_SetColMixRate(SCL_NBG0|SCL_NBG2,0);
 	SCL_SetWindow(SCL_W0,SCL_NBG0,SCL_NBG2,SCL_NBG2,32,16,288-1,208-1);
*/
/*	memset(SCL_VDP2_VRAM_A0,0x00,512*512);
	memset(SCL_VDP2_VRAM_A1,0x00,512*512);
	memset(SCL_VDP2_VRAM_B0,0x00,512*512);
	memset(SCL_VDP2_VRAM_B0,0x00,512*512);
*/
//	memset(NBG0_MAP_ADR,0x00,512);
//	memset(NBG2_MAP_ADR,0x00,1024);
}