#include "level.h"

Level::MAPLinker::MAPLinker()
{
    MAPLinkerLineRecord tempRecord;
    tempRecord.LinkerTypeFlag = 0;
    tempRecord.RoomID = 0;
    tempRecord.x1 = 0;
    tempRecord.x2 = 0;
    tempRecord.y1 = 0;
    tempRecord.y2 = 0;
    tempRecord.LinkerDestination = 0;
    tempRecord.HorizontalDisplacement = 0;
    tempRecord.VerticalDisplacement = 0;
    tempRecord.SpritesMAP_ID = 0;
    tempRecord.BGM_ID_FirstByte = 0;
    tempRecord.BGM_ID_SecondByte = 0;
    MAPLinkerRecord.push_back(tempRecord);
    LevelHeaderData.HardModeMinuteNum = 0;
    LevelHeaderData.HardModeSecondOnePlaceNum = 0;
    LevelHeaderData.HardModeSecondTenPlaceNum = 0;
    LevelHeaderData.HeaderPointerIndex = 0;
    LevelHeaderData.NormalModeMinuteNum = 0;
    LevelHeaderData.NormalModeSecondOnePlaceNum = 0;
    LevelHeaderData.NormalModeSecondTenPlaceNum = 0;
    LevelHeaderData.NumOfMap = 0;
    LevelHeaderData.SHardModeMinuteNum = 0;
    LevelHeaderData.SHardModeSecondOnePlaceNum = 0;
    LevelHeaderData.SHardModeSecondTenPlaceNum = 0;
    LevelHeaderData.Unknown0A = (unsigned char)10;
}

bool Level::MAPLinker::IsLinkerBlockRepeat(unsigned char _RoomID, unsigned char _x1, unsigned char _x2, unsigned char _y1, unsigned char _y2)
{
    std::list<MAPLinkerLineRecord>::iterator i;
    for(i=MAPLinkerRecord.begin(); i!=MAPLinkerRecord.end(); i++)
        if(i->RoomID == _RoomID)
        {
            if(((i->x1 <= _x1)&&(_x2 <= i->x2)) || ((_x1 <= i->x1)&&(i->x2 <= _x2)))
                return true;
            if(((i->y1 <= _y1)&&(_y2 <= i->y2)) || ((_y1 <= i->y1)&&(i->y2 <= _y2)))
                return true;
        }
    return false;
}

bool Level::MAPLinker::AddNewLinker(MakeLinkerFlag MakeLinkerTypeFlag, unsigned char _LinkerTypeFlag, unsigned char _RoomID,
                                unsigned char _x1, unsigned char _x2, unsigned char _y1, unsigned char _y2,
                                unsigned char _LinkerDestination, unsigned char _HorizontalDisplacement, unsigned char _VerticalDisplacement,
                                unsigned char _SpritesMAP_ID, unsigned char _BGM_ID_FirstByte, unsigned char _BGM_ID_SecondByte)

{
    if((_x1>_x2 || _y1>_y2) || (IsLinkerBlockRepeat(_RoomID, _x1, _x2, _y1, _y2)))   //judge before save record
        return false;
    MAPLinkerLineRecord tempRecord;
    tempRecord.LinkerTypeFlag = _LinkerTypeFlag;
    tempRecord.RoomID = _RoomID;
    tempRecord.x1 = _x1;
    tempRecord.x2 = _x2;
    tempRecord.y1 = _y1;
    tempRecord.y2 = _y2;
    tempRecord.LinkerDestination = _LinkerDestination;
    tempRecord.HorizontalDisplacement = _HorizontalDisplacement;
    tempRecord.VerticalDisplacement = _VerticalDisplacement;
    tempRecord.SpritesMAP_ID = _SpritesMAP_ID;
    tempRecord.BGM_ID_FirstByte = _BGM_ID_FirstByte;
    tempRecord.BGM_ID_SecondByte = _BGM_ID_SecondByte;

    std::list<MAPLinkerLineRecord>::iterator i;

    if(MakeLinkerTypeFlag == MakeLinkerFlag_PortalRecord)
    {
        if(tempRecord.LinkerTypeFlag != '\1')
            return false;
        for(i=MAPLinkerRecord.begin(); i!=MAPLinkerRecord.end(); i++)
            if(i->LinkerTypeFlag != 0) //if i is not the last one
                i->LinkerDestination = (i->LinkerDestination)+1;
        MAPLinkerRecord.push_front(tempRecord);
        return true;
    }
    if(MakeLinkerTypeFlag == MakeLinkerFlag_OnlySetBlockAndType)
    {
        if(tempRecord.LinkerTypeFlag == '\1')
            return false;
        i=MAPLinkerRecord.end();
        i--; i--;   //get the last record but one
        tempRecord.LinkerDestination = (unsigned char)MAPLinkerRecord.size();
        MAPLinkerRecord.insert(i, tempRecord);
        return true;
    }
    if(MakeLinkerTypeFlag == MakeLinkerFlag_linkExistRecord)  //not support, use the other one
        return false;
    if(MakeLinkerTypeFlag == MakeLinkerFlag_ChangeBGM)
    {
        for(i=MAPLinkerRecord.begin(); i!=MAPLinkerRecord.end(); i++)
        {
            if(i->LinkerTypeFlag == 0)
                return false;
            if((i->RoomID == _RoomID) && (i->x1 == _x1) && (i->y1 == _y1))
                break;
        }
        i->BGM_ID_FirstByte = _BGM_ID_FirstByte;
        i->BGM_ID_SecondByte = _BGM_ID_SecondByte;
        return true;
    }
    return false;
}

