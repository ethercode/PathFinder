//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "CNode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain*   frmMain;
CNode*      PathGrid[128][128];
int         ObstacleGrid[128][128];
bool        Newbie[128][128];
CNode*      StartNode   = 0;
CNode*      EndNode     = 0;
bool        found;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner):
    TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button1Click(TObject* Sender)
{
    FindPath();
    if (found)
    {
        int     x, y;
        CNode*  n   = EndNode;
        while (n != StartNode)
        {
            x = n->Location.x;
            y = n->Location.y;
            Image1->Picture->Bitmap->Canvas->Pixels[x][y] = ((TColor) (0x00FF0000));
            n = n->Parent;
        }
    }
    else
    {
        MessageBox(Application->Handle, "No path to end!", "Error!", MB_OK);
    }
    for (int g = 0; g < 128; g++)
    {
        for (int h = 0; h < 128; h++)
        {
            delete PathGrid[g][h];
            PathGrid[g][h] = 0;
            ObstacleGrid[g][h] = 0;
            Newbie[g][h] = 0;
        }
    }
    found = false;
    StartNode = EndNode = 0;
    Button1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FindPath()
{
    int Pixel;
    for (int x = 0; x < 128; x++)
    {
        for (int y = 0; y < 128; y++)
        {
            Pixel = Image1->Picture->Bitmap->Canvas->Pixels[x][y];
            if (Pixel == 0x00FFFFFF)
            {
                ObstacleGrid[x][y] = 0;
                PathGrid[x][y] = 0;
            }
            else if (Pixel == 0x00000000)
            {
                ObstacleGrid[x][y] = 1;
                PathGrid[x][y] = 0;
            }
            else if (Pixel == 0x0000FF00)
            {
                ObstacleGrid[x][y] = 1;
                StartNode = new CNode(0, x, y);
                TPoint  Location;
                Location.x = x;
                Location.y = y;
                StartNode->Location = Location;
                PathGrid[x][y] = StartNode;
            }
            else if (Pixel == 0x000000FF)
            {
                ObstacleGrid[x][y] = 0;
                EndNode = new CNode(0, x, y);
                TPoint  Location;
                Location.x = x;
                Location.y = y;
                EndNode->Location = Location;
                PathGrid[x][y] = 0;
            }
        }
    }
    if (StartNode == 0)
    {
        MessageBox(Application->Handle, "No Starting Point!", "Error", MB_OK);
        return;
    }
    if (EndNode == 0)
    {
        MessageBox(Application->Handle, "No Ending Point!", "Error", MB_OK);
        return;
    }
    bool    expanded;
    found = false;
    while (!found)
    {
        for (int xx = 0; xx < 128; xx++)
        {
            for (int yy = 0; yy < 128; yy++)
            {
                if (PathGrid[xx][yy] != 0)
                {
                    Newbie[xx][yy] = false;
                }
            }
        }
        expanded = false;
        for (int x = 0; x < 128; x++)
        {
            for (int y = 0; y < 128; y++)
            {
                if (PathGrid[x][y] != 0)
                {
                    if (!Newbie[x][y])
                    {
                        expanded = ExpandNode(PathGrid[x][y]);
                    }
                }
            }
        }
        //if (!expanded) return;
    }
}

bool __fastcall TfrmMain::ExpandNode(CNode* node)
{
    bool    r   = false;
    int     x   = node->Location.x;
    int     y   = node->Location.y;
    if (PathGrid[x - 1][y] == 0 && ObstacleGrid[x - 1][y] == 0)
    {
        r = true;
        Newbie[x - 1][y] = true;
        PathGrid[x - 1][y] = new CNode(node, x - 1, y);
        if (x - 1 == EndNode->Location.x && y == EndNode->Location.y)
        {
            EndNode = node;
            found = true;
            return true;
        }
    }
    if (PathGrid[x + 1][y] == 0 && ObstacleGrid[x + 1][y] == 0)
    {
        r = true;
        Newbie[x + 1][y] = true;
        PathGrid[x + 1][y] = new CNode(node, x + 1, y);
        if (x + 1 == EndNode->Location.x && y == EndNode->Location.y)
        {
            EndNode = node;
            found = true;
            return true;
        }
    }
    if (PathGrid[x][y - 1] == 0 && ObstacleGrid[x][y - 1] == 0)
    {
        r = true;
        Newbie[x][y - 1] = true;
        PathGrid[x][y - 1] = new CNode(node, x, y - 1);
        if (x == EndNode->Location.x && y - 1 == EndNode->Location.y)
        {
            EndNode = node;
            found = true;
            return true;
        }
    }
    if (PathGrid[x][y + 1] == 0 && ObstacleGrid[x][y + 1] == 0)
    {
        r = true;
        Newbie[x][y + 1] = true;
        PathGrid[x][y + 1] = new CNode(node, x, y + 1);
        if (x == EndNode->Location.x && y + 1 == EndNode->Location.y)
        {
            EndNode = node;
            found = true;
            return true;
        }
    }
    return r;
}




void __fastcall TfrmMain::Button2Click(TObject* Sender)
{
    AnsiString  c;
    c += "To use:\n\r";
    c += "Make a 128x128 bitmap, and then put one green dot\n\r";
    c += "as starting point and a red as ending point.";
    Application->MessageBoxA(c.c_str(), "How to use", 0);
    od->InitialDir = ".";
    if (od->Execute())
    {
        Button1->Enabled = true;
        Image1->Picture->LoadFromFile(od->FileName);
    }
}
//---------------------------------------------------------------------------

