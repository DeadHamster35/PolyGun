.include "macros.inc"


.section .data


glabel _BlockTestSeg4
.incbin "/src/leveldata/BlockTest/Segment4.MIO0"
.balign 16
glabel _BlockTestSeg4END

glabel _BlockTestSeg5
.incbin "/src/leveldata/BlockTest/Segment5.MIO0"
.balign 16
glabel _BlockTestSeg5END

glabel _BlockTestSeg6
.incbin "/src/leveldata/BlockTest/Segment6.MIO0"
.balign 16
glabel _BlockTestSeg6END