bool Level::MAPLinker::AddNewLinker(MakeLinkerFlag MakeLinkerTypeFlag, unsigned char First_RoomID, unsigned char First_x1, unsigned char First_y1,
                                    unsigned char Second_RoomID, unsigned char Second_x1, unsigned char Second_y1)
{
    if(MakeLinkerTypeFlag == MakeLinkerFlag_linkExistRecord)
    {
        std::list<MAPLinkerLineRecord>::iterator i, j;
        unsigned char icount, jcount;
        icount = 0; jcount = 0;

        for(i=MAPLinkerRecord.begin(); i!=MAPLinkerRecord.end(); i++)
        {
            if(i->LinkerTypeFlag == 0)
                return false;
            if((i->RoomID == First_RoomID) && (i->x1 == First_x1) && (i->y1 == First_y1))
                break;
            icount++;
        }
        for(j=MAPLinkerRecord.begin(); j!=MAPLinkerRecord.end(); j++)
        {
            if(j->LinkerTypeFlag == 0)
                return false;
            if((j->RoomID == Second_RoomID) && (j->x1 == Second_x1) && (j->y1 == Second_y1))
                break;
            jcount++;
        }
        i->LinkerDestination = jcount;
        j->LinkerDestination = icount;
        return true;
    }
    return false;
}

bool Level::MAPLinker::FindUnLinkedLinker(std::list<MAPLinkerLineRecord> &UnLinkedLinkerRecord)
{
    std::list<MAPLinkerLineRecord>::iterator i;
    unsigned char icount;
    icount = 0;

    for(i=MAPLinkerRecord.begin(); i!=MAPLinkerRecord.end(); i++)
    {
        if(i->LinkerTypeFlag == 0)
            continue;
        if(i->LinkerDestination == icount)
            UnLinkedLinkerRecord.push_back(*i);
        icount++;
    }

    if(UnLinkedLinkerRecord.size()>0)
        return true;
    return false;
}

bool Level::SetHardModeTimeCountdownCounter(unsigned char _MinuteNum, unsigned char _SecondTenPlaceNum, unsigned char _OnePlaceNum)
{
    if((_SecondTenPlaceNum > 5 )&&(_OnePlaceNum >9 ))
        return false;
    LevelHeaderData.HardModeMinuteNum = _MinuteNum;
    LevelHeaderData.HardModeSecondTenPlaceNum = _SecondTenPlaceNum;
    LevelHeaderData.HardModeSecondOnePlaceNum = _OnePlaceNum;
    return true;
}

bool Level::SetNormalModeTimeCountdownCounter(unsigned char _MinuteNum, unsigned char _SecondTenPlaceNum, unsigned char _OnePlaceNum)
{
    if((_SecondTenPlaceNum > 5 )&&(_OnePlaceNum >9 ))
        return false;
    LevelHeaderData.NormalModeMinuteNum = _MinuteNum;
    LevelHeaderData.NormalModeSecondTenPlaceNum = _SecondTenPlaceNum;
    LevelHeaderData.NormalModeSecondOnePlaceNum = _OnePlaceNum;
    return true;
}

bool Level::SetSHardModeTimeCountdownCounter(unsigned char _MinuteNum, unsigned char _SecondTenPlaceNum, unsigned char _OnePlaceNum)
{
    if((_SecondTenPlaceNum > 5 )&&(_OnePlaceNum >9 ))
        return false;
    LevelHeaderData.SHardModeMinuteNum = _MinuteNum;
    LevelHeaderData.SHardModeSecondTenPlaceNum = _SecondTenPlaceNum;
    LevelHeaderData.SHardModeSecondOnePlaceNum = _OnePlaceNum;
    return true;
}
