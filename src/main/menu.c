
#include <nusys.h>
#include <nualsgi_n.h>
#include "common.h"
#include "main.h"
#include "compressionbuffer.h"
#include "graphic.h"


CharacterData PlayerCountParameters[] = {
    {"One",3},
    {"Two",3},
    {"Three",5},
    {"Four",4}
};


CharacterData LevelSelectParameters[] = {
    {"A30",3},
    {"RiverBed",8},
};

MenuOption MainMenuOptions[] = 
{
    { { "Players", 7 }, PlayerCountParameters, 4 },
    { { "Map", 3 }, LevelSelectParameters, 2 },
};



MenuPanel MainPanel = {
    .PanelName = { "Main Panel", 10 },
    .OptionArray = MainMenuOptions,  // Array decays into a pointer
    .OptionCount = 2
};

//CharacterData PlayerCountParameterOne = { "One", 3 };
