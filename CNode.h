//---------------------------------------------------------------------------

#ifndef CNodeH
#define CNodeH

#include <vcl.h>

class CNode
{
public:
            CNode(CNode*, int x, int y);
    CNode*  GetParent();
    TPoint  Location;
    CNode*  Parent;
private:
};

//---------------------------------------------------------------------------
#endif
