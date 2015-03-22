#include "sega_sys.h"  
#include "sega_per.h"
#include "sega_scl.h"
#include "per_x.h" 
#include "main.h"
#include "shared.h"
//#include "saturn.h"

//---------------------------------------------------------------------------------------------
void useSlave(Uint32 param, volatile Uint32 *function)
{
    slave_command = function;
    SlaveParam = param;
        
    *(Uint16 *)0x21000000 = 0xffff; /* slave FRT inp invoke */
}
//---------------------------------------------------------------------------------------------
void waitSlave()
{
    while( slave_command != 0 )
    	;
}
//---------------------------------------------------------------------------------------------
