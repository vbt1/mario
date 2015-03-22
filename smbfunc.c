#include "saturn/saturn.h"
#include "saturn/main.h"
#include "saturn/title/title2.cel"
#include "saturn/title/title2.map"
#include "saturn/title/title2.pal"
 /*
#include "saturn/title/mariomap.cel"
#include "saturn/title/mariomap.map"
#include "saturn/title/mariomap.pal"
*/
#include "saturn/sprites/block001.cel"
#include "saturn/levels/bgrnd001.cel"
#include "saturn/levels/bgrnd001.pal"
#include "saturn/sprites/block002.cel"
#include "saturn/levels/bgrnd002.cel"
#include "saturn/levels/bgrnd002.pal"
#include "saturn/sprites/block003.cel"
#include "saturn/levels/bgrnd003.cel"
#include "saturn/levels/bgrnd003.pal"
#include "saturn/sprites/block004.cel"
#include "saturn/levels/bgrnd004.cel"
#include "saturn/levels/bgrnd004.pal"


#define SPRITES 100
extern SprSpCmd sprites[SPRITES];
extern SysPort		*__port;
extern  SysDevice	*device;
extern trigger_t	        pltrigger[2],pltriggerE[2];
extern char pcm_sound[5][0x10000];
extern 	signed long pcm_size[5];
extern Uint16 *colBgAddr;
extern char pscore[7];
extern long high_score;
SclNorscl	Scl_n_reg;
extern     SclLineparam lp;
extern int first_display;


//SET UP ALL OF THE GRAPHICS AND OTHER JUNK//////////////////////////////////
void init()
{
  int loop;
//  x_set_mode(X_MODE_320x240,320);	//SET MODE X//
//  x_set_tripplebuffer(240);		//INSTALL TRIPPLE BUFFER//
//  install_new_key_handler();		//INSTALL KEYBOARD HANDLER//
//  x_install_vsync_handler(1);		//INSTALL VSYNC HANDLER//
  for (loop=0;loop<52;loop++)		//ALLOCATE MEM FOR GRAPHICS//
    if ((data.block[loop]=(char  *)malloc(258))==NULL)
      exitgame();
  for (loop=0;loop<3;loop++)
    if ((data.coin[loop]=(char  *)malloc(258))==NULL)
      exitgame();
  if ((bcoin=(cointype *)malloc(sizeof(cointype)))==NULL)
    exitgame();
  bcoin->next=NULL;
  if ((bscore=(scoretype *)malloc(sizeof(scoretype)))==NULL)
    exitgame();
  bscore->next=NULL;
  for (loop=0;loop<2;loop++)
  {
    player[loop].lives=3;
    player[loop].level=1;
    player[loop].screenx=0;
  }
}

//FILL SCREEN ///////////////////////////////////////////////////////////////
void fillscreen(int color)
{
//  x_rect_fill(32,0,288,224,HiddenPageOffs,color);
//		SCL_SetColRam(SCL_NBG2,0,256,); 
		memset(NBG2_MAP_ADR,0x00,1024);
}

