OUTPUT_ARCH (mips)
SECTIONS
{
   __romPos = 0;
   _bootSegmentStart = ADDR(.boot); _bootSegmentRomStart = __romPos; .boot 0x04000000 : AT(__romPos)
   {
      build/asm/rom_header.o(.text);
      build/boot.6102.o(.data);
   }
   _bootSegmentEnd = ALIGN(ADDR(.boot) + SIZEOF(.boot),0x10); _bootSegmentRomEnd = _bootSegmentEnd - _bootSegmentStart + _bootSegmentRomStart; __romPos = _bootSegmentRomEnd; . = _bootSegmentEnd;
   _codeSegmentStart = ADDR(.code); _codeSegmentRomStart = __romPos; .code 0x80025c00 : AT(__romPos) SUBALIGN(16)
   {
  build/asm/entry.o(.start);
      /usr/lib/n64/nusys/nusys_isv.o(.text);
      build/src/main*.o(.text);
      */libultra_d.a:*.o(.text);
      build/src/buffers*.o(.text);
      build/asm/compression.o(.text);
      build/asm/mathtables.o(.text);
      */libultra_rom.a:*.o(.text);
      */libnusys.a:*.o(.text);
      */libnualsgi_n.a:*.o(.text);
      */libn_audio.a:*.o(.text);
      */libgcc.a:*.o(.text);
      /usr/lib/n64/PR/rspboot.o(.text);
      /usr/lib/n64/PR/aspMain.o(.text);
      /usr/lib/n64/PR/n_aspMain.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.text);
      /usr/lib/n64/PR/gspL3DEX2.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.Rej.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.NoN.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DLX2.Rej.fifo.o(.text);
      /usr/lib/n64/PR/gspS2DEX2.fifo.o(.text);
      /usr/lib/n64/nusys/nusys_isv.o(.data*);
      build/src/main*.o(.data*);
      */libultra_d.a:*.o(.data*);
      build/src/buffers*.o(.data*);
      build/asm/compression.o(.data*);
      build/asm/mathtables.o(.data*);
      */libultra_rom.a:*.o(.data*);
      */libnusys.a:*.o(.data*);
      */libnualsgi_n.a:*.o(.data*);
      */libn_audio.a:*.o(.data*);
      /usr/lib/n64/PR/rspboot.o(.data*);
      /usr/lib/n64/PR/aspMain.o(.data*);
      /usr/lib/n64/PR/n_aspMain.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.data*);
      /usr/lib/n64/PR/gspL3DEX2.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.Rej.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.NoN.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DLX2.Rej.fifo.o(.data*);
      /usr/lib/n64/PR/gspS2DEX2.fifo.o(.data*);
      /usr/lib/n64/nusys/nusys_isv.o(.*rodata*);
      build/src/main*.o(.*rodata*);
      */libultra_d.a:*.o(.*rodata);
      build/src/buffers*.o(.*rodata*);
      build/asm/compression.o(.*rodata*);
     build/asm/mathtables.o(.*rodata*);
      */libultra_rom.a:*.o(.*rodata*);
      */libnusys.a:*.o(.*rodata*);
      */libnualsgi_n.a:*.o(.*rodata*);
      */libn_audio.a:*.o(.*rodata*);
      */libgcc.a:*.o(.*rodata*);
   }
   _codeSegmentEnd = ALIGN(ADDR(.code) + SIZEOF(.code),0x10); _codeSegmentRomEnd = _codeSegmentEnd - _codeSegmentStart + _codeSegmentRomStart; __romPos = _codeSegmentRomEnd; . = _codeSegmentEnd;
   _codeSegmentBssStart = ADDR(.code.noload); .code.noload (NOLOAD) :
   {
      /usr/lib/n64/nusys/nusys_isv.o(COMMON);
      /usr/lib/n64/nusys/nusys_isv.o(.scommon);
      /usr/lib/n64/nusys/nusys_isv.o(.*bss*);
      build/src/main*.o(.*bss*);
      */libultra_d.a:*.o(.*bss*);
      build/src/buffers*.o(.*bss*);
      build/asm/compression.o(.*bss*);
    build/asm/mathtables.o(.*bss*);
      */libultra_rom.a:*.o(COMMON);
      */libultra_rom.a:*.o(.scommon);
      */libultra_rom.a:*.o(.*bss*);
      */libnusys.a:*.o(COMMON);
      */libnusys.a:*.o(.scommon);
      */libnusys.a:*.o(.*bss*);
      */libnualsgi_n.a:*.o(COMMON);
      */libnualsgi_n.a:*.o(.scommon);
      */libnualsgi_n.a:*.o(.*bss*);
      */libn_audio.a:*.o(COMMON);
      */libn_audio.a:*.o(.scommon);
      */libn_audio.a:*.o(.*bss*);
   }
   _codeSegmentBssEnd = ALIGN(ADDR(.code.noload) + SIZEOF(.code.noload),0x10); _codeSegmentBssSize = _codeSegmentBssEnd - _codeSegmentBssStart; . = _codeSegmentBssEnd;
   _level_dataSegmentStart = ADDR(.level_data); _level_dataSegmentRomStart = __romPos; .level_data __romPos : AT(__romPos)
   {
        build/asm/level_data.o(.data);
   }
   _level_dataSegmentEnd = ALIGN(ADDR(.level_data) + SIZEOF(.level_data),0x10); _level_dataSegmentRomEnd = _level_dataSegmentEnd - _level_dataSegmentStart + _level_dataSegmentRomStart; __romPos = _level_dataSegmentRomEnd; . = _level_dataSegmentEnd;
   _sound_dataSegmentStart = ADDR(.sound_data); _sound_dataSegmentRomStart = __romPos; .sound_data __romPos : AT(__romPos)
   {
      build/sound/sound_data.o(.data);
   }
   _sound_dataSegmentEnd = ALIGN(ADDR(.sound_data) + SIZEOF(.sound_data),0x10); _sound_dataSegmentRomEnd = _sound_dataSegmentEnd - _sound_dataSegmentStart + _sound_dataSegmentRomStart; __romPos = _sound_dataSegmentRomEnd; . = _sound_dataSegmentEnd;
   /DISCARD/ :
   {
      *(*);
   }
}
