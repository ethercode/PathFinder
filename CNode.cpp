//---------------------------------------------------------------------------


#pragma hdrstop

#include "CNode.h"
#include "mainform.h"

CNode::CNode(CNode* NewParent, int x, int y)
{
    Parent = NewParent;
    Location.x = x;
    Location.y = y;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
