#include "level.h"

Level::MAPLinker::MAPLinker()
{
    Level.MAPLinker.MAPLinkerRecord.clear();
    Level.MAPLinker.MAPLinkerRecord.push_back({\0, \0, \0, \0, \0, \0, \0, \0, \0, \0, \0, \0});
}

Level::MAPLinker::MakeNewLinker(int MakeLinkerTypeFlag, unsigned char _LinkerTypeFlag, unsigned char _RoomID,
                                unsigned char _x1, unsigned char _x2, unsigned char _y1, unsigned char _y2,
                                unsigned char _LinkerDestination, unsigned char _HorizontalDisplacement, unsigned char _VerticalDisplacement,
                                unsigned char _SpritesMAP_ID, unsigned char _BGM_ID_FirstByte, unsigned char _BGM_ID_SecondByte)
{
    MAPLinkerLineRecord tempRecord;
    tempRecord.LinkerTypeFlag = '\0';
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

    if(MakeLinkerTypeFlag == MakeLinkerFlag_PortalRecord)
        Level.MAPLinker.MAPLinkerRecord.push_front(tempRecord);

    //TODO: add other condition branches, the difference between is the methods used in deque
}