//GET INPUTS FROM DATA FILES/////////////////////////////////////////////////
int getinputs()
{
//  FILE *in;
  int loop1,loop2,yinit,blocknum,backnum;
  signed long size;
  signed long fid;
  char levelfile[13],graphfile[13];
  int in2[4000];
  unsigned char ch;
  unsigned char in[4000];
  int i;

  strcpy(levelfile,"LEVEL000.DAT");
  levelfile[7]=player[curplay].level%10+48; // VBT virage temporaire
  if (player[curplay].level>9)
    levelfile[6]=player[curplay].level/10+48;

	fid =GFS_NameToId(levelfile);
	size=GetFileSize(fid);

     SCL_DisplayFrame();    
	GFS_Load(fid,0,(int *)in2,size);

     SCL_DisplayFrame();    

	for(i=0;i<2000;i+=1) 
	{
		in[3+(i*4)]=(in2[i])          & 0xff;
		in[2+(i*4)]=(in2[i]>>8)   & 0xff;
		in[1+(i*4)]=(in2[i]>>16) & 0xff;
		in[0+(i*4)]=(in2[i]>>24) & 0xff;
	}

  data.maxlength=(int)in[0];
  yinit=(int)in[1];
  data.startpos[0]=(int)in[2];
  data.startpos[1]=(int)in[3];
  blocknum=(int)in[4];
  backnum=(int)in[5];

		ch=in[0];

  for (loop1=0;loop1<14;loop1++)
    for (loop2=0;loop2<=data.maxlength;loop2++)
    {
//      ch=getc(in);
		ch=in[(loop1*(data.maxlength+2))+loop2];   // mettre 218 en dur ?
//		ch=in[(loop1*218)+loop2];   // mettre 218 en dur ?
/*
		if (titi>DELTA &&  titi <= (DELTA +14))
		{

			sprintf(toto,"%d %02x",titi, ch);
			graphstring(0,vbt+16,toto,TEXTCOLOR,HiddenPageOffs);
			vbt+=16;
		}
		titi++;
*/

		if(ch<='0')
		{
			data.world[loop1][loop2]=0;
//			sprintf(toto,"%02d",data.world[loop1][loop2]);
//			graphstring(0+loop1*16,20+loop2*16,toto,TEXTCOLOR,HiddenPageOffs);
		}

		if (ch>='a' && ch<='z')
		{
			data.world[loop1][loop2]=ch-70;
//				sprintf(toto,"%02d",data.world[loop1][loop2]);
//				graphstring(0+loop1*16,20+loop2*16,toto,TEXTCOLOR,HiddenPageOffs);
		}
		if (ch>='A' && ch<='Z')
//		if (ch>=0x40 && ch<=0x5A)
		{
			data.world[loop1][loop2]=ch-64;

//				sprintf(toto,"ch %02d %02d %02d",ch,data.world[loop1][loop2],loop1,loop2);
//				graphstring(0+loop1*16,20+loop2*16,toto,TEXTCOLOR,HiddenPageOffs);
			
//			sprintf(toto,"%02d",data.world[loop1][loop2]);
//			graphstring(0+loop1*16,20+loop2*16,toto,TEXTCOLOR,HiddenPageOffs);
		}
		if (loop1==0)
		{
			data.world[loop1][loop2]=0;
		}
//test vbt
//	data.world[loop1][loop2]=1;
    }

colBgAddr = (Uint16*)SCL_AllocColRam(SCL_NBG2,256,OFF); 

//if (backnum==49)
if(player[curplay].level%10==1)
{
	 SCL_SetColRam(SCL_NBG2,0,256,pal_bgrnd001); 
	 Cel2VRAM	(cel_bgrnd001 , (void *)NBG2_CEL_ADR , sizeof(cel_bgrnd001)) ; 
//	 Cel2VRAM	(cel_block001 , (void *)(NBG2_CEL_ADR+sizeof(cel_bgrnd001)) , sizeof(cel_block001)) ;
	 Cel2VRAM	(cel_block001 , (void *)(NBG2_CEL_ADR+sizeof(cel_bgrnd001)+2304) , sizeof(cel_block001)) ;
//	 Map2VRAM	(map_bgrnd001  , (void *)NBG2_MAP_ADR , 64 , 8, 0 , 0) ;
}
//else if (backnum==51)
else if(player[curplay].level%10==2)
{
	 SCL_SetColRam(SCL_NBG2,0,256,pal_bgrnd002); 
	 Cel2VRAM	(cel_bgrnd002 , (void *)NBG2_CEL_ADR , sizeof(cel_bgrnd002)) ; 
	 Cel2VRAM	(cel_block002 , (void *)(NBG2_CEL_ADR+sizeof(cel_bgrnd002)+2304) , sizeof(cel_block002)) ;
//	 Map2VRAM	(map_bgrnd002  , (void *)NBG2_MAP_ADR , 64 , 8, 0 , 0) ;
}
//else if (backnum==50)
else if(player[curplay].level%10==3)
{
	 SCL_SetColRam(SCL_NBG2,0,256,pal_bgrnd003); 
	 Cel2VRAM	(cel_bgrnd003 , (void *)NBG2_CEL_ADR , sizeof(cel_bgrnd003)) ; 
	 Cel2VRAM	(cel_block003 , (void *)(NBG2_CEL_ADR+sizeof(cel_bgrnd003)+2304) , sizeof(cel_block003)) ;
//	 Map2VRAM	(map_bgrnd003  , (void *)NBG2_MAP_ADR , 64 , 8, 0 , 0) ;
}
//else
else if(player[curplay].level%10==4)
{
	 SCL_SetColRam(SCL_NBG2,0,256,pal_bgrnd004); 
	 Cel2VRAM	(cel_bgrnd004 , (void *)NBG2_CEL_ADR , sizeof(cel_bgrnd004)) ; 
	 Cel2VRAM	(cel_block004 , (void *)(NBG2_CEL_ADR+sizeof(cel_bgrnd004)+2304) , sizeof(cel_block004)) ;
//	 Map2VRAM	(map_bgrnd004  , (void *)NBG2_MAP_ADR , 64 , 8, 0 , 0) ;
}
else
{
	StopMusic();
	player[0].lives=0;
	player[0].coins[0]=0;
	times[0]="   ";
	ending_screen();
//    graphstring(88,24,"IT is THE END :",0,NULL);
//	loadBackground(pal_mariomap,cel_mariomap,map_mariomap,64,4,61184);   
//SetAutoLinePara(SCL_NBG0);

//	while(1);
}
  return(yinit);
}

