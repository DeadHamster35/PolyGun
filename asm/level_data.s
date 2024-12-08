.include "macros.inc"

.section .data



glabel _A30Seg4
.incbin "/src/main/leveldata/A30/Segment4.MIO0"
.balign 16
glabel _A30Seg4END

glabel _A30Seg5
.incbin "/src/main/leveldata/A30/Segment5.MIO0"
.balign 16
glabel _A30Seg5END

glabel _A30Seg6
.incbin "/src/main/leveldata/A30/Segment6.MIO0"
.balign 16
glabel _A30Seg6END


glabel _sandcastle4
.incbin "/src/main/leveldata/sandcastle/Segment4.MIO0"
.balign 16
glabel _sandcastle4END

glabel _sandcastle5
.incbin "/src/main/leveldata/sandcastle/Segment5.MIO0"
.balign 16
glabel _sandcastle5END

glabel _sandcastle6
.incbin "/src/main/leveldata/sandcastle/Segment6.MIO0"
.balign 16
glabel _sandcastle6END

