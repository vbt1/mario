/*
 *  Slave SH2 Driver Module
 *
 *  <1st version>: FRT inputcapture is not supported. (1994-04-01)
 *                 SOUND RAM is used for MasterSH SlaveSH Handshake flag.
 *
 *  <2nd version>: FRT inputcapture is supported. (1994-04-01)
 *                 work RAM is used for Master Slave parameter passing.
 *
 */

#include "sega_xpt.h"
#include <stdlib.h>
#include <machine.h>

#define VBR   0x06000000
#define SETSINT   ((Sint32 (*)()) *((Uint32*)(VBR+0x310)))

#if	0
/*
**Å°1995-09-21	çÇã¥íqâÑ
**	ÉXÉåÅ[Éuë§Ç∆ÇÃÇhÅ^ÇeÇÕ cache through Ç©Ç¬ volatile Ç…Ç∑ÇÈÇ±Ç∆ÅB
*/
Uint32
  *SlaveCommand  = (Uint32 *)0;          /* MASTER to SLAVE command AREA */
#else
volatile Uint32	*SlaveCommand = NULL;
#define	FTCSR			*( volatile Uint8 * )0xfffffe11
#define	slave_command	*( volatile Uint32 * )((Uint32)&SlaveCommand+0x20000000)
#endif

#if	0
/*
 *'95-11-01 H.Okamoto
 * Subcpu status
 * 0: Subcpu is sleeping.
 * 1: Subcpu is running.
 */

Uint32
  SlaveState    = (Uint32)0;             /* SLAVE to MASTER state  AREA */
#else
volatile int	SlaveStatus;             /* SLAVE to MASTER state  AREA */
#define slavestatus	*(volatile int *)((Uint32)&SlaveStatus+0x20000000)
#endif
Uint32
  SlaveParam    = (Uint32)0;             /* MASTER to SLAVE parameter  AREA */

void **SlaveSHEntry
  = (void **)0x6000250;                 /* BOOT ROMs dispatch address */

volatile Uint8 *SMPC_COM = (Uint8 *)0x2010001F;   /* SMPC command register */

volatile Uint8 *SMPC_RET = (Uint8 *)0x2010005f;   /* SMPC result register */

volatile Uint8 *SMPC_SF  = (Uint8 *)0x20100063;   /* SMPC status flag */

const Uint8 SMPC_SSHON  = 0x02;          /* SMPC slave SH on command */

const Uint8 SMPC_SSHOFF = 0x03;          /* SMPC slave SH off command */

/* ============ DECLARE FUNCTIONS =========== */

void InitSlaveSH(void);

void SlaveSHmain(void);

/* ============ DEFINE FUNCTIONS ============ */

/* -Change BOOT ROMs "slave SH dummy loop entry" To "SlaveSHmain entry" */
/* -Enable Slave SH with SMPC command SSHON                             */
/* -Then Slave SH start and Initialized by BOOT ROM code                */
/* -Finally Slave SH round a flag checking loop in SlaveSHmain          */

void /* slave SH Initialize (RUNS on main SH) */
  InitSlaveSH(void)
{
    volatile Uint16 i;

    /* SlaveSH ÇÃÉäÉZÉbÉgèÛë‘Çê›íËÇ∑ÇÈ */
    while((*SMPC_SF & 0x01) == 0x01);
    *SMPC_SF = 1;                 /* --- SMPC StatusFlag SET */
#if 0	/* 95.12.22 kkawai  */
    *SMPC_COM = SMPC_SSHOFF;      /* --- Slave SH OFF SET */
    while((*SMPC_SF & 0x01) == 0x01);
#endif
    for(i = 0 ; i < 1000; i++);   /* slave reset assert length */
    slavestatus = 0;                /* make subcpu sleep */
#if 0
    *(void **)SlaveSHEntry = (void *)&SlaveSHmain; /* dispatch address set */
#endif
	SETSINT(0x94,(void *)&SlaveSHmain);
    /* SlaveSH ÇÃÉäÉZÉbÉgèÛë‘ÇâèúÇ∑ÇÈ */
    *SMPC_SF = 1;                 /* --- SMPC StatusFlag SET */
    *SMPC_COM = SMPC_SSHON;       /* --- Slave SH ON SET */
    while((*SMPC_SF & 0x01) == 0x01);
    while(slavestatus == 0);
}

void /* Slave SH2 main loop (RUNS on slave SH) */
  SlaveSHmain(void)
{
/*	95-7-26 unuse
    const Uint32 RUNNING = 1;
    const Uint32 WAITING = 0;
*/

    /* Wait until SlaveSHReqCode is set */
    /* then call function for SlaveSHReqCode */
    set_imask(0xf);
    *(Uint16 *)0xfffffee2 = 0x0000;  /* IPRA int disable */
    *(Uint16 *)0xfffffe60 = 0x0000;  /* IPRB int disable */
    *(Uint8 *)0xfffffe10  = 0x01;    /* TIER FRT INT disable */
	slavestatus = 1;
#if	0
/*
**Å°1995-09-21	çÇã¥íqâÑ
**	ÉXÉåÅ[Éuë§Ç∆ÇÃÇhÅ^ÇeÇÕ cache through Ç©Ç¬ volatile Ç…Ç∑ÇÈÇ±Ç∆ÅB
*/
    while(1){
	/* Use "FRT InputCaptureFlag" Poling for wait command from Master */
        if((*(Uint8 *)0xfffffe11 & 0x80) == 0x80){
	    *(Uint8 *)0xfffffe11 = 0x00; /* FTCSR clear */

	    (*(void (*)(void))*(void **)((Uint32)&SlaveCommand+0x20000000))();
	    SlaveCommand = (void *)0;      /* RESET request code */
	}
    }
#else
	for(;;){
		if(( FTCSR & 0x80 ) != 0 ){
			FTCSR = 0;
			
			(( void (*)( void ))slave_command )();
			
			slave_command = 0;
		}
	}
#endif
}