//CALCULATE CURRENT SCREEN///////////////////////////////////////////////////
void drawscreen(int x)
{
  int loop1,loop2,back,x2;
  static int dy;
 // VBT à remettre

	if(x==-1)
	{
		graphstring(0,1,"                                          ",TEXTCOLOR,HiddenPageOffs);
		graphstring(0,9,"       C4 - 2006   www.rockin-b.de       ",TEXTCOLOR,HiddenPageOffs);
		x=0;
	}
	else
	status();

  x2=x;
  back=0;
  while(x2>=16)
  {
    x2-=16;
    back++;
  }

//				graphstring(16,100,"HERE HERE HERE",TEXTCOLOR,HiddenPageOffs);

loop1=1;

//NBG2_MAP_ADR

	Uint16 *ss_map;
	int vbt=1;

	ss_map = (Uint16 *)NBG2_MAP_ADR;
//	ss_map = (Uint16 *)NBG0_MAP_ADR;

/*
	(*(Uint16 *)0x25F8009A) = 0x0003; 
	(*(Uint16 *)0x25F80020) = 0x0303;

	SCL_Open(SCL_NBG2);
	Scl_n_reg.n2_move_x =  50<<16 ;
	Scl_n_reg.n2_move_y =  50<<16 ;
	SCL_Close();
*/

	SCL_Open(SCL_NBG2);
//	Scl_n_reg.n0_move_y =  y-(16<<16) ;
	SCL_MoveTo(FIXED(x), FIXED(0),0);/* Home Position */
	SCL_Close();

//				char toto[20];
//				sprintf(toto,"x2 %02d x %02d mod%2d",x2,x,x&0x0f);
//				graphstring(0,150,toto,TEXTCOLOR,HiddenPageOffs);


//				sprintf(toto,"back %02d",back);
//				graphstring(0,170,toto,TEXTCOLOR,HiddenPageOffs);

		//	if(back>=14)
				vbt=0;//*=2;


//	for (loop1=1;loop1<=13;loop1++) //yy
	for (loop1=0;loop1<=13;loop1++) //yy
	{

				char toto[20];
//				sprintf(toto,"delta %02d %02d",delta,back);
//				graphstring(0,150,toto,TEXTCOLOR,HiddenPageOffs);

//		for (loop2=back;loop2<=back+16;loop2++) //x
		for (loop2=back;loop2<=back+32;loop2++) //x
//		for (loop2=0;loop2<16;loop2++) //x
		{	
//				sprintf(toto,"%02d",data.world[loop1][loop2]);
//				graphstring(0+(loop2-back)*16,loop1*16,toto,TEXTCOLOR,HiddenPageOffs);

			if (data.world[loop1+1][loop2]>0)
			{
//				ss_map[(loop2+(loop1)*32)+1+32-( (loop2+1)/32       )*32]= 0x08;//(data.world[loop1+1][loop2])*2;
				ss_map[(loop2+(loop1)*32)+1+32-( (loop2+1)/32       )*32]= (data.world[loop1+1][loop2])<<1;
//				ss_map[(loop2+(loop1)*32)+1+30-( (loop2+3)/32       )*32 ]=(data.world[loop1+1][loop2])<<1;

				if (data.bumped[0]==loop2 && data.bumped[1]==(loop1+1))
				{
					dy+=data.bumploop;
					//	  x_put_masked_pbm((loop2<<4)-x+32,(loop1<<4)+dy,HiddenPageOffs,data.block[data.world[loop1][loop2]-1]);
					data.bumploop++;
					if(data.bumploop==3)
					{
						data.bumploop=0;
						data.bumped[0]=0;
						data.bumped[1]=0;
						dy=0;
					}
				}
//				x_put_masked_pbm((loop2<<4)-x+32,(loop1<<4),HiddenPageOffs,data.block[data.world[loop1][loop2]-1]);
			}
			else
			{
//				ss_map[(loop2+(loop1)*32)+1+32-( (loop2+1)/32       )*32]=0x02;
				ss_map[(loop2+(loop1)*32)+1+32-( (loop2+1)/32       )*32]=0x00;
//				ss_map[(loop2+(loop1)*32)+1+30-( (loop2+3)/32       )*32 ]=0;
			}
		}
	}

  drawcoin(x);
  drawscore(x);
//  x_rect_fill(15,0,32,224,HiddenPageOffs,0);
//  x_rect_fill(288,0,306,224,HiddenPageOffs,0);
}

//DRAW INFO ON TOP OF SCREEN/////////////////////////////////////////////////
void status()
{
  char pscore2[7];
  char slevel[4]="1-1";
  char scoins[3]="00";
  static char stime[4]="   ";
  pscore[7]="000000";
  int loop1,loop2;
  if (curplay==0)
    graphstring(34,1,"MARIO",TEXTCOLOR,HiddenPageOffs);
  else
    graphstring(34,1,"LUIGI",TEXTCOLOR,HiddenPageOffs);
  graphstring(108,1,"COINS",TEXTCOLOR,HiddenPageOffs);
  graphstring(180,1,"WORLD",TEXTCOLOR,HiddenPageOffs);
  graphstring(254,1,"TIME",TEXTCOLOR,HiddenPageOffs);
  if(player[curplay].score[1]!=player[curplay].score[0])
  {
//    itoa(player[curplay].score[1],pscore2,10);
	sprintf(pscore2,"%d",player[curplay].score[1]);
    loop2=5;
    for(loop1=strlen(pscore2)-1;loop1>=0;loop1--)
	pscore[loop2--]=pscore2[loop1];
    graphstring(34,9,pscore,BACKGROUND,HiddenPageOffs);
  }
  strcpy(pscore,"000000");
//  itoa(player[curplay].score[0],pscore2,10);
	sprintf(pscore2,"%d",player[curplay].score[1]);
  loop2=5;
  for(loop1=strlen(pscore2)-1;loop1>=0;loop1--)
    pscore[loop2--]=pscore2[loop1];
  graphstring(34,9,pscore,TEXTCOLOR,HiddenPageOffs);
  player[curplay].score[1]=player[curplay].score[0];
  if (times[1]!=times[2])
  {
//    itoa(times[0],stime,10);
	sprintf(stime,"%03d",times[0]);
    graphstring(260,9,stime,BACKGROUND,HiddenPageOffs);
    times[2]=times[1];
    times[0]--;
//    itoa(times[0],stime,10);
	sprintf(stime,"%03d",times[0]);
  }
  graphstring(260,9,stime,TEXTCOLOR,HiddenPageOffs);
  slevel[0]=(char)(player[curplay].level/5+1-208);
  slevel[2]=(char)(player[curplay].level%5-208);
  graphstring(188,9,slevel,TEXTCOLOR,HiddenPageOffs);
  if (player[curplay].coins[0]!=player[curplay].coins[1])
  {
//    itoa(player[curplay].coins[1],scoins,10);
	sprintf(scoins,"%d",player[curplay].coins[1]);
    if (player[curplay].coins[1]<10)
    {
      scoins[1]=scoins[0];
      scoins[0]='0';
    }
    graphstring(116,9,scoins,BACKGROUND,HiddenPageOffs);
    player[curplay].coins[1]=player[curplay].coins[0];
  }
//  itoa(player[curplay].coins[0],scoins,10);
	sprintf(scoins,"%d",player[curplay].coins[0]);

  if (player[curplay].coins[0]<10)
  {
    scoins[1]=scoins[0];
    scoins[0]='0';
  }
  graphchar(108,9,'x',TEXTCOLOR,HiddenPageOffs);
  graphstring(116,9,scoins,TEXTCOLOR,HiddenPageOffs);
//  x_line(100,8,101,8,20,HiddenPageOffs);
//  x_put_pix(102,8,HiddenPageOffs,0);
//  x_line(100,15,101,15,20,HiddenPageOffs);
//  x_put_pix(102,15,HiddenPageOffs,0);
  for(loop1=0;loop1<6;loop1++)
  {
//    x_line(99,9+loop1,102,9+loop1,20,HiddenPageOffs);
//    x_put_pix(103,9+loop1,HiddenPageOffs,0);
  }
}

