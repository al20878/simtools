/* Device.h V2.1    Definitions for device routines */

/*
        This is part of ODS2 written by Paul Nankervis,
        email address:  Paulnank@au1.ibm.com

        ODS2 is distributed freely for all members of the
        VMS community to use. However all derived works
        must maintain comments in their source to acknowledge
        the contibution of the original author.
*/

#ifndef _DEVICE_H
#define _DEVICE_H

#ifdef _WIN32
#include <windows.h>		/* HANDLE */
#endif

#include "access.h"
#include "cache.h"

struct DEV {                    /* Device information */
    struct CACHE cache;
    struct VCB *vcb;            /* Pointer to volume (if mounted) */
    int      access;            /* Device mount options (e.g., /Write) */
    unsigned sectors;           /* Device physical sectors */
#ifdef _WIN32
    short    drive;             /* Drive no. (0=A, 1=B, 2=C, ...) */
    unsigned bytespersector;    /* Device physical sectorsize (bytes) */
    unsigned blockspersector;   /* Device physical sectorsize (blocks) */
    union {
        struct {                /* Device uses Win32 APIs for physical I/O */
            HANDLE   handle;    /* Win32 I/O handle */
        } Win32;
        struct {                /* Device uses ASPI APIs for physical I/O */
            short    dtype;     /* ASPI disk type  */
            short    bus;       /* ASPI device bus */
            short    id;        /* ASPI device id  */
        } ASPI;
    } API;
    char    *IoBuffer;          /* Pointer to a buffer for the device */
    unsigned last_sector;       /* Last sector no read (still in buffer) */
#else
    int      handle;            /* Device physical I/O handle */
#endif
    char devnam[1];             /* Device name */
};

unsigned device_lookup( unsigned devlen, char *devnam, int create,
                        struct DEV **retdev );

#endif /* # ifndef _DEVICE_H */
