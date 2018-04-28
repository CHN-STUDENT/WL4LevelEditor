#ifndef LEVEL_H
#define LEVEL_H

#ifndef _DEQUE_
#include <list>
#endif

struct LevelHeader
{
    unsigned char HeaderPointerIndex;   //multiply 4 make a shift from some base pointers
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

struct MAPLinkerLineRecord
{
    unsigned char LinkerTypeFlag; //x01 for portal only, x02 for instant shift, x03 for door and tube, x04 unknown, x05 unknown
    unsigned char RoomID; //start from x00
    unsigned char x1;
    unsigned char x2;
    unsigned char y1;
    unsigned char y2;  //topleft judge block position (x1, y1), bottomleft judge block position (x2, y2), the first block start from (0, 0)
    unsigned char LinkerDestination;
    //multiply x0C make a shift to find another linker record to find the destination ROOM by RoomID, wario will appear at the position(x1, y1) in a (new) MAP
    //and immediately shift the position with vector (HorizontalDisplacement, VerticalDisplacement)
    //if set LinkerTypeFlag=0x01 for protal, then you should set LinkerDestination, HorizontalDisplacement and VerticalDisplacement all be 0x00
    unsigned char HorizontalDisplacement;
    unsigned char VerticalDisplacement;  //the two numbers can be negtivate by using this function: ResultByte = 0x100 + (the negtive number), so -1 just input 0xFF
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
        std::list<MAPLinkerLineRecord> MAPLinkerRecord;
        //remember to add a all-zero record at the bottom of the deque,on loading a new room, the game engine will stop searching the list by a  all-zero record
    public:

    };

};

#endif // LEVEL_H