//CALCULATE AND DRAW MARIO///////////////////////////////////////////////////
void drawmario(int x, int y)
{
/*
    sprites[0].ax = x-58;
    sprites[0].ay = y+34;
*/
//	char toto[50];
//	sprintf(toto,"x:%d y:%d sprite %d",x,y,data.sprite/2);

//  graphstring(100,82,toto,TEXTCOLOR,HiddenPageOffs);


  int loop1,loop2;
  for (loop1=0;loop1<=15;loop1++)
    for (loop2=0;loop2<=15;loop2++)
      if (data.mario[abs(data.sprite/2)][loop1][loop2]>=0)
	if (y-15+loop1>=0 && y-15+loop1<224)
	{
	  if (data.direction==0)
	  {
		sprites[0].charAddr   =  512+(data.sprite/2)*32;
		sprites[0].control    = ( JUMP_NEXT | FUNC_NORMALSP | DIR_NOREV); 
//	    x_put_pix(x+loop2+32,y-15+loop1,HiddenPageOffs,data.mario[data.sprite/2][loop1][loop2]);
	  }
	  else
	  {
		sprites[0].charAddr   =  512+(data.sprite/2)*32;
		sprites[0].control    = ( JUMP_NEXT | FUNC_NORMALSP | DIR_LRREV);
//	  else x_put_pix(x+15-loop2+32,y-15+loop1,HiddenPageOffs,data.mario[data.sprite/2][loop1][loop2]);
	  }
	}

/*
  for (loop1=0;loop1<=7;loop1++)
	{
	sprites[loop1].control    = ( JUMP_NEXT | FUNC_NORMALSP);
    sprites[loop1].drawMode   = ( ECD_DISABLE | COLOR_4 | COMPO_REP);
    sprites[loop1].charSize   = 0x0210;   
	sprites[loop1].charAddr   =  512+32*loop1;
    sprites[loop1].ax = x+16*loop1;
    sprites[loop1].ay = y;
	}
*/

//	sprites[0].control    = ( JUMP_NEXT | FUNC_NORMALSP);
    sprites[0].drawMode   = ( ECD_DISABLE | COLOR_4 | COMPO_REP);
    sprites[0].charSize   = 0x0210;   
    sprites[0].ax = x-20;
    sprites[0].ay = y-47;


}

//DRAW CHARACTERS////////////////////////////////////////////////////////////
void graphchar(int xc, int yc, char c,int color, unsigned offset)
{
/*
  int x,y;
  unsigned char data;
  unsigned char *work;
  unsigned char bitmask=0x80;
  work=charset+(c<<3);
  for(y=0;y<8;y++)
  {
    bitmask=0x80;
    for(x=0;x<8;x++)
    {
      if((*work & bitmask))
//	x_put_pix(x+xc,y+yc,offset,color);
      bitmask=(bitmask>>1);
    }
  work++;
  }
*/
       FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)c,xc,yc-1,1,8,9,0);
}

//DRAW A STRING//////////////////////////////////////////////////////////////
void graphstring(int x,int y,char *string,int color, unsigned offset)
{
//  int loop;
//  for(loop=0;loop<strlen(string);loop++)
//    graphchar(x+loop*8,y,string[loop],color,offset);
       FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
				(Uint8 *)string,x,y-1,1,8,9,0);
}

