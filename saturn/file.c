#include "sega_gfs.h"
#ifdef DEBUG
#include "string.h"
#endif

//#define ACTIONREPLAY	0

#ifndef ACTIONREPLAY
#define	MAX_FILE		128
#define MAX_OPEN        20
#define MAX_DIR         128
#else
#define	MAX_FILE		1
#define MAX_OPEN        2
#define MAX_DIR         1
#endif
//#define DEBUG 1
#define GFS_ON 1

//extern int file_max;
//extern t_cart cart;
#ifndef ACTIONREPLAY
GfsDirName dir_name[MAX_DIR];
#endif

signed long LoadFile(char *name, Uint8 *location);
//00200000H
//--------------------------------------------------------------------------------------------------------------------------------------
void InitCD()
{
#ifndef ACTIONREPLAY
	Sint32 ret;
	CDC_CdInit(0x00,0x00,0x05,0x0f);
	Uint32 lib_work[GFS_WORK_SIZE(MAX_OPEN) / sizeof(Uint32)];
	GfsDirTbl dirtbl; 
    GFS_DIRTBL_TYPE(&dirtbl) = GFS_DIR_NAME;
    GFS_DIRTBL_DIRNAME(&dirtbl) = dir_name;
    GFS_DIRTBL_NDIR(&dirtbl) = MAX_DIR;
    ret = GFS_Init(MAX_OPEN, lib_work, &dirtbl);
#endif	    
}
//--------------------------------------------------------------------------------------------------------------------------------------
/*
void ChangeDir(char *dirname)
{
#ifndef ACTIONREPLAY	
    Sint32 fid;
	GfsDirTbl dirtbl; 
	
    fid = GFS_NameToId((Sint8 *)dirname);

	GFS_DIRTBL_TYPE(&dirtbl) = GFS_DIR_NAME;
	GFS_DIRTBL_DIRNAME(&dirtbl) = dir_name;
	GFS_DIRTBL_NDIR(&dirtbl) = MAX_DIR;

	for (;;) {
	    file_max = GFS_LoadDir(fid, &dirtbl)-2;
		if ( file_max >= 0) {
			break;
		}
	}
	for (;;) {
		if (GFS_SetDir(&dirtbl) == 0) {
			break;
		}
	}
#endif	
}
*/

//--------------------------------------------------------------------------------------------------------------------------------------
Sint32 GetFileSize(int file_id)
{
#ifndef ACTIONREPLAY	
	GfsHn gfs;
    Sint32 sctsize, nsct, lastsize;
    
    gfs = GFS_Open(file_id);
    GFS_GetFileSize(gfs, &sctsize, &nsct, &lastsize);

    GFS_Close(gfs);
	return (sctsize*(nsct-1) + lastsize);
#else
    return 900;
#endif	
}
//--------------------------------------------------------------------------------------------------------------------------------------
signed long LoadFile(char *name, Uint8 *location)
{
#ifndef ACTIONREPLAY	
	Sint32 		fid;//, i;
	Sint32 size;

//	for (i = 0; i < 10; i++) {
	fid = GFS_NameToId(name);

	size=GetFileSize(fid);

		if (fid >= 0) {
			GFS_Load(fid, 0, location, size);
			return size;
		}
//	}
	return -1;
#else
    return 0;
#endif	
}
//--------------------------------------------------------------------------------------------------------------------------------------