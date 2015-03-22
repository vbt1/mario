#include "saturn.h"
#include "main.h"

extern SysPort		*__port;
const  SysDevice	*device;
trigger_t	        pltrigger[2],pltriggerE[2];
#define SPRITES 400
extern SprSpCmd sprites[SPRITES];
//int firepflag=FALSE,fire2pflag=FALSE,pausef=FALSE;

//-----------------------------------------------------------------------------
int getControlSubMenu(int *i)
{
    if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
    {
    	pltrigger[0]  = PER_GetTrigger( device );
        checkExitHere(pltrigger[0]);
        
    	if((pltrigger[0] & PER_DGT_U)!=0)
    	{
            *i = (*i>0) ? *i-1 : 3;                         
            wait(1000000);
            return 2;
        }
    	if((pltrigger[0] & PER_DGT_D)!=0)
    	{
            *i = (*i<4) ? *i+1 : 0;                           
            wait(1000000);            
            return 2;
        }        
    	if((pltrigger[0] & PER_DGT_B)!=0)
    	{
            memset(SCL_VDP2_VRAM_A1,0,512*256);
            return 1;
        }        

    	if((pltrigger[0] & PER_DGT_S)!=0)
    	{
            memset(SCL_VDP2_VRAM_A1,0,512*256);

            if (*i==0)
               return 3;
            else if(*i==1)
               return 4;
            else if(*i==2)
               return 5;            
            else if(*i==3)            
               return 6;            
        }          
    }
    return 2;
}
//-----------------------------------------------------------------------------
int getControlMainMenu(int *i)
{
    if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
    {
    	pltrigger[0]  = PER_GetTrigger( device );
        checkExitHere(pltrigger[0]);
        
    	if((pltrigger[0] & PER_DGT_S)!=0)
    	{
            memset(SCL_VDP2_VRAM_A1,0,512*256);
            *i = 0;
            wait(1000000);              
            return 2;
        }
    }
    return 1;
}
//-----------------------------------------------------------------------------
int getControlCreditsMenu(int *i)
{
    if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
    {
    	pltrigger[0]  = PER_GetTrigger( device );
        checkExitHere(pltrigger[0]);
        
    	if((pltrigger[0] & PER_DGT_B)!=0)
    	{
            memset(SCL_VDP2_VRAM_A1,0,512*256);
            *i = 0;
            wait(1000000);              
            return 2;
        }
    }
    return 6;
}
//-----------------------------------------------------------------------------
int getControlConfigurationMenu(int *i)
{
    if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
    {
    	pltrigger[0]  = PER_GetTrigger( device );
        checkExitHere(pltrigger[0]);
        
    	if((pltrigger[0] & PER_DGT_B)!=0)
    	{
            memset(SCL_VDP2_VRAM_A1,0,512*256);
            *i = 0;
            wait(1000000);              
            return 2;
        }
    }
    return 5;
}
//-----------------------------------------------------------------------------
void checkExitHere(Uint16 data)
{
 // check exit
 if(          ((data & PER_DGT_S) != 0) 
           && ((data & PER_DGT_A) != 0) 
           && ((data & PER_DGT_B) != 0) 
           && ((data & PER_DGT_C) != 0)
   ) 
 {
     SYS_Exit(0);
}
}
//-----------------------------------------------------------------------------
/*
Sint4 getdir(int n)
{
  Sint4 dir;

    dir=DIR_NONE;
    firepflag=FALSE;

   if(( device = PER_GetDeviceR( &__port[0], 0 )) != NULL )
    {
    	pltrigger[0]  = PER_GetTrigger( device );
        checkExitHere(pltrigger[0]);
        
    	if((pltrigger[0] & PER_DGT_U)!=0)
    	{
             dir=DIR_UP; 
//             wait(1000000);                  
        }
    	if((pltrigger[0] & PER_DGT_D)!=0)
    	{
            dir=DIR_DOWN;                        
//            wait(1000000);            
        }    

    	if((pltrigger[0] & PER_DGT_R)!=0)
    	{
            dir=DIR_RIGHT;                        
//            wait(1000000);            
        } 

    	if((pltrigger[0] & PER_DGT_L)!=0)
    	{
            dir=DIR_LEFT;                        
//            wait(1000000);            
        }     
        
    	if((pltrigger[0] & PER_DGT_A)!=0)
    	{        
            if(sprites[FIRSTDIGGER+n].control == ( JUMP_NEXT | FUNC_NORMALSP | DIR_LRREV))
                  sprites[FIRSTFIREBALL+n].control = ( JUMP_NEXT | FUNC_NORMALSP | DIR_LRREV);
            else            
                  sprites[FIRSTFIREBALL+n].control = ( JUMP_NEXT | FUNC_NORMALSP | DIR_NOREV);

            firepflag=TRUE;
        }
        
        if ((pltrigger[0] & PER_DGT_S)!=0)
        {
         pausef = (pausef== TRUE) ? FALSE : TRUE;
         wait(500000);  
        }
    }
wait(130000);  
  return dir;
}
*/
//-----------------------------------------------------------------------------
void testpause(void)
{
     
   FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
  (Uint8 *)"PAUSE",120,104,     1,2,3,0);
/*       
   while(pausef == TRUE)
   {
         getdir(DIR_NONE);
   }
*/   
   FNT_Print256_2bpp((volatile Uint8 *)SCL_VDP2_VRAM_A1,
  (Uint8 *)"     ",120,104,     0,0,0,0);
     
}
//-----------------------------------------------------------------------------