//DRAW SCREEN SHOWING LEVEL AND NUMBER OF LIVES//////////////////////////////
void levelscreen()
{
  int x=75;
  int y=110;
  int wait[3];
  char print[3];
  char level_str[50];
  data.sprite=0;
  data.direction=0;
  fillscreen(0); //remplit l'ecran d'une couleur
		graphstring(0,1,"                                          ",TEXTCOLOR,HiddenPageOffs);
		graphstring(0,9,"                                          ",TEXTCOLOR,HiddenPageOffs);
  status();
  drawmario(x,y);
//  PlayMusic(tno[0]);
	StopMusic();

sprintf(level_str,"WORLD %c-%c",(char)(player[curplay].level/5+1-208),(char)(player[curplay].level%5-208));

  graphstring(100,82,level_str,TEXTCOLOR,HiddenPageOffs);

//  itoa(player[curplay].lives,print,10);
sprintf(print,"x %d",player[curplay].lives);
  graphstring(132,100,print,TEXTCOLOR,HiddenPageOffs);

//  x_page_flip(0,0);
//  mktime(&t);
	SCL_DisplayFrame();
	wait_seconds(3);

//  wait(1000000);     
  graphstring(100,82,"                 ",TEXTCOLOR,HiddenPageOffs);
  graphstring(132,100,"                 ",TEXTCOLOR,HiddenPageOffs);
  graphstring(164,82,"                 ",TEXTCOLOR,HiddenPageOffs);
}

//TITLE SCREEN AND CHOOSING NUMBER OF PLAYERS////////////////////////////////
int startscreen()
{
	char top_score[50];
  int x;
//  int x=10;
  int y=191;
  int choice,screenx,offset,numplayers;
//  FILE *logoin;
//  int count,loop1,loop2;
//  char *temp;


start_menu:
numplayers=1;
x=40;
y=191;
  data.sprite=0;
  screenx=-1;//modif vbt

  fillscreen(BACKGROUND); //remplit l'écran d'une couleur

  drawscreen(screenx); //vbt à remettre

//  drawmario(x,y);

//	loadBackground(pal_title2,cel_title2,map_title2,64,4,61184);   
	loadBackground(pal_title2,cel_title2,map_title2,64,4,61184);   

//  free(temp);
//  fclose(logoin);

sprintf(top_score,"TOP - %06d",high_score);

 //VBT à remettre
  graphstring(160,118,"1985 NINTENDO",TEXTCOLOR,HiddenPageOffs);
//  graphstring(120,130,"PRESS START",TEXTCOLOR,HiddenPageOffs);
//  graphstring(120,146,"PRESS START",TEXTCOLOR,HiddenPageOffs);

  graphstring(80,131,"PRESS X for help",TEXTCOLOR,HiddenPageOffs);
  graphstring(80,141,"PRESS Y for credits",TEXTCOLOR,HiddenPageOffs);
  graphstring(80,151,"PRESS START to start",TEXTCOLOR,HiddenPageOffs);

//  graphstring(120,162,"TOP - 000000",TEXTCOLOR,HiddenPageOffs);
  graphstring(120,162,top_score,TEXTCOLOR,HiddenPageOffs);

	int mosaic_effect=0;

	if (first_display==0)
	{
		for (mosaic_effect=0;mosaic_effect<=15 ;mosaic_effect++)
		{
			SCL_SetMosaic(SCL_NBG2|SCL_NBG1|SCL_NBG0,15-mosaic_effect,15-mosaic_effect);
			SCL_DisplayFrame();
			wait_seconds(1);
		}
	}

	first_display =1;
	// VBT 31/12/2006 : déplacement du mario
  drawmario(x,y);

		device = PER_GetDeviceR( &__port[0], 0 );
        
    	while((pltrigger[0] & PER_DGT_S)==0)
    	{
			pltrigger[0]  = PER_GetTrigger( device );
			checkExitHere(pltrigger[0]);

			
			if ((pltrigger[0] & PER_DGT_X)!=0)
			{
				displayConfiguration(0);
				goto start_menu;
			}

			if ((pltrigger[0] & PER_DGT_Y)!=0)
			{
				displayTextCredits(0);
				goto start_menu;
			}


			SCL_DisplayFrame();    
        }

		memset(NBG0_MAP_ADR,0x00,512);
		  graphstring(160,118,"                                      ",TEXTCOLOR,HiddenPageOffs);
		  graphstring(80,131,"                                      ",TEXTCOLOR,HiddenPageOffs);
		  graphstring(80,141,"                                      ",TEXTCOLOR,HiddenPageOffs);
		  graphstring(80,151,"                                      ",TEXTCOLOR,HiddenPageOffs);
		  graphstring(80,162,"                                      ",TEXTCOLOR,HiddenPageOffs);

		numplayers=1;

  if (numplayers==1)
      offset=129;

  return(numplayers);
}
/*
//CHANGE COLORS FOR MARIO OR LUIGI///////////////////////////////////////////
void setcolors()
{
  if (curplay==0)
  {
    setpalette(1,data.marioc[0]);
    setpalette(2,data.marioc[1]);
  }
  else
  {
    setpalette(1,data.luigic[0]);
    setpalette(2,data.luigic[1]);
  }
}
*/
// VBT à activer pls tard
void rotatepal(int *palloopp, colorpal *tempcp)
{
  int palloop=*palloopp;
  colorpal tempc=*tempcp;
	Uint16 backup;
int DELTACOL= 15;

  int loop;
  if (palloop>=16 && palloop%4==0)
  {
    if (palloop<=24)
    {
//colBgAddr
		backup = colBgAddr[1+DELTACOL];
//      tempc=data.palette[20];
//      data.palette[20]=data.palette[21];
		colBgAddr[1+DELTACOL]= colBgAddr[2+DELTACOL];
//      data.palette[21]=data.palette[22];
		colBgAddr[2+DELTACOL]= colBgAddr[3+DELTACOL];
//      data.palette[22]=data.palette[23];
		colBgAddr[3+DELTACOL]= colBgAddr[4+DELTACOL];
//      data.palette[23]=tempc;
		colBgAddr[4+DELTACOL]= backup;
    }
    else
    {
//      tempc=data.palette[23];
		backup = colBgAddr[4+DELTACOL];
//      data.palette[23]=data.palette[22];
		colBgAddr[4+DELTACOL]= colBgAddr[3+DELTACOL];
//      data.palette[22]=data.palette[21];
		colBgAddr[3+DELTACOL]= colBgAddr[2+DELTACOL];
//      data.palette[21]=data.palette[20];
		colBgAddr[2+DELTACOL]= colBgAddr[1+DELTACOL];
//      data.palette[20]=tempc;
		colBgAddr[1+DELTACOL]= backup;
    }
/*
    for(loop=20;loop<=23;loop++)
      setpalette(loop,data.palette[loop]);
*/  if (palloop==36)
      palloop=0;
  }
  palloop++;
  *tempcp=tempc;
  *palloopp=palloop;
}

