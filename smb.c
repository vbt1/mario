/****************************************************************************
*Super Mario Bros.							    *
*Copyright 1985 Nintendo						    *
*Coded by:								    *
*  William Merrill Buerger						    *
*  Buergerw@warp.msoe.edu						    *
*  http://www.msoe.edu/~buergerw					    *
*With help from:							    *
*  John Ratke		-Keyboard Handler				    *
*  Themie Gouthas	-XLIB graphics stuff				    *
****************************************************************************/

#include "smb.h"			//Main Header file (f:\smb\ = path of smb.h)//
#include "smbfunc.c"		//Function file//

char pscore[7]="000000";
long high_score=0;
int first_display=0;

//MAIN///////////////////////////////////////////////////////////////////////
void main2()
{
  int move;			//DEFINE & INITIALIZE LOCAL VARIABLES//
  int up;
  int down=0;
  int finish=0;
  int jumploop=0;
  int numplayers;
  int palloop;
//  colorpal tempc;
unsigned char *tno;

start_menu:

  init();
  curplay=0;
//	PlayMusic(1);
//  getmario(); // definit les couleurs de mario et luigi
  getinputs(); //recup des fichiiers images // A NE PAS REMETTRE !!!

	if(first_display==0)
		SCL_SetMosaic(SCL_NBG2|SCL_NBG1,15,15);
  numplayers=startscreen(); //affichage du titre

//SetAutoLinePara(SCL_NBG2);

  if (numplayers==1)
    player[1].lives=0;


//MAIN GAME LOOP/////////////////////////////////////////////////////////////
  while(finish!=3)
  {
//    setcolors();
    times[0]=201;
 // VBT à remettre
	levelscreen();

	if(player[curplay].level%10<=4)
	{
		marioy=getinputs();
	}
	else
	{
		StopMusic();
/*		player[1].lives=0;
		player[0].lives=0;
*/
		player[0].coins[0]=0;
		times[0]="   ";
		ending_screen();
//		finish=3;
//		curplay=0;
//		player[curplay].screenx=data.startpos[0]*16-2;
		goto the_end;
	}
	
    if (player[curplay].screenx>=data.startpos[0]*16)
      player[curplay].screenx=data.startpos[0]*16;
    else
      player[curplay].screenx=0;
    if (player[curplay].screenx>0)
      marioy=data.startpos[1];
    mariox=40;
//    mariox=10;
    up=0;
    move=0;
    down=0;
    palloop=0;
//    tempc=data.palette[21];
    data.sprite=6;

    times[1]=(t[0]>>4)*10 + (t[0] & 0x0F);

    times[2]=times[1]-1;
    fillscreen(BACKGROUND);

	PlayMusic(player[curplay].level%10+1);
//	PcmStart(1);
    while(!finish)			//CURRENT LEVEL AND PLAYER LOOP//
    {
		PcmTask(0);
		PcmTask(1);

      rotatepal(&palloop,NULL);//couleurs BG et blocks partagés :(
//      fillscreen(BACKGROUND); //definit la couleur de fond
      drawscreen(player[curplay].screenx); //affiche fond d'ecran et sprites+images
      drawmario(mariox,marioy);

      times[1]=(t[0]>>4)*10 + (t[0] & 0x0F);
      if (marioy<207)
		check_keybuf(&move,&finish,&up,&down,&jumploop);

      animate_mario(move);
      move_mario(&move);
      check_jump(&up,&down,&jumploop);
      check_blocks();
      check_finish(&finish);
    }
	
//REACT TO END OF CURRENT PLAYER LOOP////////////////////////////////////////
    switch (finish)
    {
      case 1:
	player[curplay].lives--;
	StopMusic();
	PlayMode(finish);
	PlayMusic(7);
	 PcmStop(0);
	PcmStop(1);
	wait_seconds(2);
	StopMusic();
	SCL_DisplayFrame();
	wait_seconds(3);
	finish=0;
	if (numplayers==2)
	{
	  if (curplay==0 && player[1].lives!=0)
	    curplay=1;
	  else
	    if (curplay==1 && player[0].lives!=0)
	      curplay=0;
	}
	if (player[0].lives==0 && player[1].lives==0)
	  finish=3;
	break;
      case 2:
			StopMusic();
			PlayMode(finish);;
			PlayMusic(6);
			  PcmStop(0);
			  PcmStop(1);
			wait_seconds(4);
			StopMusic();
			SCL_DisplayFrame();
			wait_seconds(4);

	player[curplay].level++;
	if (player[curplay].level%5==0)
	  player[curplay].level++;
	player[curplay].screenx=0;
	finish=0;
	break;
      case 3:
			  PcmStop(0);
			  PcmStop(1);
    player[curplay].coins[0]=0;
	times[0]="   ";
	graphstring(130,100,"Game Over",TEXTCOLOR,VisiblePageOffs);
  	StopMusic();
//	while(!keybuf[KEY_ENTER]);
	break;
    }

  }
	PcmStop(0);
	PcmStop(1);
    player[curplay].coins[0]=0;
	graphstring(130,100,"Game Over",TEXTCOLOR,VisiblePageOffs);
  	StopMusic();
	PlayMode(finish);
	PlayMusic(8);
	wait_seconds(5);
	StopMusic();
	SCL_DisplayFrame();
	StopMusic();
	wait_seconds(5);
the_end:
	graphstring(130,100,"              ",TEXTCOLOR,VisiblePageOffs);

	long my_score;
	sscanf(pscore,"%d",&my_score);
	sprintf(pscore,"000000");
	player[0].score[0]=0;
	player[0].score[1]=0;
	if(my_score>high_score)
		high_score=my_score;

	main2();

	SYS_Exit(0);
//RETURN SCREEN AND KEYBOARD TO NORMAL///////////////////////////////////////
//  exitgame();
}
//END////////////////////////////////////////////////////////////////////////
