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
}

bool Level::MAPLinker::AddNewLinker(int MakeLinkerTypeFlag, unsigned char _LinkerTypeFlag, unsigned char _RoomID,
                                unsigned char _x1, unsigned char _x2, unsigned char _y1, unsigned char _y2,
                                unsigned char _LinkerDestination, unsigned char _HorizontalDisplacement, unsigned char _VerticalDisplacement,
                                unsigned char _SpritesMAP_ID, unsigned char _BGM_ID_FirstByte, unsigned char _BGM_ID_SecondByte)
{
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
                i->LinkerDestination = i->LinkerDestination+1;
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
    //TODO: add other condition branches, the difference between is the methods used in list
    //TODO: add function to check if (x1, y1)-(x2, y2) area has been used
    return true;
}