void check_keybuf(int *movep, int *finishp, int *upp, int *downp, int *jumpp)
{
  int move=*movep;
  int finish=*finishp;
  int up=*upp;
  int down=*downp;
  int jumploop=*jumpp;

	device = PER_GetDeviceR( &__port[0], 0 );

			pltrigger[0]  = PER_GetTrigger( device );
			checkExitHere(pltrigger[0]);
			SCL_DisplayFrame();    

	if((pltrigger[0] & PER_DGT_R)!=0)
	{
//		graphstring(130,100,"DIR R",TEXTCOLOR,VisiblePageOffs);

		if((pltrigger[0] & PER_DGT_A)!=0)
		{
//		graphstring(130,100,"PAD A",TEXTCOLOR,VisiblePageOffs);
			if (move<16)
				move++;
		}
		else
		{
			if (move>8)
				move--;
			if (move<8)
				move++;
		}
		if (landed) //(data.world[(marioy+1)/16][(mariox+player[curplay].screenx+8)/16]>26)
			data.direction=0;
	}
	else
	{
		if(move>0)
		move--;
	}

	if((pltrigger[0] & PER_DGT_L)!=0)
	{
//		graphstring(130,100,"DIR L",TEXTCOLOR,VisiblePageOffs);

		if((pltrigger[0] & PER_DGT_A)!=0)
		{
//			graphstring(130,100,"PAD A",TEXTCOLOR,VisiblePageOffs);
			if (move>-16)
			move--;
		}
		else
		{
			if (move<-8)
				move++;
			if (move>-8)
				move--;
		}
		if (landed) //(data.world[(marioy+1)/16][(mariox+player[curplay].screenx+8)/16]>26)
			data.direction=1;
	}
	else
	{
		if(move<0 && (pltrigger[0] & PER_DGT_R)==0)
		move++;
	}


   if ((pltrigger[0] & PER_DGT_B)!=0 && !down)
//   if ((pltrigger[0] & PER_DGT_B)!=0)
   {
		if (jumploop==0)
		{
//			PcmLoad(0);
			PcmStart(0);
		}

		up=-17;
		data.sprite=12;
		jumploop++;

		if (jumploop>10)
		{
			down=1;
			jumploop=0;
		}
   }



	if((pltrigger[0] & PER_DGT_S)!=0)
	{
		int pause = 1;
		PcmStop(0);
		PcmStop(1);

		graphstring(140,100,"Pause",TEXTCOLOR,VisiblePageOffs);
//     clear_key_buffer();
		wait_seconds(1);
		
		pltrigger[0] =0;

		while(pause==1)
	   {
			if ((pltrigger[0] & PER_DGT_S)!=0)
			{ 
				SCL_DisplayFrame();   
				pause=0;
			}
			device = PER_GetDeviceR( &__port[0], 0 );

			pltrigger[0]  = PER_GetTrigger( device );
			checkExitHere(pltrigger[0]);
//			SCL_DisplayFrame();   
		}
		wait_seconds(1);
		graphstring(140,100,"      ",BACKGROUND,VisiblePageOffs);
   }
   pltrigger[0]=0;

  *movep=move;
  *finishp=finish;
  *upp=up;
  *downp=down;
  *jumpp=jumploop;
}

void animate_mario(int move)
{
  if (landed)
  {
    if (data.sprite==10 && ((move>0 && data.direction==0) || (move<0 && data.direction==1)))
      data.sprite=1;
    if (move==0)
      data.sprite=0;
    if ((move>0 && data.direction==0) || (move<0 && data.direction==1))
    {
      if(abs(move)<16)
	data.sprite++;
      else
	data.sprite+=2;
      if (data.sprite>=10)
	data.sprite=2;
    }
    if ((move>0 && data.direction==1) || (move<0 && data.direction==0))
      data.sprite=10;
  }

//	char toto[50];

//	sprintf(toto,"sprite %d mode %d",data.sprite,move);

//  graphstring(100,114,toto,TEXTCOLOR,HiddenPageOffs);

}

