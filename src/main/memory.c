
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "main.h"
#include "compressionbuffer.h"
#include "graphic.h"


int MemorySize = 4;
uint FreeSpaceAddress = 0x08000000;
uint SegmentTable[16];

uint RawBufferPointer;
/**** message queues and message buffers used by this app ****/
OSPiHandle	*handler;
static OSMesg           PiMessages[200];
static OSMesgQueue      PiMessageQ;
static OSMesgQueue      dmaMessageQ;
static OSMesg           dmaMessageBuf;

void InitDMA()
{
    handler = osCartRomInit();
    osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);
}
void LoadDMA(const char *src, const char *dest, const int len)
{
    OSIoMesg dmaIoMesgBuf;
    OSMesg dummyMesg;
    
    /*
     * Always invalidate cache before dma'ing data into the buffer.
     * This is to prevent a flush of the cache in the future from 
     * potentially trashing some data that has just been dma'ed in.
     * Since you don't care if old data makes it from cache out to 
     * memory, you can use the cheaper osInvalDCache() instead of one
     * of the writeback commands
     */
    osInvalDCache((void *)dest, (s32) len);

    dmaIoMesgBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
    dmaIoMesgBuf.hdr.retQueue = &dmaMessageQ;
    dmaIoMesgBuf.dramAddr     = (void*)dest;
    dmaIoMesgBuf.devAddr      = (u32)src;
    dmaIoMesgBuf.size         = (u32)len;
    osEPiStartDma(handler, &dmaIoMesgBuf, OS_READ);
    (void) osRecvMesg(&dmaMessageQ, &dummyMesg, OS_MESG_BLOCK);
}


extern void slidec1(unsigned char * Source,unsigned char * Target);

void SetSegment(uint SegmentID, uint RAMAddress)
{
    SegmentTable[SegmentID] = K0_TO_PHYS(RAMAddress);
}

uint GetRealAddress(uint RSPAddress)
{
	uint RSPNumber = SegmentNumber(RSPAddress);
	uint RSPOffset = SegmentOffset(RSPAddress);
	return(PHYS_TO_K0(SegmentTable[RSPNumber] + RSPOffset));
}

void StoreRSPSegments()
{
    for (int ThisRSP = 0; ThisRSP < 16; ThisRSP++)
    {
        gSPSegment(glistp++, ThisRSP, SegmentTable[ThisRSP]);
    }
}

uint DecompressData(uint Source, uint CompressionLength)
{
    uint LoadAddress = RawBufferPointer;
    //LoadDMA((char*)Source, (char*)&CompressionBuffer, CompressionLength);
    nuPiReadRom(Source, (char*)&CompressionBuffer, CompressionLength);
    slidec1((char*)&CompressionBuffer, (char*)LoadAddress);

    uint Size = *(uint*)(((uint)&CompressionBuffer) + 4);
    RawBufferPointer += Align32(Size);

    return LoadAddress;
}