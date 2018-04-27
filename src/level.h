#ifndef LEVEL_H
#define LEVEL_H

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

class Level
{
public:
    Level();
private:
    struct LevelHeader;

};

#endif // LEVEL_H