void move_mario(int *movep)
{
  int move=*movep;
  int loop1,loop2;
  if (marioy>16)
  {
    if (move>0)
      for (loop1=0;loop1<16;loop1++)
	for (loop2=0;loop2<=move;loop2++)
	  if (data.world[(marioy-loop1)/16][(mariox+player[curplay].screenx+13+loop2/4)/16]>26)
	    move=loop2;
    if (move<0)
      for (loop1=0;loop1<16;loop1++)
	for (loop2=0;loop2>=move;loop2--)
	  if (data.world[(marioy-loop1)/16][(mariox+player[curplay].screenx+2+loop2/4)/16]>26 || (mariox+loop1/2)<=0)
	    move=loop2;
  }
  if(mariox>100 && move>0)
    player[curplay].screenx+=move/4;
  else
    if (mariox+move/4>16)
      mariox+=move/4;
  *movep=move;

/*
	char toto[50];

	sprintf(toto,"move %d mariox %d",move,mariox);

  graphstring(100,114,toto,TEXTCOLOR,HiddenPageOffs);
*/

}

void addcoin(int x, int y)
{
  cointype *temp,*c;
  c=bcoin;
  while ((c->next)!=NULL)
    c=c->next;
  temp=(cointype *)malloc(sizeof(cointype));
  temp->next=NULL;
  temp->coinx=x;
  temp->coiny=y;
  temp->coinloop=-10;
  temp->dy=0;
  c->next=temp;
}

void removecoin()
{
  cointype *temp;
  cointype *c=bcoin;
  temp=c->next;
  c->next=c->next->next;
  addscore(temp->coinx,temp->coiny,"200");
  	  PcmLoad(1);
	  PcmStart(1);
//  free(temp);
}

void drawcoin(int x)
{
  cointype *c=bcoin;
  int loop,num=0;
  while ((c->next)!=NULL)
  {
    num++;
    c=c->next;
  }
  c=bcoin;
  for (loop=0;loop<num;loop++)
  {
    c=c->next;
//    if (((c->coinx)*16+32-x)>16)
//      x_put_masked_pbm((c->coinx)*16+32-x,(c->coiny)*16+c->dy,HiddenPageOffs,data.coin[abs((c->coinloop)%3)]);
    c->coinloop++;
    c->dy+=c->coinloop;
    if (c->coinloop>=10)
       removecoin();
  }
}

void addscore(int x, int y, char *pscore)
{
  scoretype *temp,*s;
  s=bscore;
  while ((s->next)!=NULL)
    s=s->next;
  temp=(scoretype *)malloc(sizeof(scoretype));
  temp->next=NULL;
  temp->scorex=x;
  temp->scorey=y;
  temp->scoreloop=0;
  strcpy(temp->num,pscore);
  s->next=temp;
}

void removescore()
{
  scoretype *temp;
  scoretype *s=bscore;
  temp=s->next;
  s->next=s->next->next;
//  free(temp);
}

void drawscore(int x)
{
  scoretype *s=bscore;
  while ((s->next)!=NULL)
  {
    s=s->next;
    if (((s->scorex)*16+32-x)>16)
	  {
      graphstring(0,(s->scorey)*16+(s->scoreloop+1),"                ",TEXTCOLOR,HiddenPageOffs);
//	  graphstring((s->scorex)*16+32-x-32,(s->scorey)*16+(s->scoreloop+1),"         ",TEXTCOLOR,HiddenPageOffs);
if((s->scorex)*16-x-64 >0)
	  graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop+2),"                ",TEXTCOLOR,HiddenPageOffs);
else
	  graphstring(0,(s->scorey)*16+(s->scoreloop+2),"                ",TEXTCOLOR,HiddenPageOffs);

	  graphstring((s->scorex)*16+32-x,(s->scorey)*16+(s->scoreloop),s->num,TEXTCOLOR,HiddenPageOffs);
	  }
	  else
//	  graphstring(0,(s->scorey)*16+(s->scoreloop+2),"                                                        ",TEXTCOLOR,HiddenPageOffs);
	  graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop+2),"                       ",TEXTCOLOR,HiddenPageOffs);
    s->scoreloop--;
    if (s->scoreloop<=-20)
	 {
/*
	   graphstring((s->scorex)*16-x-32,(s->scorey)*16+(s->scoreloop),"                                                        ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-32,(s->scorey)*16+(s->scoreloop-8),"                                                        ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-32,(s->scorey)*16+(s->scoreloop+8),"                                                        ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-32,(s->scorey)*16+(s->scoreloop+16),"                                                        ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-32,(s->scorey)*16+(s->scoreloop+24),"                                                        ",TEXTCOLOR,HiddenPageOffs);
*/
if((s->scorex)*16-x-64 >0)
{
	   graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop-8),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop+8),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop+16),"                       ",TEXTCOLOR,HiddenPageOffs);
//       graphstring((s->scorex)*16-x-64,(s->scorey)*16+(s->scoreloop+24),"                       ",TEXTCOLOR,HiddenPageOffs);
}
else
 {
	   graphstring(0,(s->scorey)*16+(s->scoreloop),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring(0,(s->scorey)*16+(s->scoreloop-8),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring(0,(s->scorey)*16+(s->scoreloop+8),"                       ",TEXTCOLOR,HiddenPageOffs);
       graphstring(0,(s->scorey)*16+(s->scoreloop+16),"                       ",TEXTCOLOR,HiddenPageOffs);
//       graphstring(0,(s->scorey)*16+(s->scoreloop+24),"                               ",TEXTCOLOR,HiddenPageOffs);

 }



	   removescore();
	 }
  }

}

