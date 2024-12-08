#ifndef MemoryH
#define MemoryH

#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "main.h"


extern int MemorySize;
extern uint FreeSpaceAddress;
extern uint RawBufferPointer;
extern uint SegmentTable[];

extern void InitDMA();
extern void LoadDMA(const char *src, const char *dest, const int len);
extern void SetSegment(uint SegmentID, uint RAMAddress);
extern uint GetRealAddress(uint RSPAddress);
extern void StoreRSPSegments();
extern void mio0decode(unsigned char * Source,unsigned char * Target);
extern uint DecompressData(uint Source, uint CompressionLength);
#endif

