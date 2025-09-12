.include "macros.inc"

.section .data

.balign 16
glabel _miditableSegmentRomStart
.incbin "GenMidiBank.tbl"
glabel _miditableSegmentRomEnd

.balign 16
glabel _midibankSegmentRomStart
.incbin "GenMidiBank.ctl"
glabel _midibankSegmentRomEnd

.balign 16
glabel _sfxbankSegmentRomStart
.incbin "se.ctl"
glabel _sfxbankSegmentRomEnd

.balign 16
glabel _sfxtableSegmentRomStart
.incbin "se.tbl"
glabel _sfxtableSegmentRomEnd

.balign 16
glabel _seqSegmentRomStart
.incbin "songs.sbk"
glabel _seqSegmentRomEnd