void exitgame()
{
  int loop;
  for (loop=0;loop<52;loop++)
    free(data.block[loop]);
  for (loop=0;loop<3;loop++)
    free(data.coin[loop]);
//  free(bcoin);
//  free(bscore);
//  uninstall_new_key_handler();
//  x_remove_vsync_handler();
//  x_text_mode();
}

void check_jump(int *upp, int *downp, int *jumploopp)
{
  int loop1,loop2;
  int up=*upp;
  int down=*downp;
  int jumploop=*jumploopp;
  loop1=3;
  landed=0;
  while (loop1<13 && landed==0)
  {
    if (data.world[(marioy+1)/16][(mariox+player[curplay].screenx+loop1)/16]>26)
      landed=1;
    else
      landed=0;
    loop1++;
  }
  if (!landed || marioy<16)
    if (up<17)
      up+=1;
  if (up>0)	//CHECK IF MARIO LANDED//
  {
    down=1;
    loop1=marioy;
    if (marioy<207)
    {
      while(loop1++<marioy+up/4)
      {
	for (loop2=3;loop2<14;loop2+=9)
	  if (data.world[loop1/16][(mariox+player[curplay].screenx+loop2)/16]>26)
	  {
	    marioy=loop1-1;
	    loop1=marioy+up/4;
	    loop2=13;
	    up=0;
	    down=0;
	    data.sprite=0;
	  }
      }
    }
    marioy+=up/4;
  }

  if (up<0)	//CHECK IF MARIO HIT A BLOCK/
  {

//    if (!keybuf[KEY_ALT])
//    {

   	device = PER_GetDeviceR( &__port[0], 0 );

	pltrigger[0]  = PER_GetTrigger( device );
   
   if ((pltrigger[0] & PER_DGT_B)==0)
   {
      down=1;
      jumploop=0;
    }
    loop1=marioy;
    marioy+=up/4;
    if (marioy>24)
    {
      while(loop1-->=marioy+up/4)
      {
	if(data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]>26 ||data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]==18)
//	if(data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]>39 ||data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]==36)
	{
	  marioy=loop1;
	  loop1=marioy+up/4-1;
	  up=-up;
	  down=1;
	  jumploop=0;
	  if (data.bumped[0]==0 && data.bumped[1]==0)
	  {
	    data.bumped[0]=(mariox+player[curplay].screenx+8)/16;
	    data.bumped[1]=marioy/16-1;
	    data.bumploop=-3;
	  }
	}


	if (data.world[loop1/16-1][(mariox+player[curplay].screenx+12)/16]>26 && data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]<26)
//	if (data.world[loop1/16-1][(mariox+player[curplay].screenx+12)/16]>39 && data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]<39)
	if(mariox>=32)
	  mariox-=1;
	if (data.world[loop1/16-1][(mariox+player[curplay].screenx+3)/16]>26 && data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]<26)
//	if (data.world[loop1/16-1][(mariox+player[curplay].screenx+3)/16]>39 && data.world[loop1/16-1][(mariox+player[curplay].screenx+8)/16]<39)
	  mariox+=1;
      }
    }
  }
  *upp=up;
  *downp=down;
  *jumploopp=jumploop;
}

void check_blocks()
{
  int bumpedblock=0;
  if (data.world[(marioy-8)/16][(mariox+player[curplay].screenx+8)/16]==10)
  {
    data.world[(marioy-8)/16][(mariox+player[curplay].screenx+8)/16]=0;
    player[curplay].score[0]+=200;
    player[curplay].coins[0]++;
//	PcmLoad(1);
	PcmStart(1);
  }
  if (data.bumploop==-3)
  {
    bumpedblock=data.world[marioy/16-1][(mariox+player[curplay].screenx+8)/16];
    switch (bumpedblock)
    {
      case 18:
      case 28:
	data.world[marioy/16-1][(mariox+player[curplay].screenx+8)/16]=27;
	player[curplay].score[0]+=200;
	player[curplay].coins[0]++;
	addcoin(data.bumped[0],data.bumped[1]-1);
      case 29:
	if (data.world[data.bumped[1]-1][data.bumped[0]]==10)
	{
	  data.world[data.bumped[1]-1][data.bumped[0]]=0;
	  player[curplay].score[0]+=200;
	  player[curplay].coins[0]++;
	  addcoin(data.bumped[0],data.bumped[1]-1);
	}
	break;
      default:
	data.bumped[0]=data.bumped[1]=0;
	data.bumploop=0;
	break;
    }
  }
  if (player[curplay].coins[0]==100)
  {
    player[curplay].lives++;
    player[curplay].coins[0]=0;
  }
}

void check_finish(int *finishp)
//CHECK FOR END OF CURRENT PLAYER LOOP///////////////////////////////////////
{
  int finish=*finishp;
  if (marioy>=250)
    finish=1;
  if ((mariox+player[curplay].screenx+16)/16==data.maxlength-13)
    finish=2;
  if (times[0]==0)
    finish=1;
  *finishp=finish;
}
//END////////////////////////////////////////////////////////////////////////
