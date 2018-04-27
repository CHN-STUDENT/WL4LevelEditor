#ifndef LEVEL_H
#define LEVEL_H

#ifndef _DEQUE_
#include <deque>
#endif

struct LevelHeader
{
    unsigned char HeaderPointerIndex;   //multiply 4 make a shift for some base pointers
    unsigned char NumOfMap;
    unsigned char Unknown0A;   //always 0x0A
    unsigned char HardModeMinuteNum;
    unsigned char HardModeSecondTenPlaceNum;
    unsigned char HardModeSecondOnePlaceNum;
    unsigned char NormalModeMinuteNum;
    unsigned char NormalModeSecondTenPlaceNum;
    unsigned char NormalModeSecondOnePlaceNum;
    unsigned char SHardModeMinuteNum;
    unsigned char SHardModeSecondTenPlaceNum;
    unsigned char SHardModeSecondOnePlaceNum;
};

struct MAPLinkerLineRecord   //only
{
    unsigned char LinkerTypeFlag; //x01 for portal only, x02 for instant shift, x03 for door and tube, x04 unknown, x05 unknown
    unsigned char RoomID; //start from x00
    unsigned char x1;
    unsigned char x2;
    unsigned char y1;
    unsigned char y2;  //topleft judge block position (x1, y1), bottomleft judge block position (x2, y2), the first block start from (0, 0)
    unsigned char HorizontalDisplacement;
    unsigned char VerticalDisplacement;  //there is a position shifting after wario switch to new room
    unsigned char SpritesMAP_ID;
    unsigned char BGM_ID_FirstByte;  //Low Byte
    unsigned char BGM_ID_SecondByte;  //High Byte
};

class Level
{
public:
    Level();
private:
    struct LevelHeader;
public:
    class MAPLinker
    {
    public:
        MAPLinker();
    private:
        deque<MAPLinkerLineRecord> MAPLinkerRecord;
    };

};

#endif // LEVEL_H
