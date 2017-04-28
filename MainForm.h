//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "Cnode.h"
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class TfrmMain:public TForm
{
__published:    // IDE-managed Components
    TImage*                 Image1;
    TButton*                Button1;
    TButton*                Button2;
    TOpenDialog*            od;
    void __fastcall         Button1Click(TObject* Sender);
    void __fastcall         FindPath();
    bool __fastcall         ExpandNode(CNode* node);
    void __fastcall         Button2Click(TObject* Sender);
private:    // User declarations
public:     // User declarations
    __fastcall              TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain*frmMain;
//---------------------------------------------------------------------------
#endif
